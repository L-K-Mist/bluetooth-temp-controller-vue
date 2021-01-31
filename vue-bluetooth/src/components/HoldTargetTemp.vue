<template>
  <div>
    <v-row wrap>
      <v-slider
        class="generic-slider"
        label="Target Temperature"
        v-model="data.targetTemp"
        @change="updateAll"
      >
        <template v-slot:append>
          <v-text-field
            v-model="data.targetTemp"
            ticks
            tick-size="4"
            class="mt-0 pt-0"
            type="number"
            style="width: 60px"
            suffix="°C"
            @input="updateAll"
          >
          </v-text-field>
        </template>
      </v-slider>
    </v-row>
    <v-row wrap>
      <v-slider
        class="generic-slider"
        label="Hold for"
        v-model="data.numberOfTimeUnits"
        @change="updateAll"
      >
        <template v-slot:append>
          <v-text-field
            v-model="data.numberOfTimeUnits"
            ticks
            tick-size="4"
            class="mt-0 pt-0"
            type="number"
            style="width: 80px"
            @input="updateAll"
          >
          </v-text-field>
        </template>
      </v-slider>

      <v-select
        class="time-field"
        v-model="data.timeUnit"
        :items="timeUnits"
        label=""
        @change="updateAll"
      ></v-select>
    </v-row>
  </div>
</template>

<script>
export default {
  props: {
    value: {
      type: Object,
      required: true,
    },
  },
  data() {
    return {
      timeUnits: ["seconds", "minutes", "hours"],
      data: this.value,
    };
  },
  computed: {
    timeWithUnits() {
      return this.timeUnits.map((unit) => `${this.numberOfTimeUnits} ${unit}`);
    },
    millisecondsToHold() {
      const { numberOfTimeUnits, timeUnit } = this;
      const millisecondsInSecond = 1000;
      const secondsInMinute = 60;
      const minutesInHour = 60;
      if (timeUnit === "seconds") {
        return numberOfTimeUnits * millisecondsInSecond;
      }
      if (timeUnit === "minutes") {
        return numberOfTimeUnits * millisecondsInSecond * secondsInMinute;
      }
      if (timeUnit === "hours") {
        return (
          numberOfTimeUnits *
          millisecondsInSecond *
          secondsInMinute *
          minutesInHour
        );
      }
      return null; // Return null should not be reached.
    },
  },
  methods: {
    onNewTargetTemp(value) {
      console.log("onNewTargetTemp - value", value);
    },
    updateAll() {
      this.$emit("input", this.data);
    },
  },
};
</script>

<style>
.time-field {
  /* border: 2px dotted blue; */
  max-width: 150px;
}
.time-field.v-text-field {
  padding-top: 12px;
  margin-top: -8px;
}
</style>
