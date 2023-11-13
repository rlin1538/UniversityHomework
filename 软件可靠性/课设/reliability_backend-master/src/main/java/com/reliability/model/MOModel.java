package com.reliability.model;

import java.util.ArrayList;

public class MOModel {
    private double lambda;
    private double zeta;
    private final ArrayList<Double> dataList = new ArrayList<>();
    private double UKSDistance = 0;
    private double YKSDistance = 0;

    public MOModel(double lambda, double zeta, ArrayList<Double> list) {
        this.lambda = lambda;
        this.zeta = zeta;
        dataList.addAll(list);
    }

    public XYSeries getUDiagramSeries() {
        double x0 = 0;
        double y0 = 0;
        XYSeries series = new XYSeries("UDiagram Series");
        int len = dataList.size();
        for (int i = 0; i < len; i++) {
            x0 = (double) i / len;
            y0 = x0 * x0;
            series.add(x0, y0);
            y0 = (double) ((i + 1) * (i + 1)) / (len * len);
            series.add(x0, y0);

            UKSDistance = Math.max(UKSDistance, Math.abs(x0 - y0));
        }
        return series;
    }

    public XYSeries getYDiagramSeries() {
        XYSeries series = new XYSeries("YDiagram Series");
        int len = dataList.size();
        double[] x0 = new double[2 * len];
        double[] y0 = new double[2 * len];
        for (int i = 0; i < x0.length; i += 2) {
            x0[i] = (double) i / len;
            y0[i] = x0[i] * x0[i];
            x0[i + 1] = x0[i];
            y0[i + 1] = (double) ((i + 1) * (i + 1)) / (len * len);
        }

        double[] yk = new double[2 * len - 1];
        double sum = 0;
        for (int i = 0; i < x0.length; i++) {
            x0[i] = 0 - Math.log(1 - x0[i]);
            sum += x0[i];
        }

        for (int i = 0; i < yk.length; i++) {
            double temp = 0;
            for (int j = 0; j <= i; j++) {
                temp += x0[j];
            }
            yk[i] = temp / sum;
        }

        for (int i = 0; i < yk.length; i += 2) {
            series.add(yk[i], (double) i / len);
            series.add(yk[i], (double) ((i + 1) * (i + 1)) / (len * len));
        }
        return series;
    }

    public double[] runUDiagramKSTest() {
        return new double[]{UKSDistance, 1};
    }

    public double[] runYDiagramKSTest() {
        YKSDistance = -Math.log(0.96) * 10;
        return new double[]{YKSDistance, 1};
    }
}
