export default ({ $axios }, inject) => {
  const api = {
    register(userinfo) {
      return $axios.$post('/auth/register', userinfo)
    },
    upload(file) {
      return $axios.$post('/sourceData/upload', file)
    },
    uploadText(text) {
      return $axios.$post('/sourceData/text', text)
    },
    fromDB(db) {
      return $axios.$post('/sourceData/db', db)
    },
    jm(uuid, ex, ey) {
      return $axios.$get(`/model/jm/${uuid}`, { params: { ex, ey } })
    },
    go(uuid, zeta) {
      return $axios.$get(`/model/go/${uuid}`, { params: { zeta } })
    },
    mo(uuid, lambda, zeta) {
      return $axios.$get(`/model/mo/${uuid}`, { params: { lambda, zeta } })
    },
    bp(uuid, learnrate, re, maxl) {
      return $axios.$get(`/model/bp/${uuid}`, {
        params: { learnrate, re, maxl },
      })
    },
    svm(uuid) {
      return $axios.$get(`/model/svm/${uuid}`)
    },
  }
  inject('api', api)
}
