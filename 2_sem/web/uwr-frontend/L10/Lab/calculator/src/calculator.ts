import { evaluate } from "mathjs";
export function calculateExpresion(expression: string): string {
  return evaluate(expression).toString();
}
