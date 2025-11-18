let Foo = (function () {
  function Qux() {
    console.log("Foo::Qux");
  }
  function Foo() {}

  Foo.prototype.Bar = function () {
    console.log("Foo::Bar");
    Qux();
  };

  return Foo;
})();

let foo = new Foo();
foo.Bar();

try {
  foo.Qux();
} catch (e) {
  console.log(e.message);
}
