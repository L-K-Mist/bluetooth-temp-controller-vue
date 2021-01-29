<script>
function randomScalingFactor() {
  return (Math.random() > 0.5 ? 1.0 : -1.0) * Math.round(Math.random() * 100);
}
import { Line } from "vue-chartjs";

import "chartjs-plugin-streaming";
import bluetooth from "@/helpers/bluetooth";
export default {
  extends: Line,
  props: {
    maxTemp: {
      type: Number,
      default: 40,
    },
    minTemp: {
      type: Number,
      default: 20,
    },
  },
  watch: {
    maxTemp(newVal) {
      if (newVal >= 10) {
        this.renderChart(this.chartData, this.chartOptions);
      }
    },
  },
  computed: {
    chartData() {
      return {
        datasets: [
          {
            label: "Dataset 1 (linear interpolation)",
            fill: false,
            lineTension: 0,
            data: [],
          },
          {
            label: "Dataset 2 (cubic interpolation)",
            fill: false,
            cubicInterpolationMode: "default",
            data: [],
          },
        ],
      };
    },
    chartOptions() {
      return {
        responsive: true,
        maintainAspectRatio: false,
        scales: {
          xAxes: [
            {
              type: "realtime",
              realtime: {
                duration: 40000,
                refresh: 4000,
                delay: 4000,
                onRefresh: this.onRefresh,
              },
              ticks: {
                steps: 1500,
                autoskip: true,
                autoSkipPadding: 30,
              },
            },
          ],
          yAxes: [
            {
              id: "tempC",
              type: "linear",
              position: "left",
              ticks: {
                display: true,
                beginsAtZero: true,
                steps: 5,
                max: this.maxTemp,
                min: this.minTemp,
              },
            },
          ],
        },
      };
    },
  },
  mounted() {
    console.log("this: ", this);
    this.renderChart(this.chartData, this.chartOptions);
  },
  methods: {
    onRefresh(chart) {
      bluetooth.send("getTemp");
      const temperature = this.$store.state.bluetooth.message;
      console.log("onRefresh - temperature", temperature);
      chart.config.data.datasets[1].data.push({
        x: Date.now(),
        y: temperature,
      });
    },
  },
};
</script>
