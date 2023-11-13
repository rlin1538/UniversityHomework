package com.reliability.model;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public class BPModel {
    int IM = 0;                                                //input element number
    int RM = 0;                                                //middle element number
    int OM = 0;                                                //output element number

    Double[] input_vector;                                    //input vector
    Double[] hidden_input_vector;                            //hidden vector
    Double[] hidden_output_vector;                            //hidden vector
    Double[] output_input_vector;                            //output vector
    Double[] output_output_vector;                            //output vector
    Double[] expect_output_vector;                            //expected output
    Double[][] Win;                                        //weight of input to middle
    Double[][] Wout;                                        //weight of middle to output
    Double[] a;                                            //threshold value of middle
    Double[] b;                                            //threshold value of output
    Double[] hidden_delta;                                    //hidden delta array
    Double[] output_delta;                                    //output delta array
    List<Double> sample_var = new ArrayList<>();            //data sample
    List<Double> sample_result = new ArrayList<>();            //data sample result exptected
    double accuracy = 0;                                    //calculating accuracy
    double Maxlearning = 0;                                    //the most times of learning
    double learnrate = 0;                                    //the learnrate

    double Max1, Max2;

    protected List<Double> x;                                //临时x坐标
    protected List<Double> y;                                //临时y坐标

    private XYSeries[] diagram;

    public void Train() {                                    //训练
        int time;                                        //学习次数
        for (time = 0; time <= this.Maxlearning; time++) {
            Forward();                                        //前向传播
            if (this.Eglobal() < this.accuracy)                //如果误差达到了精度，退出循环，结束训练，保留阈值和权值。
                break;
            Backward();                                        //反向传播
        }
        System.out.println(time);
        System.out.println(this.Eglobal());
    }

    public void Forward() {                        //前向传播
        Calcul_hidden_input();                    //求解隐藏层输入
        Calcul_hidden_output();                    //求解隐藏层输出

        Calcul_output_input();                    //求解输出层输入
        Calcul_output_output();                    //求解输出层输出
    }

    public void Backward() {                    //反向传播
        Calcul_output_delta();                    //计算输出层的delta值
        Calcul_hidden_delta();                    //计算隐含层的delta值
        update_output_w();                        //更新输出层的权值
        update_hidden_w();                        //更新隐含层的权值
        update_output_b();                        //更新输出层阈值
        update_hidden_a();                        //更新隐含层阈值
    }

    public void Calcul_hidden_input() {            //直接套公式
        for (int i = 0; i < this.RM; i++) {
            double sum = 0.0;
            for (int j = 0; j < this.IM; j++) {
                sum = sum + Win[j][i] * this.input_vector[j];
            }
            this.hidden_input_vector[i] = sum - this.a[i];
        }
    }

    public void Calcul_hidden_output() {        //同上
        for (int i = 0; i < this.RM; i++)
            this.hidden_output_vector[i] = sigmoid(this.hidden_input_vector[i]);
    }

    public void Calcul_output_input() {            //同上
        for (int i = 0; i < this.OM; i++) {
            double sum = 0.0;
            for (int j = 0; j < this.RM; j++)
                sum = sum + Wout[j][i] * this.hidden_output_vector[j];
            this.output_input_vector[i] = sum - this.b[i];
        }
    }

    public void Calcul_output_output() {        //同上
        for (int i = 0; i < this.OM; i++)
            this.output_output_vector[i] = sigmoid(this.output_input_vector[i]);
    }

    public void Calcul_output_delta() {            //计算δo，套公式
        for (int i = 0; i < this.OM; i++) {
            double value = 0.0;
            double temp = 0.0;
            value = -(this.expect_output_vector[i] - this.output_output_vector[i]);
            temp = sigmoid(this.output_input_vector[i]);    //f(x)*(1-f(x)=f'(x)
            temp = temp * (1.0 - temp);
            value = value * temp;
            this.output_delta[i] = -value;
        }
    }

    public void Calcul_hidden_delta() {            //计算δh，套公式
        for (int i = 0; i < this.RM; i++) {
            double value = 0.0;
            double temp = 0.0;
            for (int j = 0; j < this.OM; j++)
                value = value + this.output_delta[j] * this.Wout[i][j];
            value = -value;
            temp = sigmoid(this.hidden_input_vector[i]);
            temp = temp * (1.0 - temp);            //f(x)*(1-f(x))=f'(x)
            value = value * temp;
            this.hidden_delta[i] = -value;
        }
    }

    public void update_output_w() {                //更新隐含层到输出层的权值
        for (int i = 0; i < this.RM; i++)
            for (int j = 0; j < this.OM; j++)
                this.Wout[i][j] = this.Wout[i][j] + this.learnrate * this.output_delta[j] * this.hidden_output_vector[i];
    }

    public void update_hidden_w() {                //更新输入层到隐含层的权值
        for (int i = 0; i < this.IM; i++)
            for (int j = 0; j < this.RM; j++)
                this.Win[i][j] = this.Win[i][j] + this.learnrate * this.hidden_delta[j] * this.input_vector[i];
    }

    public void update_output_b() {                //更新输出层的阈值
        for (int i = 0; i < this.OM; i++)
            this.b[i] = this.b[i] + this.learnrate * this.output_delta[i];
    }

    public void update_hidden_a() {                //更新隐含层的阈值
        for (int i = 0; i < this.RM; i++)
            this.a[i] = this.a[i] + this.learnrate * this.hidden_delta[i];
    }

    public double sigmoid(double x) {            //激励函数
        double y = 0.0;
        y = 1.0 + Math.pow(Math.E, -x);
        y = 1.0 / y;
        return y;
    }

    public double Eglobal() {                    //误差函数
        double temp = 0.0;
        double temp2 = 0.0;
        for (int i = 0; i < this.OM; i++) {
            temp2 = this.expect_output_vector[i] - this.output_output_vector[i];
            temp2 = Math.pow(temp2, 2);            //差的平方
            temp = temp + temp2;                //求和
        }
        temp = temp * 0.5;                        //和要除以2
        return temp;                            //全局误差
    }

    public void free2one() {                    //归一化处理
        Max1 = Collections.max(this.sample_result);
        List<Double> temp2 = new ArrayList<>();
        for (int i = 0; i < this.sample_result.size(); i++)
            temp2.add(this.sample_result.get(i) / Max1);
        this.sample_result = temp2;

        Max2 = Collections.max(this.sample_var);
        temp2 = new ArrayList<>();
        for (int i = 0; i < this.sample_var.size(); i++)
            temp2.add(this.sample_var.get(i) / Max2);
        this.sample_var = temp2;
    }

    public void init_model() {
        input_vector = new Double[IM];
        hidden_input_vector = new Double[RM];
        hidden_output_vector = new Double[RM];
        output_input_vector = new Double[OM];
        output_output_vector = new Double[OM];
        expect_output_vector = new Double[OM];                //need to give value
        Win = new Double[IM][RM];
        Wout = new Double[RM][OM];
        a = new Double[RM];
        b = new Double[OM];
        hidden_delta = new Double[RM];
        output_delta = new Double[OM];

        this.x = new ArrayList<>();
        this.y = new ArrayList<>();

        this.diagram = new XYSeries[2];

        Random random = new Random();                        //generating random number
        for (int m = 0; m < this.IM; m++)
            for (int n = 0; n < this.RM; n++)
                Win[m][n] = random.nextDouble() * 2 - 1;    //random is (0,1),so random*2-1 is (-1,1)
        for (int m = 0; m < this.RM; m++)
            for (int n = 0; n < this.OM; n++)
                Wout[m][n] = random.nextDouble() * 2 - 1;    //the same
        for (int m = 0; m < this.RM; m++)
            a[m] = random.nextDouble() * 2 - 1;                //the same
        for (int n = 0; n < this.OM; n++)
            b[n] = random.nextDouble() * 2 - 1;                //the same
    }

    //参数从左到右为，输入样本，期望输出样本，重构维数(136||120)，学习速率(0.55)，学习精度(1)，最大学习次数(5000)。****注意****，样本第0个元素没有规定，直接读入。
    //返回为：diagram[0]是原数据，[1]是学习结果。
    public XYSeries[] run_BP_model(List<Double> input, List<Double> sample, int re, double learnrate_, double accuracy_, double Maxl) {            //BP算法运行

        this.sample_result = sample;            //期望输出
        this.sample_var = input;                //输入

        IM = this.sample_result.size();
        RM = re;
        OM = this.sample_result.size();

        init_model();
        free2one();

        learnrate = learnrate_;
        accuracy = accuracy_;
        Maxlearning = Maxl;

        sample_var.toArray(this.input_vector);                //将输入数据转换为输入层向量
        sample_result.toArray(this.expect_output_vector);    //将输出数据转换为期望输出向量

        Train();

        XYSeries oriData = new XYSeries("Real Data");
        for (int i = 0; i < this.sample_var.size(); i++) {
            oriData.add(this.sample_var.get(i) * Max2, this.sample_result.get(i) * Max1);
        }
        this.diagram[0] = oriData;

        XYSeries nowData = new XYSeries("Predict Data");
        for (int i = 0; i < this.sample_var.size(); i++) {
            nowData.add(this.sample_var.get(i) * Max2, this.output_output_vector[i] * Max1);
        }
        this.diagram[1] = nowData;

        return this.diagram;
    }
}
