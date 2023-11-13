package com.reliability.model;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class JMModel {
    private int n;                        //失效样本数据的个数
    private List<Double> t = new ArrayList<>();    //失效样本时间间隔数据
    private double ex;                    //ex控制误差
    private double ey;                    //ey控制误差

    private double resultN;                //N
    private double fie;                    //fie

    private double p;                    //过程变量
    private double root;                //过程变量

    protected List<Double> x;            //临时x坐标
    protected List<Double> y;            //临时y坐标
    protected List<Double> x0;            //为了画阶梯状而临时加的坐标

    private final XYSeries U_D;                //U图的坐标
    private final XYSeries Y_D;                //Y图的坐标

    protected double ks;                //ks距离ֵ
    protected double[][] ksTable = {    //ks检验表
            {0.97500, 0.99500}, {0.84189, 0.92929}, {0.70760, 0.82900}, {0.62394, 0.73424}, {0.56328, 0.66853}, {0.51926, 0.61661},
            {0.48342, 0.57581}, {0.45427, 0.54179}, {0.43001, 0.51332}, {0.40925, 0.48893}, {0.39122, 0.46770}, {0.37543, 0.44905},
            {0.36143, 0.43247}, {0.34890, 0.41762}, {0.33760, 0.40420}, {0.32733, 0.39201}, {0.31796, 0.38086}, {0.30936, 0.37062},
            {0.30143, 0.36117}, {0.29408, 0.35241}, {0.28724, 0.34427}, {0.28087, 0.33666}, {0.27490, 0.32954}, {0.26931, 0.32286},
            {0.26404, 0.31657}, {0.25907, 0.31064}, {0.25438, 0.30502}, {0.24993, 0.29971}, {0.24571, 0.29466}, {0.24170, 0.28987},
            {0.23788, 0.28530}, {0.23424, 0.28094}, {0.23076, 0.27677}, {0.22743, 0.27279}, {0.22425, 0.26897}, {0.22119, 0.26532},
            {0.21826, 0.26180}, {0.21544, 0.25843}, {0.21273, 0.25518}, {0.21012, 0.25205}, {0.20760, 0.24904}, {0.20517, 0.24613},
            {0.20283, 0.24332}, {0.20056, 0.24060}, {0.19837, 0.23798}, {0.19625, 0.23544}, {0.19420, 0.23298}, {0.19221, 0.23059},
            {0.19028, 0.22828}, {0.18841, 0.22604}, {0.18659, 0.22386}, {0.18482, 0.22174}, {0.18311, 0.21968}, {0.18144, 0.21768},
            {0.17981, 0.21574}, {0.17823, 0.21384}, {0.17669, 0.21199}, {0.17519, 0.21019}, {0.17373, 0.20844}, {0.17231, 0.20673},
            {0.17091, 0.20506}, {0.16956, 0.20343}, {0.16823, 0.20184}, {0.16693, 0.20029}, {0.16567, 0.19877}, {0.16443, 0.19729},
            {0.16322, 0.19584}, {0.16204, 0.19442}, {0.16088, 0.19303}, {0.15975, 0.19167}, {0.15864, 0.19034}, {0.15755, 0.18903},
            {0.15649, 0.18776}, {0.15544, 0.18650}, {0.15442, 0.18528}, {0.15342, 0.18408}, {0.15244, 0.18290}, {0.15147, 0.18174},
            {0.15052, 0.18060}, {0.14960, 0.17949}, {0.14868, 0.17840}, {0.14779, 0.17732}, {0.14691, 0.17627}, {0.14605, 0.17523},
            {0.14520, 0.17421}, {0.14437, 0.17321}, {0.14355, 0.17223}, {0.14274, 0.17126}, {0.14195, 0.17031}, {0.14117, 0.16938},
            {0.14040, 0.16846}, {0.13965, 0.16755}, {0.13891, 0.16666}, {0.13818, 0.16579}, {0.13746, 0.16493}, {0.13675, 0.16408},
            {0.13606, 0.16324}, {0.13537, 0.16242}, {0.13469, 0.16161}, {0.13403, 0.16081}
    };

    public JMModel() {                    //初始化函数
        setEx(0);
        setEy(0);
        n = 0;
        t = new ArrayList<>();
        t.add((double) 0);
        resultN = 0;
        fie = 0;
        p = 0;
        root = 0;

        U_D = new XYSeries("xySeries_U");
        Y_D = new XYSeries("xySeries_Y");

        ks = 0;
    }

    public int getN() {
        return n;
    }

    public void setN(int n) {
        this.n = n;
    }

    public List<Double> getT() {
        return t;
    }

    public void setT(List<Double> t) {
        this.t = t;
    }

    public double getEx() {
        return ex;
    }

    public void setEx(double ex) {
        this.ex = ex;
    }

    public double getEy() {
        return ey;
    }

    public void setEy(double ey) {
        this.ey = ey;
    }

    public double getResultN() {
        return resultN;
    }

    public void setResultN(double resultN) {
        this.resultN = resultN;
    }

    public double getFie() {
        return fie;
    }

    public void setFie(double fie) {
        this.fie = fie;
    }

    public double getP() {
        return p;
    }

    public void setP(double p) {
        this.p = p;
    }

    public double getRoot() {
        return root;
    }

    public void setRoot(double root) {
        this.root = root;
    }

    public void funcp() {                //p函数
        for (int i = 1; i <= this.n; i++)
            this.p += (i - 1) * (this.t.get(i) - this.t.get(i - 1));
        this.p = this.p / this.t.get(this.n);
    }

    public double funcf(double N) {        //f(N)函数
        double result = 0;
        for (int i = 1; i <= this.n; i++)
            result += (1.0 / (double) (N - i + 1));
        result = result - this.n / (N - this.p);
        return result;
    }

    public void step_1() {
        int left = 0;
        int right = 0;
        if (this.p > (this.n - 1) / 2.0) {
            left = this.n - 1;
            right = this.n;
            step_2(left, right);
        }
    }

    public void step_2(double left, double right) {
        while (funcf(right) > this.getEy()) {
            left = right;
            right++;
        }
        if (funcf(right) < this.getEx() * (-1))
            step_3(left, right);
        else {
            this.root = right;
            step_5();
        }
    }

    public void step_3(double left, double right) {
        if (Math.abs(right - left) < this.getEx()) {
            this.root = (right + left) / 2;
            step_5();
        } else {
            this.root = (right + left) / 2;
            step_4(left, right);
        }
    }

    public void step_4(double left, double right) {
        if (funcf(this.root) > this.getEy()) {
            left = this.root;
            step_3(left, right);
        } else if (funcf(this.root) < this.getEy() * (-1)) {
            right = this.root;
            step_3(left, right);
        } else
            step_5();
    }

    public void step_5() {
        this.resultN = this.root;
        double temp = 0;
        for (int i = 1; i <= this.n; i++)
            temp += ((i - 1) * (this.t.get(i) - this.t.get(i - 1)));
        this.fie = this.n / (this.resultN * this.t.get(this.n) - temp);
    }

    public double funcF(double x, int i) {                //F(x)概率分布函数
        double temp;
        temp = -this.getFie() * (this.getResultN() - i + 1.0) * x;
        temp = Math.pow(Math.E, temp);
        temp = 1.0 - temp;
        return temp;
    }

    public double funcfm(double x, int i) {                //f(x)概率密度函数
        double temp, temp2;
        temp = this.fie * (this.resultN - (double) i + 1.0);
        temp2 = Math.pow(Math.E, -temp * x);
        temp2 = temp * temp2;
        return temp2;
    }

    public void init_U_D() {                        //初始化U图
        this.x = new ArrayList<>();
        this.y = new ArrayList<>();
        this.x0 = new ArrayList<>();

        x.add((double) 0);                            //坐标原点(0,0)
        y.add((double) 0);

        for (int i = 1; i <= this.t.size() - 1; i++)        //构造U图主坐标
        {
            x.add((funcF(this.t.get(i), i)));
            double temp = (double) i / (double) (this.n);
            y.add(temp);
        }
    }

    public void init_Y_D() {                        //初始化Y图
        x = new ArrayList<>();
        y = new ArrayList<>();
        x0 = new ArrayList<>();

        x.add((double) 0);                            //构造坐标原点
        y.add((double) 0);

        for (int i = 1; i <= this.t.size() - 1; i++)        //构造Y图未处理坐标
        {
            x.add(funcF(this.t.get(i), i));
            double temp = (double) i / (double) (this.n);
            y.add(temp);
        }

        exchange();                                    //变换坐标
    }

    public void exchange() {                        //Y图坐标变换函数
        List<Double> tempx = new ArrayList<>();        //变换x坐标
        for (int i = 1; i <= this.x.size() - 1; i++) {
            double temp = this.x.get(i);
            if (temp == 1.0)
                temp = 0.9999999999999999;
            tempx.add(-Math.log(1.0 - temp));
        }


        List<Double> tempy = new ArrayList<>();        //变换Y坐标
        tempy.add((double) 0);
        for (int j = 0; j <= tempx.size() - 1; j++) {
            double sum1 = 0, sum2 = 0;
            for (int l = 0; l <= j; l++)
                sum1 = sum1 + tempx.get(l);
            for (int l = 0; l <= tempx.size() - 1; l++)
                sum2 = sum2 + tempx.get(l);
            tempy.add((double) sum1 / (double) sum2);
        }

        this.x = tempy;
    }

    public double solve_ks() {                            //获取KS距离函数
        List<Double> diff = new ArrayList<>();
        for (int i = 0; i <= this.y.size() - 1; i++)
            diff.add(this.x.get(i) - this.y.get(i));
        return Collections.max(diff);
    }

    public double isKSTest95() {                        //获取KS检验结果
        if (this.x.size() - 1 > 100) {
            if (this.ks < 1.35810 / Math.sqrt(this.x.size() - 1))
                return 1.0;
            else
                return 0.0;
        } else {
            if (this.ks < this.ksTable[this.x.size() - 2][0])
                return 1.0;
            else
                return 0.0;
        }
    }

    public XYSeries run_U_D(final List<Double> temp, double e_x, double e_y)        //U图运行函数
    {
        this.t = temp;                                    //初始化
        this.ex = e_x;
        this.ey = e_y;
        this.n = this.t.size() - 1;

        funcp();
        step_1();                                        //运行JM模型，参数估计

        init_U_D();                                        //运行U图，初始化坐标

        Collections.sort(this.x);                            //将坐标从小到大排序

        for (int i = 0; i <= this.x.size() - 1; i++)                //构造阶梯状函数坐标
            this.x0.add(this.x.get(i));

        for (int i = 0; i < this.x.size(); i++) {                //获取U图(XY坐标系的图像)
            if (i > 0)
                this.U_D.add(this.x.get(i - 1), this.y.get(i));
            this.U_D.add(this.x.get(i), this.y.get(i));
        }

        return this.U_D;
    }

    //@输出格式：double[0]是ks距离，直接输出；double[1]是检验结果，等于1时输出为“在显著性水平为0.05的情况下，拒绝原假设，即检验样本不满足改模型”，等于0时满足。
    public double[] run_KS() {                            //KS检验;U图Y图均适用;运行完毕U图再运行KS检验函数才能得到正确的U图KS检验结果。
        double[] temp = new double[2];

        this.ks = solve_ks();                            //获取KS距离
        temp[0] = this.ks;

        temp[1] = isKSTest95();                            //获取假设结果

        return temp;
    }

    public XYSeries run_Y_D(final List<Double> temp, double e_x, double e_y)        //Y图运行函数
    {
        this.t = temp;
        this.ex = e_x;
        this.ey = e_y;
        this.n = this.t.size() - 1;

        funcp();
        step_1();                                        //运行JM模型，参数估计

        init_Y_D();                                        //运行Y图，初始化坐标

        Collections.sort(this.x);                        //将坐标从小到大排列

        for (int i = 0; i <= this.x.size() - 1; i++)            //构造阶梯状函数的坐标
            this.x0.add(this.x.get(i));

        for (int i = 0; i < this.x.size(); i++) {            //获取Y图(XY坐标系的图像)
            if (i > 0)
                this.Y_D.add(this.x.get(i - 1), this.y.get(i));
            this.Y_D.add(this.x.get(i), this.y.get(i));
        }

        return this.Y_D;
    }
}
