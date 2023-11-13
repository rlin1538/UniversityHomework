<template>
  <div class="welcome">
    <h1>欢迎来到软件可靠性数据分析系统！</h1>
    <br />
    <br />
    <Button
      id="in"
      type="info"
      shape="circle"
      icon="ios-arrow-dropright"
      long
      @click="$router.push('model')"
      >进入系统</Button
    >
  </div>
</template>

<script>
export default {
  auth: false,
  components: {
    // Logo,
  },
}
</script>

<style scoped>
.welcome {
  margin-top: 350px;
  text-align: center;
}
#in {
  text-align: center;
  width: 200px;
}
</style>
