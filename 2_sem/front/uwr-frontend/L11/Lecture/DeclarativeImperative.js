const list = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15];

// Wybierz liczby parzyste z listy

// Imperatywne

const evenNumbersImperative = [];

for (let i = 0; i < list.length; i++) {
  if (list[i] % 2 === 0) {
    evenNumbersImperative.push(list[i]);
  }
}
console.log(evenNumbersImperative); // [2, 4, 6, 8, 10, 12, 14]

// Deklaratywne

const evenNumbersDeclarative = list.filter((number) => number % 2 === 0);

// Counter

// Imperatywne

const counterElement = document.getElementById("counter");
const counterButton = document.getElementById("counter-button");

counterButton.addEventListener("click", () => {
  counterElement.innerText = Number(counterElement.innerText) + 1;
});

// Deklaratywne

`
<span>${counter}</span>
<button onClick=${counter + 1}>Click me</button>
`;
