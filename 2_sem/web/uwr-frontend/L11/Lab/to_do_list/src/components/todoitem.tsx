
import type { Todo } from "../types";

interface Props {
  todo: Todo;
  onToggle: () => void;
  onRemove: () => void;
  onMoveUp: () => void;
  onMoveDown: () => void;
}
export function TodoItem({ todo, onToggle, onRemove, onMoveDown, onMoveUp }: Props) {
  return (
    <li className={"todo__container " + (todo.completed ? "todo__container--completed" : "")}>
      <div className="todo-element todo-name">{todo.text}</div>
      <button className="todo-element todo-button move-up" onClick={onMoveUp}>
        ↑
      </button>
      <button className="todo-element todo-button move-down" onClick={onMoveDown}>
        ↓
      </button>
      <button className="todo-element todo-button" onClick={onToggle}>
        {!todo.completed ? "Done" : "Revert"}
      </button>
      <button className="todo-element todo-button" onClick={onRemove}>
        Remove
      </button>
    </li>
  );
}
