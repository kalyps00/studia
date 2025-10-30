import itertools


class Formula:
    def __str__(self):
        raise NotImplementedError

    def variables(self) -> set[str]:
        raise NotImplementedError

    def evaluate(self, variables: dict[str, bool]) -> bool:
        raise NotImplementedError

    def simplify(self):
        raise NotImplementedError

    def __add__(self, other):
        return Or(self, other)

    def __mul__(self, other):
        return And(self, other)

    def tautology(self) -> bool:
        vars = list(self.variables())
        if not vars:
            return bool(self.evaluate({}))
        for values in itertools.product([False, True], repeat=len(vars)):
            mapp = dict(zip(vars, values))
            try:
                v = self.evaluate(mapp)
            except KeyError as e:
                raise KeyError(f"Variable {e} not found in mapping") from e
            if not v:
                return False
        return True


class Variable(Formula):
    def __init__(self, name):
        if not isinstance(name, str):
            raise TypeError("Variable name must be a string")
        self.name = name

    def __str__(self) -> str:
        return self.name

    def variables(self):
        return {self.name}

    def simplify(self):
        return Variable(self.name)

    def evaluate(self, variables):
        if self.name not in variables:
            raise KeyError(f"Variable {self.name} not found in mapping")
        return variables[self.name]


class Constant(Formula):
    def __init__(self, value: bool):
        if not isinstance(value, bool):
            raise TypeError("Constant value must be a boolean")
        self.value = value

    def __str__(self) -> str:
        return "T" if self.value else "F"

    def variables(self):
        return set()

    def simplify(self):
        return Constant(self.value)

    def evaluate(self, variables):
        return self.value


class Not(Formula):
    def __init__(self, operand: Formula):
        self.operand = operand

    def __str__(self) -> str:
        return f"¬({self.operand})"

    def variables(self):
        return self.operand.variables()

    def evaluate(self, variables: dict[str, bool]) -> bool:
        return not self.operand.evaluate(variables)

    def simplify(self):
        return Not(self.operand.simplify())


class And(Formula):
    def __init__(self, left: Formula, right: Formula):
        self.left = left
        self.right = right

    def __str__(self) -> str:
        return f"{self.left} ∧ {self.right}"

    def variables(self):
        return self.left.variables().union(self.right.variables())

    def evaluate(self, variables: dict[str, bool]) -> bool:
        lv = self.left.evaluate(variables)
        if not lv:
            return False
        rv = self.right.evaluate(variables)
        return lv and rv

    def simplify(self):
        rv = self.right.simplify()
        lv = self.left.simplify()
        if isinstance(rv, Constant) and rv is False:
            return Constant(False)
        if isinstance(lv, Constant) and lv is False:
            return Constant(False)
        return And(lv, rv)


class Or(Formula):
    def __init__(self, left: Formula, right: Formula):
        self.left = left
        self.right = right

    def __str__(self) -> str:
        return f"{self.left} v {self.right}"

    def variables(self):
        return self.left.variables().union(self.right.variables())

    def evaluate(self, variables: dict[str, bool]) -> bool:
        lv = self.left.evaluate(variables)
        if lv:
            return True
        rv = self.right.evaluate(variables)
        return lv or rv

    def simplify(self):
        rv = self.right.simplify()
        lv = self.left.simplify()
        if isinstance(rv, Constant) and rv is True:
            return Constant(True)
        if isinstance(lv, Constant) and lv is True:
            return Constant(True)
        return Or(lv, rv)


if __name__ == "__main__":
    import unittest  # testy

    class Tests(unittest.TestCase):
        def test_constant(self):
            self.assertTrue(Constant(True).evaluate({}))
            self.assertFalse(Constant(False).evaluate({}))

        def test_variable(self):
            v = Variable("x")
            self.assertEqual(v.variables(), {"x"})
            self.assertTrue(v.evaluate({"x": True}))
            with self.assertRaises(KeyError):
                v.evaluate({})

        def test_and_or_evaluate(self):
            a = And(Variable("x"), Variable("y"))
            self.assertFalse(a.evaluate({"x": False, "y": True}))
            self.assertFalse(a.evaluate({"x": True, "y": False}))
            self.assertTrue(a.evaluate({"x": True, "y": True}))
            o = Or(Variable("x"), Variable("y"))
            self.assertTrue(o.evaluate({"x": True, "y": False}))
            self.assertFalse(o.evaluate({"x": False, "y": False}))

        def test_operators(self):
            expr = Variable("x") + Variable("y")
            self.assertIsInstance(expr, Or)
            expr2 = Variable("x") * Variable("y")
            self.assertIsInstance(expr2, And)

        def test_str(self):
            v = Variable("x")
            c_true = Constant(True)
            c_false = Constant(False)
            n = Not(v)
            a = And(v, c_true)
            o = Or(n, a)
            print("\nstr(v):", str(v))
            print("str(c_true):", str(c_true))
            print("str(c_false):", str(c_false))
            print("str(n):", str(n))
            print("str(a):", str(a))
            print("str(o):", str(o))
            # basic assertions
            self.assertEqual(str(v), "x")
            self.assertEqual(str(c_true), "T")
            self.assertEqual(str(c_false), "F")
            self.assertEqual(str(n), "¬(x)")
            self.assertTrue("∧" in str(a))
            self.assertTrue("v" in str(o))

        def test_tautology(self):
            f = Or(Variable("p"), Not(Variable("p")))
            self.assertTrue(f.tautology())

    unittest.main(verbosity=2)
