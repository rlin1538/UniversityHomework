<template>
  <div>
    <i class="el-icon-circle-plus-outline"  @click="dialogFormVisible = true"></i>
    <el-dialog
      title="添加/修改课程"
      :visible.sync="dialogFormVisible"
      @close="clear">
      <el-form v-model="form" style="text-align: left" ref="dataForm">
        <el-form-item label="课程代码" :label-width="formLabelWidth" prop="code">
          <el-input v-model="form.code" autocomplete="off"></el-input>
        </el-form-item>
        <el-form-item label="课程名称" :label-width="formLabelWidth" prop="name">
          <el-input v-model="form.name" autocomplete="off"></el-input>
        </el-form-item>
        <el-form-item label="学分" :label-width="formLabelWidth" prop="credit">
          <el-input v-model="form.credit" autocomplete="off"></el-input>
        </el-form-item>
        <el-form-item label="修读学期" :label-width="formLabelWidth" prop="term">
          <el-select v-model="form.term" placeholder="请选择学期">
            <el-option label="大一上" value="1"></el-option>
            <el-option label="大一下" value="2"></el-option>
            <el-option label="大二上" value="3"></el-option>
            <el-option label="大二下" value="4"></el-option>
            <el-option label="大三上" value="5"></el-option>
            <el-option label="大三下" value="6"></el-option>
            <el-option label="大四上" value="7"></el-option>
            <el-option label="大四下" value="8"></el-option>
          </el-select>
        </el-form-item>
        <el-form-item label="修读状态" :label-width="formLabelWidth" prop="state">
          <el-select v-model="form.state" placeholder="请选择类别">
            <el-option label="已修" value="已修"></el-option>
            <el-option label="未修" value="未修"></el-option>
          </el-select>
        </el-form-item>
        <el-form-item label="备注" :label-width="formLabelWidth" prop="abs">
          <el-input type="textarea" v-model="form.abs" autocomplete="off"></el-input>
        </el-form-item>
        <el-form-item label="课程类别" :label-width="formLabelWidth" prop="uid">
          <el-select v-model="form.category.id" placeholder="请选择类别">
            <el-option label="通识必修课" value="1"></el-option>
            <el-option label="国防军事课" value="2"></el-option>
            <el-option label="文化素质课" value="3"></el-option>
            <el-option label="学科基础课" value="4"></el-option>
            <el-option label="专业必修课" value="5"></el-option>
            <el-option label="专业选修课" value="6"></el-option>
            <el-option label="实践必修课" value="7"></el-option>
            <el-option label="实践选修课" value="8"></el-option>
          </el-select>
        </el-form-item>
        <el-form-item prop="id" style="height: 0">
          <el-input type="hidden" v-model="form.id" autocomplete="off"></el-input>
        </el-form-item>
      </el-form>
      <div slot="footer" class="dialog-footer">
        <el-button @click="dialogFormVisible = false">取 消</el-button>
        <el-button type="primary" @click="onSubmit">确 定</el-button>
      </div>
    </el-dialog>
  </div>
</template>

<script>
export default {
  name: 'EditForm',
  data () {
    return {
      dialogFormVisible: false,
      // 设置为false初始不显示
      form: {
        id: '',
        code: '',
        name: '',
        credit: '',
        state: '',
        term: '',
        abs: '',
        category: {
          id: '',
          name: ''
        }
      },
      formLabelWidth: '120px'
    }
  },
  methods: {
    clear () {
      this.form = {
        id: '',
        code: '',
        name: '',
        credit: '',
        state: '',
        term: '',
        abs: '',
        category: {
          id: '',
          name: ''
        }
      }
      // 清空表单
    },
    onSubmit () {
      this.$axios
        .post('/courses', {
          id: this.form.id,
          code: this.form.code,
          name: this.form.name,
          credit: this.form.credit,
          state: this.form.state,
          term: this.form.term,
          abs: this.form.abs,
          category: this.form.category
        }).then(resp => {
          if (resp && resp.status === 200) {
            this.dialogFormVisible = false
            this.$emit('onSubmit')
          }
        })
    }
  }
}
</script>

<style scoped>
.el-icon-circle-plus-outline {
  margin: 50px 0 0 20px;
  font-size: 100px;
  float: left;
  cursor: pointer;
}
</style>
