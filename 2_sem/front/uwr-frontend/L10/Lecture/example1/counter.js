const handleCounter = (currentValue, action) => {
  switch (action) {
    case "increment":
      return currentValue + 1;
    case "decrement":
      return currentValue - 1;
    default:
      throw new Error("Invalid action");
  }
};
