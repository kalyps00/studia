# Task: Calculator (10 points)

Your task in this assignment is to create a simple calculator using **TypeScript** and the [mathjs](https://www.npmjs.com/package/mathjs) library. You will use the [Vite](https://vite.dev/) bundler to set up and build the project.

You can find an example solution [here](./example.gif).

## Requirements

The following requirements are **not** presented as a step-by-step guide. In particular, you are advised to first set up the environment (add the bundler and ESLint support), and only then begin implementing functionality.

1. Your calculator must be written in TypeScript using modern conventions.
   1. The TypeScript code should be split into at least two separate files.
2. Your calculator must include styling that follows well-known CSS conventions (e.g., BEM) to improve maintainability and readability.
   1. Your calculator **does not** need to be responsive.
3. Your calculator must be functional:
   1. It must allow entering any formula using numbers, multiplication, division, addition, subtraction, and decimal points.
   1. It must allow deleting the last character and clearing the entire input.
   1. It must allow evaluating the formula using the `=` button.
   1. In case of an error, the display must show the text `Error`.
4. The application must use the [Vite](https://vite.dev/) bundler.
   1. **This requirement is critical.** An application that does not use a bundler, or in which the bundler does not produce a production-ready build, **will not be accepted**.
5. Change the default port used by the development server by modifying the configuration.
   1. This must be done using a `vite.config.ts` file, **not** by passing CLI arguments.
