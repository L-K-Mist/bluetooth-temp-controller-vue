<script>
function randomScalingFactor() {
  return (Math.random() > 0.5 ? 1.0 : -1.0) * Math.round(Math.random() * 100);
}
import { Line } from "vue-chartjs";

import "chartjs-plugin-streaming";
import bluetooth from "@/helpers/bluetooth";
export default {
  extends: Line,
  mounted() {
    this.renderChart(
      {
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
      },
      {
        responsive: true,
        maintainAspectRatio: false,
        scales: {
          xAxes: [
            {
              type: "realtime",
              realtime: {
                duration: 20000,
                refresh: 1000,
                delay: 2000,
                onRefresh: this.onRefresh,
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
                max: 40,
                min: 20,
              },
            },
          ],
        },
      }
    );
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
