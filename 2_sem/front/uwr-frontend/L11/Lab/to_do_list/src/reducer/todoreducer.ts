import type { Todo } from "../types";
type Action =
  | { type: "ADD"; payload: { text: string } }
  | { type: "REMOVE"; payload: { id: string } }
  | { type: "TOGGLE"; payload: { id: string } }
  | { type: "CLEAR_ALL" }
  | { type: "MOVE_UP"; payload: { id: string } }
  | { type: "MOVE_DOWN"; payload: { id: string } };

export function todoReducer(state: Todo[], action: Action): Todo[] {
  switch (action.type) {
    case "ADD":
      return [...state, { id: crypto.randomUUID(), text: action.payload.text, completed: false }];
    case "REMOVE":
      return state.filter((todo) => todo.id !== action.payload.id);
    case "TOGGLE":
      return state.map((todo) => (todo.id === action.payload.id ? { ...todo, completed: !todo.completed } : todo));

    case "CLEAR_ALL":
      return [];
    case "MOVE_DOWN": {
      const idx = state.findIndex((temptodo) => temptodo.id === action.payload.id);
      if (idx === -1 || idx === state.length - 1) return state;
      const newTodo = [...state];
      [newTodo[idx], newTodo[idx + 1]] = [newTodo[idx + 1], newTodo[idx]];
      return newTodo;
    }

    case "MOVE_UP": {
      const idx = state.findIndex((temptodo) => temptodo.id === action.payload.id);
      if (idx <= 0) return state;
      const newTodo = [...state];
      [newTodo[idx], newTodo[idx - 1]] = [newTodo[idx - 1], newTodo[idx]];
      return newTodo;
    }
    default:
      return state;
  }
}
