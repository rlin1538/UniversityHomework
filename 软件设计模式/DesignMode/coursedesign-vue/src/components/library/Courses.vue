<template>
  <div>
    <el-row style="height: 840px;width: auto">
      <search-bar @onSearch="searchResult" ref="searchBar"></search-bar>
      <el-table
        :data="courses"
        style="width: 100%"
        fit>
        <el-table-column
          label="课程号"
          width="180">
          <template slot-scope="scope">
            <span style="margin-left: 10px">{{ scope.row.code }}</span>
          </template>
        </el-table-column>
        <el-table-column
          label="课程名"
          width="250">
          <template slot-scope="scope">
            <el-popover trigger="hover" placement="top" open-delay="500">
              <p>备注: {{ scope.row.abs }}</p>
              <div slot="reference" class="name-wrapper">
                <el-tag size="medium">{{ scope.row.name }}</el-tag>
              </div>
            </el-popover>
          </template>
        </el-table-column>
        <el-table-column
          label="课程类别"
          width="150">
          <template slot-scope="scope">
            <span style="margin-left: 10px">{{ scope.row.category.name }}</span>
          </template>
        </el-table-column>
        <el-table-column
          label="学分"
          width="100">
          <template slot-scope="scope">
            <span style="margin-left: 10px">{{ scope.row.credit }}</span>
          </template>
        </el-table-column>
        <el-table-column
          label="修读学期"
          width="100">
          <template slot-scope="scope">
            <span style="margin-left: 10px">{{ scope.row.term }}</span>
          </template>
        </el-table-column>
        <el-table-column
          label="修读状态"
          width="100">
          <template slot-scope="scope">
            <span style="margin-left: 10px">{{ scope.row.state }}</span>
          </template>
        </el-table-column>
        <el-table-column label="操作" fixed="right">
          <template slot-scope="scope">
            <el-button
              size="mini"
              @click="editCourse(scope.row)">编辑</el-button>
            <el-button
              size="mini"
              type="danger"
              @click="deleteCourse(scope.row.id)">删除</el-button>
          </template>
        </el-table-column>
      </el-table>
      <edit-form @onSubmit="loadCourses()" ref="edit"></edit-form>
    </el-row>
    <el-row>
      <el-pagination
        @current-change="handleCurrentChange"
        :current-page="currentPage"
        :page-size="pagesize"
        :total="courses.length">
      </el-pagination>
    </el-row>
  </div>
</template>

<script>
import EditForm from './EditForm'
import SearchBar from './SearchBar'
export default {
  name: 'Courses',
  components: {EditForm, SearchBar},
  data () {
    return {
      courses: [],
      currentPage: 1,
      pagesize: 17
    }
  },
  mounted: function () {
    this.loadCourses()
    // 钩子函数，打开页面时触发代码进行发送请求并渲染本页面
  },
  methods: {
    loadCourses () {
      var _this = this
      this.$axios.get('/courses').then(resp => {
        if (resp && resp.status === 200) {
          _this.courses = resp.data
        }
      })
      // 利用axios发送一个get请求，后端返回后把data更新为后端传来的数据
    },
    handleCurrentChange: function (currentPage) {
      this.currentPage = currentPage
      console.log(this.currentPage)
    },
    searchResult () {
      var _this = this
      this.$axios
        .get('/search?keywords=' + this.$refs.searchBar.keywords, {
        }).then(resp => {
          if (resp && resp.status === 200) {
            _this.courses = resp.data
          }
        })
    },
    deleteCourse (id) {
      this.$confirm('此操作将永久删除该课程, 是否继续?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      }).then(() => {
        this.$axios
          .post('/delete', {id: id}).then(resp => {
            if (resp && resp.status === 200) {
              this.loadCourses()
            }
          })
      }
      ).catch(() => {
        this.$message({
          type: 'info',
          message: '已取消删除'
        })
      })
      // alert(id)
    },
    editCourse (item) {
      this.$refs.edit.dialogFormVisible = true
      this.$refs.edit.form = {
        id: item.id,
        code: item.code,
        name: item.name,
        credit: item.credit,
        state: item.state,
        term: item.term,
        abs: item.abs,
        category: {
          id: item.category.id.toString(),
          name: item.category.name
        }
      }
    }
  }

}
</script>

<style scoped>

img {
  width: 115px;
  height: 172px;
  /*margin: 0 auto;*/
}

a {
  text-decoration: none;
}

a:link, a:visited, a:focus {
  color: #3377aa;
}
</style>
