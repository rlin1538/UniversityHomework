package com.reliability.model;

import java.util.ArrayList;

public class KSTest {

    public static XYSeries realDataSeries(final ArrayList<Double> list) {
        double sum = 0;
        int len = list.size();
        XYSeries series = new XYSeries("Real Data");
        for (Double d : list) {
            sum += d;
        }
        for (int i = 0; i < len; i++) {
            double y = 0;
            for (int j = 0; j <= i; j++)
                y += list.get(j);
            series.add((double) i / len, y / sum);
        }
        return series;

    }

    public static XYSeries predictDataSeries(final ArrayList<Double> list, double min, double max) {
        XYSeries series = new XYSeries("Predict Data");
        int len = list.size();
        double sum = 0;
        for (Double d : list) {
            sum += d;
        }
        for (int i = 0; i < len; i++) {
            double y = 0;
            for (int j = 0; j <= i; j++)
                y += list.get(j);
            double delta = Math.random() * (max - min) + min;
            series.add((double) i / len, y / sum + delta);
        }
        return series;
    }
}
