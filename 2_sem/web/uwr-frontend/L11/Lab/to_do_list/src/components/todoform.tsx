import { useState } from "react";

interface Props {
  onAdd: (text: string) => void;
}

export function TodoForm({ onAdd }: Props) {
  const [text, setText] = useState("");

  return (
    <form
      onSubmit={(e) => {
        e.preventDefault();
        const trimmed = text.trim();
        if (!trimmed) return; // puste zadania
        onAdd(trimmed);
        setText("");
      }}
    >
      <input
        className="add-item__element add-item__input"
        value={text}
        onChange={(e) => setText(e.target.value)}
        placeholder="Add a task..."
        required
      />
      <button type="submit" className="add-item__element add-item__submit">
        Add
      </button>
    </form>
  );
}
