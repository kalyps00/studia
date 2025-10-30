import type { MovieType } from "../types/Movie.type";

type MovieProps = Omit<MovieType, "id"> & {
  onRemove: () => void;
};

const Movie = ({ title, year, onRemove }: MovieProps) => {
  return (
    <div>
      <h2>{title}</h2>
      <p>Year: {year}</p>
      <button onClick={onRemove}>Delete</button>
    </div>
  );
};

export default Movie;
