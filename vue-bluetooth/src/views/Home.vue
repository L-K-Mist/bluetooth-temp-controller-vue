<template>
  <div>
    <dev-mode-only id="text-send-arduino"
      ><text-send-arduino></text-send-arduino
    ></dev-mode-only>
    <v-btn @click color="success">Plus</v-btn>
    <v-card>
      <v-card-title>Temperature Controller</v-card-title>
      <br />
      <v-card-text>
        <div class="chart-container">
          <hold-target-temp
            v-for="(target, index) in tempData"
            :key="index"
            :maximumTemp="maximumTemp"
            :minimumTemp="minimumTemp"
            v-model="tempData[index]"
          ></hold-target-temp>
          <v-row wrap>
            <v-text-field
              class="tight-text-field"
              label="Max Operating Temperature"
              v-model.number="maximumTemp"
            ></v-text-field>
            <v-text-field
              class="tight-text-field"
              label="Min Operating Temperature"
              v-model.number="minimumTemp"
            ></v-text-field>
          </v-row>
          <temperature-chart
            ref="tempChart"
            :maxTemp="maximumTemp"
            :minTemp="minimumTemp"
          ></temperature-chart>
        </div>
      </v-card-text>
    </v-card>
  </div>
</template>

<script>
import bluetooth from "@/helpers/bluetooth";
import TemperatureChart from "@/components/TemperatureChart";
import DevModeOnly from "@/components/DevModeOnly";
import TextSendArduino from "@/components/TextSendArduino";
import HoldTargetTemp from "../components/HoldTargetTemp.vue";
export default {
  name: "send-string",
  components: {
    TemperatureChart,
    DevModeOnly,
    TextSendArduino,
    HoldTargetTemp,
  },
  data: () => ({
    tempData: [
      { id: 1, targetTemp: 60, timeUnit: "minutes", numberOfTimeUnits: 30 },
    ],

    minimumTemp: 20,
    maximumTemp: 110,
  }),
  watch: {
    tempData: {
      handler(val) {
        console.log("handler - val", val);
      },
      deep: true,
    },
  },
  mounted() {
    const chart = this.$refs.tempChart;
    console.log("mounted - chart", chart);
  },
};
</script>

<style>
.tight-text-field.v-text-field {
  max-width: 200px;
  margin: 0 30px;
}
#text-send-arduino {
  margin: 0 0 30px 0;
}
.generic-slider {
  max-width: 500px;
  margin: 0 30px;
}
</style>
