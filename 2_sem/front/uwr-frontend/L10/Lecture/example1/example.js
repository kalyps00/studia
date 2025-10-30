const increaseButtonElement = document.getElementById("increase");
const decreaseButtonElement = document.getElementById("decrease");
const counterElement = document.getElementById("counter");

counterElement.innerText = 0;

const handleClick = (action) => {
  const currentValue = +counterElement.innerText;
  const newValue = handleCounter(currentValue, action);
  counterElement.innerText = newValue;
};

increaseButtonElement.addEventListener("click", () => {
  handleClick("increment");
});

decreaseButtonElement.addEventListener("click", () => {
  handleClick("decrement");
});

handleClick("increment");
handleClick("increment");
handleClick("increment");
