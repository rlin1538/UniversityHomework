import { Message } from 'view-design'

export default ({ $axios, app, redirect }, inject) => {
  $axios.onError((error) => {
    const code = parseInt(error.response && error.response.status)
    switch (code) {
      case 504:
        Message.error('后端连接异常')
        redirect('/')
        break
      default:
        break
    }
  })
}
