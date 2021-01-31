import Vue from "vue";
import Vuex from "vuex";
import bluetooth from "./bluetooth";

const isDevMode = process.env.NODE_ENV === "development";

Vue.use(Vuex);

export default new Vuex.Store({
  state: {
    isDevMode,
  },
  modules: {
    bluetooth,
  },
});
