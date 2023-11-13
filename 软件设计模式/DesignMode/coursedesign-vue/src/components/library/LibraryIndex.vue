<template>
  <el-container>
    <el-aside style="width: 200px;margin-top: 20px">
      <switch></switch>
      <el-card>
        <side-menu @indexSelect="listByCategory" ref="sideMenu"></side-menu>
      </el-card>
    </el-aside>
      <el-main>
        <el-card style="margin-left: 10px;;width: auto">
          <courses class="courses-area" ref="coursesArea"></courses>
        </el-card>
    </el-main>
  </el-container>
</template>

<script>
import SideMenu from './SideMenu'
import Courses from './Courses'
export default {
  name: 'LibraryIndex',
  components: {Courses, SideMenu},
  comments: {SideMenu, Courses},
  methods: {
    listByCategory () {
      var _this = this
      var cid = this.$refs.sideMenu.cid
      var url = 'categories/' + cid + '/courses'
      // url构造方式
      this.$axios.get(url).then(resp => {
        if (resp && resp.status === 200) {
          _this.$refs.coursesArea.courses = resp.data
        }
      })
      // 调axios向后端发送有参数的get请求
    }
  }
}
</script>

<style scoped>
.courses-area {
  width: auto;
  margin-left: auto;
  margin-right: auto;
}

</style>
