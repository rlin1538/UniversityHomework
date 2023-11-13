package com.reliability.model;

import lombok.AllArgsConstructor;
import lombok.Data;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

@Data
public class XYSeries {
    private final List<List<Double>> l = new ArrayList<>();
    private final String name;

    public XYSeries(String name) {
        this.name = name;
    }

    public void add(Double x, Double y) {
        this.l.add(new ArrayList<>(Arrays.asList(x, y)));
    }

//    public void show() {
//        this.l.forEach(xy -> {
//            System.out.printf("[%f,%f],", xy.getX(), xy.getY());
//        });
//    }
}

