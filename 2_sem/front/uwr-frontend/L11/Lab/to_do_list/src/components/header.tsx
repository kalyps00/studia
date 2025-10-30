interface HeaderProps {
  remaining: number;
  onClear: () => void;
}
export function Header({ remaining, onClear }: HeaderProps) {
  return (
    <header className="todos-header__container">
      <h1>Todo List ({remaining} remaining)</h1>
      <button className="todos-clear" onClick={onClear}>
        Clear All
      </button>
    </header>
  );
}
