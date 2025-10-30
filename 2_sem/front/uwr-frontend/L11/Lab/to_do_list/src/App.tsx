import { useReducer } from "react";
import { todoReducer } from "./reducer/todoreducer";
import { Header } from "./components/header";
import { TodoForm } from "./components/todoform";
import { TodoList } from "./components/todolist";
import "./index.css";
function App() {
  const [todos, dispatch] = useReducer(todoReducer, []);
  const remainingCount = todos.filter((todo) => !todo.completed).length;
  return (
    <div className="body__wrapper">
      <main className="main">
        <section>
          <TodoForm onAdd={(text) => dispatch({ type: "ADD", payload: { text } })}></TodoForm>
        </section>
        <section className="todos__container">
          <Header remaining={remainingCount} onClear={() => dispatch({ type: "CLEAR_ALL" })}></Header>
          <TodoList
            todos={todos}
            onToggle={(id) => dispatch({ type: "TOGGLE", payload: { id } })}
            onRemove={(id) => dispatch({ type: "REMOVE", payload: { id } })}
            onMoveUp={(id) => dispatch({ type: "MOVE_UP", payload: { id } })}
            onMoveDown={(id) => dispatch({ type: "MOVE_DOWN", payload: { id } })}
          ></TodoList>
        </section>
      </main>
    </div>
  );
}
export default App;
