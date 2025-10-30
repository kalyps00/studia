let todos = [];
const form = document.getElementById("add-todo-form");
const input = form.querySelector("input");
const clearBtn = document.getElementById("todos-clear");
const todolist = document.getElementById("todo-list");
clearBtn.addEventListener("click", function () {
  todos = [];
  render();
});
form.addEventListener("submit", function (event) {
  event.preventDefault();
  todos.push({ name: input.value, completed: false });
  input.value = "";
  render();
});
todolist.addEventListener("click", function (event) {
  if (!event.target.classList.contains("todo-button")) return;
  const li = event.target.closest("li");
  const index = Array.from(todolist.children).indexOf(li);

  if (event.target.textContent === "Remove") {
    todos.splice(index, 1);
  } else if (event.target.textContent === "Done") {
    todos[index].completed = true;
  } else if (event.target.textContent === "Revert") {
    todos[index].completed = false;
  } else if (event.target.textContent === "↑") {
    const temp = todos[index - 1];
    todos[index - 1] = todos[index];
    todos[index] = temp;
  } else if (event.target.textContent === "↓") {
    const temp = todos[index + 1];
    todos[index + 1] = todos[index];
    todos[index] = temp;
  }

  render();
});
function render() {
  todolist.innerHTML = "";
  todos.forEach((todo) => {
    const li = document.createElement("li");
    li.className = "todo__container";
    if (todo.completed) li.classList.add("todo__container--completed");
    //name
    const nameDiv = document.createElement("div");
    nameDiv.className = "todo-element todo-name";
    nameDiv.textContent = todo.name;
    //up
    const upButton = document.createElement("button");
    upButton.className = "todo-element todo-button move-up";
    upButton.textContent = "↑";
    //down
    const downButton = document.createElement("button");
    downButton.className = "todo-element todo-button move-down";
    downButton.textContent = "↓";
    //revert / done
    const revert_done_Button = document.createElement("button");
    revert_done_Button.className = "todo-element todo-button";
    revert_done_Button.textContent = todo.completed ? "Revert" : "Done";
    //remove
    const remove_Button = document.createElement("button");
    remove_Button.className = "todo-element todo-button";
    remove_Button.textContent = "Remove";

    li.append(nameDiv, upButton, downButton, revert_done_Button, remove_Button);
    todolist.append(li);
  });
  const counter = document.getElementById("count");
  counter.textContent = todos.filter((todo) => !todo.completed).length;
}
