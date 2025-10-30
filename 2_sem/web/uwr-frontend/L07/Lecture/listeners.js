const button = document.getElementById("highlight-button");
const secondParagraph = document.getElementById("second-paragraph");
const form = document.getElementById("form");

console.log(button);

button.addEventListener("click", function (event) {
  console.log(event);
  secondParagraph.classList.toggle("highlight");
});

form.addEventListener("submit", function (event) {
  event.preventDefault();
  const formData = new FormData(event.target);

  console.log(formData.get("name"));
  /*   console.log(event);
  event.preventDefault();
  const input = document.getElementById("name");
  const value = input.value;
  console.log(value);
  input.value = ""; */
});
