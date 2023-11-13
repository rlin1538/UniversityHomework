<template>
  <div id="list">
    <div id="menu">
      <Menu
        mode="horizontal"
        :theme="light"
        active-name="jm"
        @on-select="onSelect"
      >
        <MenuItem name="jm" style="width: 20%">JM模型</MenuItem>
        <MenuItem name="go" style="width: 20%">GO模型</MenuItem>
        <MenuItem name="mo" style="width: 20%">MO模型</MenuItem>
        <MenuItem name="bp" style="width: 20%">BP模型</MenuItem>
        <MenuItem name="svm" style="width: 20%">SVM模型</MenuItem>
      </Menu>
    </div>
    <div id="info">
      <div v-if="name === 'jm'">
        <h1>JM模型</h1>
        <h2>模型背景</h2>
        <p class="pp">
          该模型是由Jelinski、Moranda于1972年开发的可靠性模型，是最早建立的软件可靠性模型之一，曾用于麦克唐奈道格拉斯海军工程中。
        </p>
        <p class="pp">
          该模型以一种简便和合乎直觉的方式表明如何根据软件缺陷的显露历程来预计未来软件可靠性的行为，它包含软件可靠性建模中若干典型和最主要的假设，因而引发出后来的许多种变形。
        </p>
        <p class="pp">
          事实上，现有大多数软件可靠性模型要么可认为是其变形或扩展，要么与其密切相关。该模型对软件可靠性定量分析技术的建立和发展做出了重要的贡献，是软件可靠性研究领域的第一个里程碑。
        </p>
        <h2>模型假设</h2>
        <li>程序中的固有错误数N0是一个未知的常数</li>
        <li>
          程序中的各个错误是相互独立的，每个错误导致系统发生失效的可能性大致相同，各次失效间隔时间也相互独立
        </li>
        <li>
          测试过程中检测到的错误，都被排除，每次排错只排除一个错误，排错时间可以忽略不计，在排错过程中不引入新的错误
        </li>
        <li>
          程序的失效率在每个失效间隔时间内是常数，其数值正比于程序中残留的错误数，在第i个测试区间，其失效率函数为:
        </li>
        <li>
          错误以相等的可能发生，且相互独立，错误检测率正比于当前程序中的错误数
        </li>
        <li>软件的运行方式与预期的运行方式相似</li>
      </div>
      <div v-if="name === 'go'">
        <h1>GO模型</h1>
        <h2>模型背景</h2>
        <p>
          Goel-Okumoto软件可靠性模型(G-O模型)于1979年由Goel和Okumoto提出，属于NHPP有限错误模型。
        </p>
        <h2>模型假设</h2>
        <li>
          测试未运行时的软件失效为0；当测试进行时，软件失效服从均值为𝐦(𝒕)的泊松分布
        </li>
        <li>当△𝐭→𝟎 时, 测试时间(𝒕,𝒕+𝜟𝒕)内产生的失效与软件残留错误成正比</li>
        <li>对于任一组有限时间点，在对应时间段分别发生的失效次数相互独立</li>
        <li>
          每次只修正一个错误，当软件故障出现时，引发故障的错误被立即排除，并不会引入新的错误
        </li>
      </div>
      <div v-if="name === 'mo'">
        <h1>MO模型</h1>
        <h2>模型概述</h2>
        <li>该模型是失效强度函数随失效发生而指数递减的非均匀泊松过程</li>
        <li>
          指数率递减反映了以下观点：早起发现的缺陷比晚期发现的缺陷对失效强度函数的减小作用大
        </li>
        <li>之所以称之为对数泊松模型是因为期望的失效数是时间的对数函数</li>
        <h2>假设与数据要求</h2>
        <li>到时刻t的累计失效数M(t)符合泊松过程</li>
        <li>
          失效强度随着失效期望数的增加而呈现指数递减，即λ(t)=λ0eθμ(t)其中μ(t)为均值函数，θ>0是失效强度递减参量，且λ0>0是初始失效强度
        </li>
        <li>软件的运行方式与预期的运用方式相似</li>
        <li>每个错误发生的机会相同，且严重等级相同</li>
        <li>失效之间相互独立</li>
        <li>数据要求为：完全失效数据，即失效间隔时间或累计失效时间</li>
      </div>
      <div v-if="name === 'bp'">
        <h1>BP模型</h1>
        <h2>模型背景</h2>
        <p>
          BP (back propagation) 神经网络是 1986 年由 Rumelhart 和 McClelland
          为首的科学家提出的概念，是一种按照误差逆向传播算法训练的多层前馈神经网络，是目前应用最广泛的神经网络。BP
          神经网络具有任意复杂的模式分类能力和优良的多维函数映射能力，解决了简单感知器不能解决的异或
          (Exclusive OR，XOR) 和一些其他问题。从结构上讲，BP
          网络具有输入层、隐藏层和输出层；从本质上讲，BP
          算法就是以网络误差平方为目标函数、采用梯度下降法来计算目标函数的最小值
        </p>
        <h2>假模型原理</h2>
        <p>
          利用输出后的误差来估计输出层的直接前导层的误差，再用这个误差估计更前一层的误差，如此一层一层的反传下去，就获得了所有其他各层的误差估计
        </p>
      </div>
      <div v-if="name === 'svm'">
        <h1>SVM模型</h1>
        <h2>模型介绍</h2>
        <p>
          支持向量机（Support Vector Machine, SVM）是一类按监督学习（supervised
          learning）方式对数据进行二元分类的广义线性分类器（generalized linear
          classifier），其决策边界是对学习样本求解的最大边距超平面（maximum-margin
          hyperplane
        </p>
      </div>
      <Divider></Divider>
      <Params></Params>
    </div>
  </div>
</template>

<script>
import Params from '~/components/Params'
export default {
  components: {
    Params,
  },
  data() {
    return {
      name: 'jm',
    }
  },
  computed: {
    show() {
      return this.$store.state.model.show
    },
  },
  methods: {
    onSelect(name) {
      this.$store.commit('updateName', name)
      this.$store.commit('updateShow', false)
      this.name = name
    },
  },
}
</script>

<style scoped>
#list {
  display: flex;
  flex-direction: column;
}

#menu {
  margin-top: 10px;
}

#info {
  width: 100%;
}

.pp {
  text-indent: 2em;
}
</style>
