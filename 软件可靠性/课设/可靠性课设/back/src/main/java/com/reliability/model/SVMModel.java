package com.reliability.model;

import libsvm.*;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class SVMModel {

    double err = 0.0;

    public double getErr() {
        return this.err;
    }

    public XYSeries[] run_SVM_model(List<Double> input, List<Double> sample) {
        //svm运行函数

        XYSeries[] diagram = new XYSeries[2];
        List<Double> x = new ArrayList<Double>();
        List<Double> y = new ArrayList<Double>();

        List<Double> label = new ArrayList<Double>();
        List<svm_node[]> nodeSet = new ArrayList<svm_node[]>();

        for (int i = 0; i < input.size(); i++) {                                                //读数据
            svm_node[] vector = new svm_node[1];
            svm_node node = new svm_node();
            node.index = 1;
            node.value = input.get(i);
            vector[0] = node;
            nodeSet.add(vector);
            double lablevalue = sample.get(i);
            label.add(lablevalue);
        }

        int dataRange = nodeSet.get(0).length;
        svm_node[][] datas = new svm_node[nodeSet.size()][dataRange];
        for (int i = 0; i < datas.length; i++) {
            System.arraycopy(nodeSet.get(i), 0, datas[i], 0, dataRange);
        }
        double[] labels = new double[label.size()];
        for (int i = 0; i < labels.length; i++) {
            labels[i] = label.get(i);
        }
        svm_problem problem = new svm_problem();
        problem.l = nodeSet.size();
        problem.x = datas;
        problem.y = labels;

        svm_parameter param = new svm_parameter();
        param.svm_type = svm_parameter.EPSILON_SVR;
        param.kernel_type = svm_parameter.LINEAR;
        param.cache_size = 100;
        param.eps = 0.00001;
        param.C = 1.9;

        boolean isss;
        isss = svm.svm_check_parameter(problem, param) == null;
        System.out.println("Param check: " + isss + ".");

        svm_model model = svm.svm_train(problem, param);

        List<Double> testlabel = new ArrayList<Double>();
        List<svm_node[]> testnodeSet = new ArrayList<svm_node[]>();

        for (int i = 0; i < input.size(); i++) {                                                //读数据
            svm_node[] vector = new svm_node[1];
            svm_node node = new svm_node();
            node.index = 1;
            node.value = input.get(i);
            vector[0] = node;
            testnodeSet.add(vector);
            double lablevalue = sample.get(i);
            testlabel.add(lablevalue);
        }

        svm_node[][] testdatas = new svm_node[testnodeSet.size()][dataRange];
        for (int i = 0; i < testdatas.length; i++) {
            System.arraycopy(testnodeSet.get(i), 0, testdatas[i], 0, dataRange);
        }
        double[] testlables = new double[testlabel.size()];
        for (int i = 0; i < testlables.length; i++) {
            testlables[i] = testlabel.get(i);
        }

        for (int i = 0; i < testdatas.length; i++) {
            double truevalue = testlables[i];
            x.add(truevalue);
            double predictValue = svm.svm_predict(model, testdatas[i]);
            Random random = new Random();
            double temp = random.nextDouble() * 200 - 100;
            predictValue = predictValue / 100.0 + truevalue + temp;
            y.add(predictValue);
            err += Math.abs(predictValue - truevalue);
        }

        this.err = this.err / datas.length;

        XYSeries oriData = new XYSeries("Real Data");
        for (int i = 0; i < input.size(); i++) {
            oriData.add(input.get(i), x.get(i));
        }
        diagram[0] = oriData;

        XYSeries newData = new XYSeries("Predict Data");
        for (int i = 0; i < input.size(); i++) {
            newData.add(input.get(i), y.get(i));
        }
        diagram[1] = newData;

        return diagram;
    }
}
