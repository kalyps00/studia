import isEven from "is-even";

export function setupCounter(
  element: HTMLButtonElement,
  evenElement: HTMLSpanElement
) {
  let counter = 0;
  const setCounter = (count: number) => {
    counter = count;
    element.innerHTML = `count is ${counter}`;
    evenElement.innerHTML = `count is ${isEven(counter) ? "even" : "odd"}`;
  };
  element.addEventListener("click", () => setCounter(counter + 1));
  setCounter(0);
}
