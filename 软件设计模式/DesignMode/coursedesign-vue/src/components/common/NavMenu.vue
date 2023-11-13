<template>
  <el-menu
    :default-active="'/library'"
    router
    mode="horizontal"
    active-text-color="blue">
    <el-menu-item index="/index">主页</el-menu-item>
    <el-menu-item index="/library" >管理</el-menu-item>
    <span style="position: absolute;padding-top: 20px;right: 43%;font-size: 20px;font-weight: bold">
      学生培养计划管理系统
    </span>
    <div style="position: absolute;padding-top: 20px;align-items: center;right: 5%">
      <el-button size="small" round icon="el-icon-setting">admin</el-button>
    </div>
  </el-menu>
</template>

<script>
export default {
  name: 'NavMenu'
}
</script>

<style scoped>
span {
  pointer-events: none;
}
</style>
