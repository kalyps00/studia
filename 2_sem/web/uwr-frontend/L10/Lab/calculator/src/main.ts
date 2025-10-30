import "./style.css";
import { calculateExpresion } from "./calculator";
const display = document.querySelector("#calculator__display") as HTMLInputElement;
const buttons = document.querySelector("#calculator__buttons") as HTMLDivElement;

let expression: string = "";
buttons.addEventListener("click", (event) => {
  const target = event.target as HTMLButtonElement;
  if (!target.matches(".calculator__button")) return;

  const value = target.textContent as string;

  switch (value) {
    case "DEL":
      expression = expression.slice(0, -1);
      display.value = expression;
      break;
    case "CE":
      expression = "";
      display.value = "";
      break;
    case "=":
      try {
        const result = calculateExpresion(expression);
        display.value = result;
        expression = result;
      } catch (error) {
        display.value = "Error";
        expression = "";
      }
      break;
    default:
      expression += value;
      display.value = expression;
  }
});
