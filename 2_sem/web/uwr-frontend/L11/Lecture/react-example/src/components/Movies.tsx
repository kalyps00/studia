import { useReducer } from "react";
import AddMovieForm from "./AddMovieForm";
import Movie from "./Movie";
import { movieReducer } from "./movieReducer";

const Movies = () => {
  /*   const [movies, setMovies] = useState([
    { id: 1, title: "Movie 1", year: 2021 },
    { id: 2, title: "Movie 2", year: 2020 },
    { id: 3, title: "Movie 3", year: 2019 },
    { id: 4, title: "Movie 4", year: 2018 },
  ]); */

  const [movies, dispatch] = useReducer(movieReducer, [
    { id: 1, title: "Movie 1", year: 2021 },
    { id: 2, title: "Movie 2", year: 2020 },
    { id: 3, title: "Movie 3", year: 2019 },
    { id: 4, title: "Movie 4", year: 2018 },
  ]);

  return (
    <div>
      <AddMovieForm
        onAdd={(movie) => dispatch({ type: "ADD_MOVIE", payload: movie })}
      />
      {movies.map((movie) => (
        <Movie
          key={movie.id}
          title={movie.title}
          year={movie.year}
          onRemove={() => dispatch({ type: "REMOVE_MOVIE", payload: movie.id })}
        />
      ))}
    </div>
  );
};

export default Movies;
