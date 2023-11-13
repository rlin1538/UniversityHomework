const state = () => ({
  model: {
    name: 'jm',
    show: false,
    uuid: '',
    params: {},
  },
})

const getters = {
  dataUUID: (state) => state.model.uuid,
}

const mutations = {
  updateUUID(state, uuid) {
    state.model.uuid = uuid
  },
  updateName(state, name) {
    state.model.name = name
  },
  updateParams(state, params) {
    state.model.params = params
  },
  updateShow(state, show) {
    state.model.show = show
  },
}

export { state, getters, mutations }
