<template>
  <div id="params">
    <div id="list">
      <div v-if="name === 'jm'">
        <h1>JM模型</h1>
        <label>精度ex</label>
        <Input
          v-model="params.ex"
          placeholder="精度ex"
          type="number"
          clearable
        ></Input>
        <label>精度ey</label>
        <Input
          v-model="params.ey"
          placeholder="精度ey"
          type="number"
          clearable
        ></Input>
      </div>
      <div v-if="name === 'go'">
        <h1>GO模型</h1>
        <label>精度zeta</label>
        <Input
          v-model="params.zeta"
          placeholder="精度zeta"
          type="number"
          clearable
        ></Input>
      </div>
      <div v-if="name === 'mo'">
        <h1>MO模型</h1>
        <label>精度lambda</label>
        <Input
          v-model="params.lambda"
          placeholder="精度lambda"
          type="number"
          clearable
        ></Input>
        <label>精度zeta</label>
        <Input
          v-model="params.zeta"
          placeholder="精度zeta"
          type="number"
          clearable
        ></Input>
      </div>
      <div v-if="name === 'bp'">
        <h1>BP模型</h1>
        <label>学习系数</label>
        <Input
          v-model="params.learnrate"
          placeholder="学习系数"
          type="number"
          clearable
        ></Input>
        <label>重构维数</label>
        <Input
          v-model="params.re"
          placeholder="重构维数"
          type="number"
          clearable
        ></Input>
        <label>训练代数</label>
        <Input
          v-model="params.maxl"
          placeholder="训练代数"
          type="number"
          clearable
        ></Input>
      </div>
      <div v-if="name === 'svm'">
        <h1>SVM模型</h1>
        <label>核函数</label>
        <Select v-model="kernel">
          <Option
            v-for="item in kernels"
            :key="item.value"
            :value="item.value"
            >{{ item.value }}</Option
          >
        </Select>
      </div>
      <Button type="primary" @click="submit()">提交</Button>
    </div>
  </div>
</template>

<script>
export default {
  data() {
    return {
      params: Object.assign({}, this.$store.state.model.params),
      kernel: '',
      kernels: [
        {
          value: 'Sigmoid函数',
        },
        {
          value: '径向基函数',
        },
        {
          value: '多项式函数',
        },
      ],
    }
  },
  computed: {
    name() {
      return this.$store.state.model.name
    },
  },
  methods: {
    submit() {
      this.$store.commit('updateParams', Object.assign({}, this.params))
      this.$store.commit('updateShow', true)
    },
  },
  // watch: {
  //   params: {
  //     handler(newparams, oldparams) {
  //       this.$store.commit('updateParams', Object.assign({}, this.params))
  //     },
  //     deep: true,
  //   },
  // },
  // beforeDestroy() {
  //   this.$store.commit('updateParams', Object.assign({}, this.params))
  // },
}
</script>

<style scoped>
#params {
  display: flex;
  justify-content: center;
  justify-items: center;
}
</style>
