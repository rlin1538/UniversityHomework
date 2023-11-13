import tensorflow.compat.v1 as tf
tf.disable_v2_behavior()
import numpy as np
import matplotlib.pyplot as plt
 
#创建一个神经网络层
def add_layer(input,in_size,out_size,activation_function=None):
    """
    :param input: 数据输入
    :param in_size: 输入大小
    :param out_size: 输出大小
    :param activation_function: 激活函数（默认没有）
    :return:output：数据输出
    """
    #权值初始化
    Weight=tf.Variable(tf.random_normal([in_size,out_size]) )
    #偏置初始化
    biases=tf.Variable(tf.zeros([1,out_size]) +0.1 )
    W_mul_x_plus_b=tf.matmul(input,Weight) + biases
    #根据是否有激活函数
    if activation_function == None:
        output=W_mul_x_plus_b
    else:
        output=activation_function(W_mul_x_plus_b)
    return output

#学习率
eta = 0.1
"学习率"
d = 1
"输入节点个数"
l = 1
"输出节点个数"
q = 10
"隐藏层个数"
#创建一个具有输入层，隐藏层，输出层的三层神经网络，神经元个数分别为1，10，1
x_data=np.loadtxt('CSR1.txt',delimiter='\t',usecols=0,skiprows=11)[:,np.newaxis]   # 创建输入数据  np.newaxis分别是在列(第二维)上增加维度，原先是（300，）变为（300，1）
#noise=np.random.normal(0,0.05,x_data.shape)
y_data=np.loadtxt('CSR1.txt',delimiter='\t',usecols=1,skiprows=11)[:,np.newaxis]    # 创建输入数据对应的输出
 

print(x_data.shape)
# x=np.linspace(-1,1,300)
# print(x.shape)
 
#定义输入数据
xs=tf.placeholder(tf.float32,[None,d])
ys=tf.placeholder(tf.float32,[None,l])
 
#定义一个隐藏层,用sigmoid函数
hidden_layer1=add_layer(xs,d,q,activation_function=tf.nn.sigmoid)
#定义一个输出层，不使用，即默认y=x
prediction=add_layer(hidden_layer1,q,l,activation_function=None)
 
#求解神经网络参数
#1.定义损失函数
loss=tf.reduce_mean(tf.reduce_sum(tf.square(ys-prediction) ,reduction_indices=[1] ))
#2.定义训练过程
train_step=tf.train.GradientDescentOptimizer(eta).minimize(loss)
 
init=tf.global_variables_initializer()
sess=tf.Session()
sess.run(init)
 
 
# 绘制求解的曲线
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
ax.scatter(x_data, y_data)
plt.ion()  #Turn interactive mode on 开启互动模式
plt.show() #Display a figure
 

#3.进行训练
for i in range(1000):
    sess.run(train_step,feed_dict={xs:x_data,ys:y_data})
    if i%100==0:
        try:
            ax.lines.remove(lines[0])  #擦除之前的轨迹
        except Exception:
           pass
 
        print(sess.run(loss,feed_dict={xs:x_data,ys:y_data} )  )
        # 计算预测值
        prediction_value = sess.run(prediction, feed_dict={xs: x_data})
        #print(prediction.shape)
        # 绘制预测值
        lines = ax.plot(x_data, prediction_value, 'r-', lw=5)
        plt.pause(0.1)
# 关闭Session
plt.pause(1000)
 
#关闭sess
sess.close()