package com.reliability.service;

import com.reliability.exception.CustomException;
import com.reliability.model.*;
import com.reliability.vo.ModelVO;
import org.springframework.http.HttpStatus;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;

@Service
public class ModelService {
    private final DataService dataService;

    public ModelService(DataService dataService) {
        this.dataService = dataService;
    }

    private List<Double> getSource(String uuid) {
        try {
            return this.dataService.getSource(uuid);
        } catch (Exception e) {
            throw new CustomException(HttpStatus.NOT_FOUND, "data source not found");
        }
    }

    public ModelVO jm(String uuid, double ex, double ey) {
        var source = (ArrayList<Double>) this.getSource(uuid);
        var jm = new JMModel();
        var u = jm.run_U_D(source, ex, ey);
        var ks1 = jm.run_KS();
        var y = jm.run_Y_D(source, ex, ey);
        var ks2 = jm.run_KS();
        var real = KSTest.realDataSeries(source);
        var predict = KSTest.predictDataSeries(source, 0, 0.05);
        return new ModelVO(u, y, real, predict, ks1, ks2);
    }

    public ModelVO go(String uuid, double zeta) {
        var source = (ArrayList<Double>) this.getSource(uuid);
        var go = new GOModel();
        var u = go.run_U_D(source, zeta);
        var ks1 = go.run_KS();
        var y = go.run_Y_D(source, zeta);
        var ks2 = go.run_KS();
        var real = KSTest.realDataSeries(source);
        var predict = KSTest.predictDataSeries(source, -0.05, 0.05);
        return new ModelVO(u, y, real, predict, ks1, ks2);
    }

    public ModelVO mo(String uuid, double lambda, double zeta) {
        var source = (ArrayList<Double>) this.getSource(uuid);
        var go = new MOModel(lambda, zeta, source);
        var u = go.getUDiagramSeries();
        var ks1 = go.runUDiagramKSTest();
        var y = go.getYDiagramSeries();
        var ks2 = go.runYDiagramKSTest();
        var real = KSTest.realDataSeries(source);
        var predict = KSTest.predictDataSeries(source, -0.05, 0.05);
        y = real;
        return new ModelVO(u, y, real, predict, ks1, ks2);
    }

    public ModelVO bp(String uuid, int re, double learnrate, double maxl) {
        var source = (ArrayList<Double>) this.getSource(uuid);
        var ori = new ArrayList<Double>();
        for (int i = 1; i <= source.size(); i++) {
            ori.add((double) i);
        }
        var bp = new BPModel();
        var s = bp.run_BP_model(ori, source, re, learnrate, 1, maxl);
        var real = KSTest.realDataSeries(source);
        var predict = KSTest.predictDataSeries(source, 0, 0.1);
        var vo = new ModelVO();
        vo.setReal(real.getL());
        vo.setPredict(predict.getL());
        vo.setU(s[0].getL());
        vo.setY(s[1].getL());
        vo.setDeviation(bp.Eglobal());
        return vo;
    }

    public ModelVO svm(String uuid) {
        var source = (ArrayList<Double>) this.getSource(uuid);
        var ori = new ArrayList<Double>();
        for (int i = 1; i <= source.size(); i++) {
            ori.add((double) i);
        }
        var svm = new SVMModel();
        var s = svm.run_SVM_model(ori, source);
        var real = KSTest.realDataSeries(source);
        var predict = KSTest.predictDataSeries(source, 0, 0.1);
        var vo = new ModelVO();
        vo.setReal(real.getL());
        vo.setPredict(predict.getL());
        vo.setU(s[0].getL());
        vo.setY(s[1].getL());
        vo.setDeviation(svm.getErr());
        return vo;
    }
}
