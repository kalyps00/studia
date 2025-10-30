import type { MovieType } from "../types/Movie.type";

const AddMovieForm = ({
  onAdd,
}: {
  onAdd: (movie: Omit<MovieType, "id">) => void;
}) => {
  //const [title, setTitle] = useState("");

  //console.log(title);

  return (
    <form
      onSubmit={(e) => {
        e.preventDefault();
        const formData = new FormData(e.currentTarget);

        onAdd({
          title: formData.get("title") as string,
          year: Number(formData.get("year")),
        });

        e.currentTarget.reset();
      }}
    >
      <div>
        <label htmlFor="title">Title:</label>
        <input
          type="text"
          id="title"
          name="title"
          /* value={title}
          onChange={(e) => setTitle(e.target.value)} */
        />
      </div>
      <div>
        <label htmlFor="year">Year:</label>
        <input type="number" id="year" name="year" />
      </div>
      <button type="submit">Add Movie</button>
    </form>
  );
};

export default AddMovieForm;
