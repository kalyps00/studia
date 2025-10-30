import type { Todo } from "../types";
import { TodoItem } from "./todoitem";

interface Props {
  todos: Todo[];
  onToggle: (id: string) => void;
  onRemove: (id: string) => void;
  onMoveUp: (id: string) => void;
  onMoveDown: (id: string) => void;
}

export function TodoList({ todos, onToggle, onRemove, onMoveUp, onMoveDown }: Props) {
  return (
    <ul className="todos__list">
      {todos.map((todo) => (
        <TodoItem
          key={todo.id}
          todo={todo}
          onToggle={() => onToggle(todo.id)}
          onRemove={() => onRemove(todo.id)}
          onMoveUp={() => onMoveUp(todo.id)}
          onMoveDown={() => onMoveDown(todo.id)}
        />
      ))}
    </ul>
  );
}
