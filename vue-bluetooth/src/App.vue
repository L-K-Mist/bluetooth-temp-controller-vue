<template>
  <v-app>
    <v-app-bar app color="primary" dark>
      Web Bluetooth Temp Controller
      <v-spacer></v-spacer>
      <v-badge :value="isConnected" color="success" icon="mdi-check" overlap>
        <v-btn class="blue--text text--darken-4" color="accent" @click="start"
          ><v-icon class="mr-3">mdi-bluetooth</v-icon>
          {{ isConnected ? "Connected" : "See Devices" }}</v-btn
        >
      </v-badge>
    </v-app-bar>
    <v-main>
      <v-container>
        <v-btn @click="testSend">Test send receive style</v-btn>
        <router-view></router-view>
      </v-container>
    </v-main>
  </v-app>
</template>

<script>
import bluetooth from "@/helpers/bluetooth";
export default {
  data: () => ({
    message: null,
    characteristic: null,
    count: 0,
    command: "",
  }),
  mounted() {
    // this.start(); // This just demonstrates that start only works if triggered by a user action.
  },
  computed: {
    isConnected() {
      return this.$store.state.bluetooth.isConnected;
    },
  },
  methods: {
    async testSend() {
      try {
        const message = "echo,testSend";
        let enc = new TextEncoder(); // By default this encodes to utf-8
        let decoder = new TextDecoder("utf-8");
        // Why the <opening and closing> characters?
        // Went with this guy's example 3 for the reasons he mentions: https://forum.arduino.cc/index.php?topic=396450.0
        if (!this.characteristic) {
          throw "Not ready for sending yet.";
        }

        await this.characteristic
          .writeValue(enc.encode(`<${message}>`))
          .catch((error) => {
            console.log("Let's update state to unconnected");
          });
        let value1;
        let fromArduino;

        setTimeout(async () => {
          value1 = await this.characteristic.readValue();
          fromArduino = await decoder.decode(value1);
          debugger;
        }, 1000);
      } catch (error) {
        console.log("testSend - error", error);
      }
    },
    async start() {
      try {
        this.characteristic = await bluetooth.initialize({
          // Sticking with the defaults
        });
        await this.characteristic.startNotifications();
        // await this.characteristic.addEventListener(
        //   "characteristicvaluechanged",
        //   this.onChange
        // );

        console.log("Notifications have been started: ", this.characteristic);
        bluetooth.send("Hi from web"); // Arduino is expecting this message as part of the initial handshake.
      } catch (error) {
        console.error(error.message);
      }
    },
    onChange(event) {
      const value = event.target.value;
      this.$store.dispatch("bluetooth/decodeMessage", value);
    },
    onDisconnected() {
      // TODO someday: Add automatic reconnect like: https://googlechrome.github.io/samples/web-bluetooth/automatic-reconnect-async-await.html
      this.$store.dispatch("bluetooth/isConnected", false);
    },
  },
};
</script>
<style scoped>
.button {
  color: navy;
}
</style>
