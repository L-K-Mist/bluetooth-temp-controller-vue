<template>
  <div>
    <dev-mode-only id="text-send-arduino"
      ><text-send-arduino></text-send-arduino
    ></dev-mode-only>
    <v-card>
      <v-card-title>Temperature Controller</v-card-title>
      <br />
      <v-card-text>
        <div class="chart-container">
          <v-row wrap>
            <v-slider
              class="generic-slider"
              label="Target Temptarature"
              v-model="targetTemp"
              @change="onNewTargetTemp"
            >
              <template v-slot:append>
                <v-text-field
                  v-model="targetTemp"
                  ticks
                  tick-size="4"
                  class="mt-0 pt-0"
                  type="number"
                  style="width: 60px"
                  suffix="°C"
                ></v-text-field>
              </template>
            </v-slider>
          </v-row>
          <v-row wrap>
            <v-text-field
              class="tight-text-field"
              label="Max Operating Temptarature"
              v-model.number="maximumTemp"
            ></v-text-field>
            <v-text-field
              class="tight-text-field"
              label="Min Operating Temptarature"
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
export default {
  name: "send-string",
  components: {
    TemperatureChart,
    DevModeOnly,
    TextSendArduino,
  },
  data: () => ({
    targetTemp: 60,
    maximumTemp: 110,
    minimumTemp: 20,
  }),

  mounted() {
    const chart = this.$refs.tempChart;
    console.log("mounted - chart", chart);
  },
  methods: {
    onNewTargetTemp(value) {
      console.log("onNewTargetTemp - value", value);
    },
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
