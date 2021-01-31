import bluetooth from "../helpers/bluetooth";
let decoder = new TextDecoder("utf-8");

const state = {
  message: "",
  isConnected: false,
  clearNext: false,
  tempC: 26,
};

const getters = {};

const actions = {
  decodeMessage({ commit }, message) {
    message = decoder.decode(message);
    if (message.includes("Hi from arduino")) {
      console.log(`Handshake completed. Arduino says: ${message}`);
      commit("isConnected", true);
    }
    if (message.includes("tempC")) {
      // eslint-disable-next-line
      const regex = /[^0-9\.]+/g; // Pull out the decimal
      commit("tempC", Number(message.replace(regex, "")));
    }
    commit("setMessage", message);
  },
  sendMessage({ commit }, message) {
    try {
      bluetooth.send(message);
    } catch (error) {
      if (error.includes("Not ready")) {
        commit("isConnected", false);
      }
      console.error(error);
    }
  },
  isConnected({ commit }, isConnected) {
    commit("isConnected", isConnected);
  },
};

const mutations = {
  setMessage(state, message) {
    if (state.clearNext === true) {
      state.message = "";
      state.clearNext = false;
    }
    if (message.includes("\n")) {
      // Allows arduino to send a bunch of minimessages that are assembled here into one message.
      state.clearNext = true;
    }
    state.message += message;
  },
  isConnected(state, isConnected) {
    state.isConnected = isConnected;
  },
  tempC(state, tempC) {
    state.tempC = tempC;
  },
};

export default {
  namespaced: true,
  state,
  getters,
  actions,
  mutations,
};
