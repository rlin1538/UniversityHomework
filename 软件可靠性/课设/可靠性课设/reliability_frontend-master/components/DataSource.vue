<template>
  <div id="source">
    <Tabs value="file">
      <TabPane label="手动输入数据" name="input">
        <Input
          v-model="text"
          type="textarea"
          :rows="4"
          placeholder="请输入软件失效数据"
        />
        <Button v-if="text" type="primary" @click="uploadText()">
          点击提交
        </Button>
      </TabPane>
      <TabPane label="上传数据文件" name="file">
        <p>请上传txt, csv或xls文件</p>
        <Upload
          action="/"
          type="drag"
          :before-upload="handleUpload"
          :accept="'.txt,.csv,.xls,.xlsx'"
          :format="['txt', 'csv', 'xls', 'xlsx']"
        >
          <div style="padding: 20px 0">
            <Icon
              type="ios-cloud-upload"
              size="52"
              style="color: #3399ff"
            ></Icon>
            <p>点击或拖拽文件</p>
          </div>
        </Upload>
        <Button v-if="file" type="primary" @click="upload()">点击上传</Button>
      </TabPane>
    </Tabs>
    <Table v-if="data.length > 0" :columns="col" :data="data"></Table>
  </div>
</template>

<script>
export default {
  data() {
    return {
      file: null,
      uuid: '',
      text: '',
      db: {
        type: '',
        host: '',
        port: '',
        database: '',
        table: '',
        username: '',
        password: '',
      },
      col: [
        { title: '失效次数', key: 'times' },
        { title: '失效间隔', key: 'gaps' },
      ],
      data: [],
    }
  },
  methods: {
    handleUpload(file) {
      const form = new FormData()
      form.append('file', file)
      this.file = form
      return false
    },
    async upload() {
      try {
        const res = await this.$api.upload(this.file)
        this.uuid = res.uuid
        this.data = res.data
        this.$store.commit('updateUUID', res.uuid)
        this.$Message.success('文件上传成功！')
      } catch (error) {
        this.$Message.error(
          '文件上传失败！ 错误代码：' + error.response.data.message
        )
      }
    },
    async uploadText() {
      try {
        const res = await this.$api.uploadText({ text: this.text })
        this.uuid = res.uuid
        this.data = res.data
        this.$store.commit('updateUUID', res.uuid)
        this.$Message.success('数据提交成功！')
      } catch (error) {
        this.$Message.error(
          '数据提交失败！ 错误代码：' + error.response.data.message
        )
      }
    },
  },
}
</script>

<style scoped>
#source {
}

#db {
  display: flex;
  justify-content: center;
  justify-items: center;
}

#form {
  width: 50%;
}
</style>
