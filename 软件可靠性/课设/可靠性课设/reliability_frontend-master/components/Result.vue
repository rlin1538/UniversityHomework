<template>
  <div id="result">
    <div v-if="name === 'jm'" id="jm" class="graph">
      <Alert type="success" show-icon style="width: 100%">
        成功
        <span slot="desc">
          <p>参数: ex = {{ model.params.ex }}, ey = {{ model.params.ey }}</p>
          <p>U图KS距离: {{ jm.uks[0] }}</p>
          <p>Y图KS距离: {{ jm.yks[0] }}</p>
          <p
            v-text="
              '基于U图的KS检验结果' + jm.uks[0] < 0.001
                ? '失效数据样本不满足JM模型'
                : '失效数据样本满足JM模型'
            "
          ></p>
          <p
            v-text="
              '基于Y图的KS检验结果' + jm.yks[0] < 0.001
                ? '失效数据样本不满足JM模型'
                : '失效数据样本满足JM模型'
            "
          ></p>
        </span>
      </Alert>
      <echart :options="jm_u"></echart>
      <echart :options="jm_y"></echart>
      <echart :options="jm_ks"></echart>
    </div>
    <div v-if="name === 'go'" id="go" class="graph">
      <Alert type="success" show-icon style="width: 100%">
        成功
        <span slot="desc">
          <p>参数: zeta = {{ model.params.zeta }}</p>
          <p>U图KS距离: {{ go.uks[0] }}</p>
          <p>Y图KS距离: {{ go.yks[0] }}</p>
          <p
            v-text="
              '基于U图的KS检验结果' + go.uks[0] < 0.001
                ? '失效数据样本不满足GO模型'
                : '失效数据样本满足GO模型'
            "
          ></p>
          <p
            v-text="
              '基于Y图的KS检验结果' + go.yks[0] < 0.001
                ? '失效数据样本不满足GO模型'
                : '失效数据样本满足GO模型'
            "
          ></p>
        </span>
      </Alert>
      <echart :options="go_u"></echart>
      <echart :options="go_y"></echart>
      <echart :options="go_ks"></echart>
    </div>
    <div v-if="name === 'mo'" id="mo" class="graph">
      <Alert type="success" show-icon style="width: 100%">
        成功
        <span slot="desc">
          <p>
            参数: lambda = {{ model.params.lambda }}, zeta =
            {{ model.params.zeta }}
          </p>
          <p>U图KS距离: {{ mo.uks[0] }}</p>
          <p>Y图KS距离: {{ mo.yks[0] }}</p>
          <p
            v-text="
              '基于U图的KS检验结果' + mo.uks[0] < 0.001
                ? '失效数据样本不满足MO模型'
                : '失效数据样本满足MO模型'
            "
          ></p>
          <p
            v-text="
              '基于Y图的KS检验结果' + mo.yks[0] < 0.001
                ? '失效数据样本不满足MO模型'
                : '失效数据样本满足MO模型'
            "
          ></p>
        </span>
      </Alert>
      <echart :options="mo_u"></echart>
      <echart :options="mo_y"></echart>
      <echart :options="mo_ks"></echart>
    </div>
    <div v-if="name === 'bp'" id="bp" class="graph">
      <Alert type="success" show-icon style="width: 100%">
        成功
        <span slot="desc">
          <p>
            参数: 学习系数 = {{ model.params.learnrate }}, 重构维数 =
            {{ model.params.re }}, 训练代数 = {{ model.params.maxl }}
          </p>
          <p>全局学习误差: {{ bp.deviation }}</p>
        </span>
      </Alert>
      <echart :options="bp_g"></echart>
      <echart :options="bp_ks"></echart>
    </div>
    <div v-if="name === 'svm'" id="svm" class="graph">
      <Alert type="success" show-icon style="width: 100%">
        成功
        <span slot="desc">
          <p>全局学习误差: {{ svm.deviation }}</p>
        </span>
      </Alert>
      <echart :options="svm_g"></echart>
      <echart :options="svm_ks"></echart>
    </div>
  </div>
</template>

<script>
export default {
  data() {
    return {
      jm: {
        u: [],
        y: [],
        real: [],
        predict: [],
        uks: [],
        yks: [],
      },
      go: {
        u: [],
        y: [],
        uks: [],
        yks: [],
        real: [],
        predict: [],
      },
      mo: {
        u: [],
        y: [],
        uks: [],
        yks: [],
        real: [],
        predict: [],
      },
      bp: {
        u: [],
        y: [],
        uks: [],
        yks: [],
        real: [],
        predict: [],
        deviation: 0,
      },
      svm: {
        u: [],
        y: [],
        uks: [],
        yks: [],
        real: [],
        predict: [],
        deviation: 0,
      },
      jm_u: {
        title: {
          text: 'U图',
          subtext: 'JM模型',
          x: 'center',
        },
        legend: {
          x: 'left',
          data: ['U', 'Base'],
        },
        toolbox: {
          feature: {
            saveAsImage: {},
          },
        },
        xAxis: {
          type: 'value',
        },
        yAxis: {
          type: 'value',
        },
        series: [
          {
            name: 'U',
            type: 'line',
            symbol: 'none',
            data: [],
          },
          {
            name: 'Base',
            type: 'line',
            data: [
              [0, 0],
              [1, 1],
            ],
          },
        ],
      },
      jm_y: {
        title: {
          text: 'Y图',
          subtext: 'JM模型',
          x: 'center',
        },
        legend: {
          x: 'left',
          data: ['Y', 'Base'],
        },
        toolbox: {
          feature: {
            saveAsImage: {},
          },
        },
        xAxis: {
          type: 'value',
        },
        yAxis: {
          type: 'value',
        },
        series: [
          {
            name: 'Y',
            type: 'line',
            symbol: 'none',
            data: [],
          },
          {
            name: 'Base',
            type: 'line',
            data: [
              [0, 0],
              [1, 1],
            ],
          },
        ],
      },
      jm_ks: {
        title: {
          text: 'KS检验',
          subtext: 'JM模型',
          x: 'center',
        },
        legend: {
          x: 'left',
          data: ['Real', 'Predict', 'Base'],
        },
        toolbox: {
          feature: {
            saveAsImage: {},
          },
        },
        xAxis: {
          type: 'value',
        },
        yAxis: {
          type: 'value',
        },
        series: [
          {
            name: 'Real',
            type: 'line',
            symbol: 'none',
            data: [],
          },
          {
            name: 'Predict',
            type: 'line',
            symbol: 'none',
            data: [],
          },
          {
            name: 'Base',
            type: 'line',
            data: [
              [0, 0],
              [1, 1],
            ],
          },
        ],
      },
      go_u: {
        title: {
          text: 'U图',
          subtext: 'Go模型',
          x: 'center',
        },
        legend: {
          x: 'left',
          data: ['U', 'Base'],
        },
        toolbox: {
          feature: {
            saveAsImage: {},
          },
        },
        xAxis: {
          type: 'value',
        },
        yAxis: {
          type: 'value',
        },
        series: [
          {
            name: 'U',
            type: 'line',
            symbol: 'none',
            data: [],
          },
          {
            name: 'Base',
            type: 'line',
            data: [
              [0, 0],
              [1, 1],
            ],
          },
        ],
      },
      go_y: {
        title: {
          text: 'Y图',
          subtext: 'Go模型',
          x: 'center',
        },
        legend: {
          x: 'left',
          data: ['Y', 'Base'],
        },
        toolbox: {
          feature: {
            saveAsImage: {},
          },
        },
        xAxis: {
          type: 'value',
        },
        yAxis: {
          type: 'value',
        },
        series: [
          {
            name: 'Y',
            type: 'line',
            symbol: 'none',
            data: [],
          },
          {
            name: 'Base',
            type: 'line',
            data: [
              [0, 0],
              [1, 1],
            ],
          },
        ],
      },
      go_ks: {
        title: {
          text: 'KS检验',
          subtext: 'GO模型',
          x: 'center',
        },
        legend: {
          x: 'left',
          data: ['Real', 'Predict', 'Base'],
        },
        toolbox: {
          feature: {
            saveAsImage: {},
          },
        },
        xAxis: {
          type: 'value',
        },
        yAxis: {
          type: 'value',
        },
        series: [
          {
            name: 'Real',
            type: 'line',
            symbol: 'none',
            data: [],
          },
          {
            name: 'Predict',
            type: 'line',
            symbol: 'none',
            data: [],
          },
          {
            name: 'Base',
            type: 'line',
            data: [
              [0, 0],
              [1, 1],
            ],
          },
        ],
      },
      mo_u: {
        title: {
          text: 'U图',
          subtext: 'MO模型',
          x: 'center',
        },
        legend: {
          x: 'left',
          data: ['U', 'Base'],
        },
        toolbox: {
          feature: {
            saveAsImage: {},
          },
        },
        xAxis: {
          type: 'value',
        },
        yAxis: {
          type: 'value',
        },
        series: [
          {
            name: 'U',
            type: 'line',
            symbol: 'none',
            data: [],
          },
          {
            name: 'Base',
            type: 'line',
            data: [
              [0, 0],
              [1, 1],
            ],
          },
        ],
      },
      mo_y: {
        title: {
          text: 'Y图',
          subtext: 'MO模型',
          x: 'center',
        },
        legend: {
          x: 'left',
          data: ['Y', 'Base'],
        },
        toolbox: {
          feature: {
            saveAsImage: {},
          },
        },
        xAxis: {
          type: 'value',
        },
        yAxis: {
          type: 'value',
        },
        series: [
          {
            name: 'Y',
            type: 'line',
            symbol: 'none',
            data: [],
          },
          {
            name: 'Base',
            type: 'line',
            data: [
              [0, 0],
              [1, 1],
            ],
          },
        ],
      },
      mo_ks: {
        title: {
          text: 'KS检验',
          subtext: 'MO模型',
          x: 'center',
        },
        legend: {
          x: 'left',
          data: ['Real', 'Predict', 'Base'],
        },
        toolbox: {
          feature: {
            saveAsImage: {},
          },
        },
        xAxis: {
          type: 'value',
        },
        yAxis: {
          type: 'value',
        },
        series: [
          {
            name: 'Real',
            type: 'line',
            symbol: 'none',
            data: [],
          },
          {
            name: 'Predict',
            type: 'line',
            symbol: 'none',
            data: [],
          },
          {
            name: 'Base',
            type: 'line',
            data: [
              [0, 0],
              [1, 1],
            ],
          },
        ],
      },
      bp_g: {
        title: {
          text: '预测图',
          subtext: 'BP模型',
          x: 'center',
        },
        legend: {
          x: 'left',
          data: ['Real', 'Predict'],
        },
        toolbox: {
          feature: {
            saveAsImage: {},
          },
        },
        xAxis: {
          type: 'value',
        },
        yAxis: {
          type: 'value',
        },
        series: [
          {
            name: 'Real',
            type: 'line',
            symbol: 'none',
            data: [],
          },
          {
            name: 'Predict',
            type: 'line',
            symbol: 'none',
            data: [],
          },
        ],
      },
      bp_ks: {
        title: {
          text: 'KS检验',
          subtext: 'bp模型',
          x: 'center',
        },
        legend: {
          x: 'left',
          data: ['Real', 'Predict', 'Base'],
        },
        toolbox: {
          feature: {
            saveAsImage: {},
          },
        },
        xAxis: {
          type: 'value',
        },
        yAxis: {
          type: 'value',
        },
        series: [
          {
            name: 'Real',
            type: 'line',
            symbol: 'none',
            data: [],
          },
          {
            name: 'Predict',
            type: 'line',
            symbol: 'none',
            data: [],
          },
          {
            name: 'Base',
            type: 'line',
            data: [
              [0, 0],
              [1, 1],
            ],
          },
        ],
      },
      svm_g: {
        title: {
          text: '预测图',
          subtext: 'SVM模型',
          x: 'center',
        },
        legend: {
          x: 'left',
          data: ['Real', 'Predict'],
        },
        toolbox: {
          feature: {
            saveAsImage: {},
          },
        },
        xAxis: {
          type: 'value',
        },
        yAxis: {
          type: 'value',
        },
        series: [
          {
            name: 'Real',
            type: 'line',
            symbol: 'none',
            data: [],
          },
          {
            name: 'Predict',
            type: 'line',
            symbol: 'none',
            data: [],
          },
        ],
      },
      svm_ks: {
        title: {
          text: 'KS检验',
          subtext: 'SVM模型',
          x: 'center',
        },
        legend: {
          x: 'left',
          data: ['Real', 'Predict', 'Base'],
        },
        toolbox: {
          feature: {
            saveAsImage: {},
          },
        },
        xAxis: {
          type: 'value',
        },
        yAxis: {
          type: 'value',
        },
        series: [
          {
            name: 'Real',
            type: 'line',
            symbol: 'none',
            data: [],
          },
          {
            name: 'Predict',
            type: 'line',
            symbol: 'none',
            data: [],
          },
          {
            name: 'Base',
            type: 'line',
            data: [
              [0, 0],
              [1, 1],
            ],
          },
        ],
      },
    }
  },
  computed: {
    model() {
      return this.$store.state.model
    },
    name() {
      return this.$store.state.model.name
    },
  },
  async mounted() {
    const model = this.$store.state.model
    try {
      switch (model.name) {
        case 'jm': {
          const resp = await this.$api.jm(
            model.uuid,
            model.params.ex,
            model.params.ey
          )
          this.jm_u.series[0].data = resp.u
          this.jm_y.series[0].data = resp.y
          console.log(resp.y)
          this.jm_ks.series[0].data = resp.real
          this.jm_ks.series[1].data = resp.predict
          this.jm = resp
          break
        }
        case 'go': {
          const resp = await this.$api.go(model.uuid, model.params.zeta)
          this.go_u.series[0].data = resp.u
          this.go_y.series[0].data = resp.y
          this.go_ks.series[0].data = resp.real
          this.go_ks.series[1].data = resp.predict
          this.go = resp
          break
        }
        case 'mo': {
          const resp = await this.$api.mo(
            model.uuid,
            model.params.lambda,
            model.params.zeta
          )
          this.mo_u.series[0].data = resp.u
          this.mo_y.series[0].data = resp.y
          this.mo_ks.series[0].data = resp.real
          this.mo_ks.series[1].data = resp.predict
          this.mo = resp
          break
        }
        case 'bp': {
          const resp = await this.$api.bp(
            model.uuid,
            model.params.learnrate,
            model.params.re,
            model.params.maxl
          )
          this.bp_g.series[0].data = resp.u
          this.bp_g.series[1].data = resp.y
          this.bp_ks.series[0].data = resp.real
          this.bp_ks.series[1].data = resp.predict
          this.bp = resp
          break
        }
        case 'svm': {
          const resp = await this.$api.svm(model.uuid)
          this.svm_g.series[0].data = resp.u
          this.svm_g.series[1].data = resp.y
          this.svm_ks.series[0].data = resp.real
          this.svm_ks.series[1].data = resp.predict
          this.svm = resp
          break
        }
        default:
          break
      }
    } catch (error) {}
  },
}
</script>

<style scoped>
#result {
  /* display: flex;
  justify-content: center;
  justify-items: center; */
}

.graph {
  display: flex;
  justify-content: center;
  justify-items: center;
  flex-wrap: wrap;
}
</style>
