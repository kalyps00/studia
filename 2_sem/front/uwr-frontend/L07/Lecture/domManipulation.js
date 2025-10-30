console.log(document.getElementById("container"));

console.log(document.getElementsByClassName("description"));
console.log(document.getElementsByTagName("p"));

console.log(document.querySelector("#container > p:nth-of-type(2)"));
console.log(document.querySelectorAll("#container > p"));
console.log(document.querySelectorAll("#container > p:nth-of-type(2)"));

const secondParagraph = document.getElementById("second-paragraph");
const container = document.getElementById("container");

console.log(secondParagraph.innerHTML);
console.log(container.innerHTML);
console.log(secondParagraph.innerText);
console.log(container.innerText);

secondParagraph.innerText = "Hello!";

/* container.innerHTML = `
  <h2>New Title</h2>
  <p>New paragraph</p>
  <p>Another paragraph</p>
`; */

secondParagraph.style.color = "red";
secondParagraph.style.backgroundColor = "blue";

const firstParagraph = document.querySelector("#container > p:first-of-type");
console.log(firstParagraph.classList);
firstParagraph.classList.add("highlight");
firstParagraph.classList.remove("highlight");

console.log(firstParagraph.classList.contains("highlight"));

firstParagraph.classList.toggle("highlight");
firstParagraph.classList.toggle("highlight");
firstParagraph.classList.toggle("highlight");
firstParagraph.classList.toggle("highlight");
firstParagraph.classList.toggle("highlight");
firstParagraph.classList.toggle("highlight");

const newParagraph = document.createElement("p");
newParagraph.innerText = "This is a new paragraph";

const newParagraph2 = document.createElement("p");
newParagraph2.innerText = "This is a new paragraph 2";

// W środku containera
container.append(newParagraph);
container.prepend(newParagraph2);

// Przed i po containerze
container.before(newParagraph);
container.after(newParagraph2);

newParagraph.remove();
newParagraph2.replaceWith(newParagraph);

container.innerHTML = container.innerHTML + `<p>Another paragraph</p>`;

const firstParagraph2 = document.querySelector("#container > p:first-of-type");

console.log(firstParagraph2.parentElement.parentElement);
console.log(firstParagraph2.nextElementSibling.nextElementSibling);

console.log(container.children);
