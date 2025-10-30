import { useState } from "react";
import NextExampleComponent from "./NextExampleComponent";

const ExampleComponent = () => {
  const [counter, setCounter] = useState(0);
  console.log("Hello, world!");

  /* 
  const a = 1;
  const hello = "hello";

  console.log("Hello, world!");

  function innerFunction() {
    console.log("This is an inner function");
  }

  console.log(a > 0 && "Greater than 0");

  const arr = [1, 2, 3, 4, 5]; */

  /*  const arr2 = arr.map((item) => {
    return <div>{item}</div>;
  }); // [<div>1</div>, <div>2</div>, <div>3</div>, <div>4</div>, <div>5</div>] */

  return (
    <>
      {/*<div>
        <span>{hello}</span>
        <div>{a}</div>
      </div>
      <div>Hello!</div>
      {false}
      {undefined}
      {null}
      {a > 0 ? <span>Greater than 0</span> : undefined}
      {a > 0 && <span>Greater than 0</span>}
             {arr.map((item) => {
        return <div key={item}>{item}</div>;
      })} */}
      <NextExampleComponent />
      <span>{counter}</span>
      <button
        onClick={() => {
          setCounter((count) => count + 1);
          setCounter((count) => count + 1);
          setCounter((count) => count + 1);
          setCounter((count) => count + 1);
          //console.log(counter);
        }}
      >
        Increment
      </button>
    </>
  );
};

export default ExampleComponent;
