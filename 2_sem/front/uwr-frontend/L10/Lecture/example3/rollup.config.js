import typescript from "@rollup/plugin-typescript";

export default {
  input: "example.ts",
  output: {
    file: "output/example.bundle.js",
  },
  plugins: [typescript()],
};
