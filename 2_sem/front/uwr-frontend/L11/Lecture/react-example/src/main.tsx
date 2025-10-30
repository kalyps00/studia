import { createRoot } from "react-dom/client";
import Movies from "./components/Movies.tsx";
import "./index.css";

createRoot(document.getElementById("root")!).render(<Movies />);
