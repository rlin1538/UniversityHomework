<template>
  <div class="model">
    <Card class="card">
      <p slot="title" style="text-align: center">
        <Icon type="ios-bulb-outline" />
        <span>软件可靠性数据分析步骤</span>
      </p>
      <Steps :current="current">
        <Step title="上传数据" content="上传可靠性数据文件"></Step>
        <Step title="选择模型" content="选择对应的可靠性模型"></Step>
        <Step title="查看结果" content="查看可靠性计算结果"></Step>
      </Steps>
      <Divider />
      <div id="action">
        <DataSource v-if="current === 0"></DataSource>
        <ModelList v-if="current === 1"></ModelList>
        <Result v-if="current === 2"></Result>
      </div>
      <Divider />
      <div id="controller">
        <Button type="primary" :disabled="previous" @click="current--">
          上一步
        </Button>
        <Button type="primary" :disabled="next" @click="current++">
          下一步
        </Button>
      </div>
    </Card>
  </div>
</template>

<script>
import { mapGetters } from 'vuex'
import DataSource from '~/components/DataSource'
import ModelList from '~/components/ModelList'
import Result from '~/components/Result'

export default {
  components: {
    DataSource,
    ModelList,
    Result,
  },
  data() {
    return {
      current: 0,
    }
  },
  computed: {
    ...mapGetters({
      uuid: 'dataUUID',
    }),
    previous() {
      return this.current <= 0
    },
    next() {
      // eslint-disable-next-line eqeqeq
      if (this.current != 1) return this.current > 0 || !this.nextPage
      else return !this.$store.state.model.show
    },
    nextPage() {
      return this.uuid
    },
    show() {
      return this.$store.state.model.show
    },
  },
}
</script>

<style scoped>
.model {
  margin: auto;
  width: 80vw;
}
.card {
  margin-top: 60px;
}
#controller {
  text-align: right;
}
</style>
