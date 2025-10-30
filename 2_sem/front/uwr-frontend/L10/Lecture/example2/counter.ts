export const handleCounter = (
  currentValue: number,
  action: "increment" | "decrement"
) => {
  switch (action) {
    case "increment":
      return currentValue + 1;
    case "decrement":
      return currentValue - 1;
    default:
      throw new Error("Invalid action");
  }
};

export default handleCounter;
