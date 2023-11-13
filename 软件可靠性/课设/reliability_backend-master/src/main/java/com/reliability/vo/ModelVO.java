package com.reliability.vo;

import com.reliability.model.XYSeries;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.List;

@Data
@NoArgsConstructor
public class ModelVO {
    private List<List<Double>> u, y;
    private List<List<Double>> real, predict;
    double[] uks, yks;
    double deviation;

    public ModelVO(XYSeries u, XYSeries y, XYSeries real, XYSeries predict, double[] uks, double[] yks) {
        this.u = u.getL();
        this.y = y.getL();
        this.real = real.getL();
        this.predict = predict.getL();
        this.uks = uks;
        this.yks = yks;
    }
}
