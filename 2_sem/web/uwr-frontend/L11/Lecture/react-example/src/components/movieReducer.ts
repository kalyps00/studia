import type { MovieType } from "../types/Movie.type";

export const movieReducer = (
  currentState: MovieType[],
  action:
    | { type: "ADD_MOVIE"; payload: Omit<MovieType, "id"> }
    | { type: "REMOVE_MOVIE"; payload: number }
) => {
  switch (action.type) {
    case "ADD_MOVIE":
      return [
        ...currentState,
        { id: currentState.length + 1, ...action.payload },
      ];
    case "REMOVE_MOVIE":
      return currentState.filter((movie) => movie.id !== action.payload);
    default:
      return currentState;
  }
};
