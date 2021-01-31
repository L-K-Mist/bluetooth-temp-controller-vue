<template>
  <div class="dev-mode" v-if="isDevMode">
    <p class="dev-guidance">
      This component is only seen in development mode, will always be hidden on
      live site.
    </p>

    <slot>
      I'm in dev mode.
    </slot>
  </div>
</template>

<script>
export default {
  computed: {
    isDevMode() {
      return process.env.NODE_ENV === "development";
    },
  },
};
</script>

<style scoped>
.dev-mode {
  border: 4px dashed rgb(3 53 148 / 0.5);
}
p.dev-guidance {
  margin: 0;
  padding-right: 10px;
  font-size: x-small;
  text-align: end;
}
</style>
