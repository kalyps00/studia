import { v4 as uuidv4 } from "./node_modules/uuid/dist/esm-browser/index.js";

const bodyElement = document.querySelector("body")!;

const todos = [
  { id: uuidv4(), text: "JavaScript", completed: false },
  { id: uuidv4(), text: "Learn TypeScript", completed: false },
  { id: uuidv4(), text: "Learn React", completed: false },
  { id: uuidv4(), text: "Learn Node.js", completed: false },
  { id: uuidv4(), text: "Learn Express.js", completed: false },
];

const renderTodos = () => {
  const todoListElement = document.createElement("ul");
  todos.forEach((todo) => {
    const todoItemElement = document.createElement("li");
    todoItemElement.innerText = `${todo.id} - ${todo.text}`;
    todoListElement.appendChild(todoItemElement);
  });
  bodyElement.appendChild(todoListElement);
};

renderTodos();
