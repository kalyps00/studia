interface Todo {
  title: string
  description: string
  completed: boolean
}

interface Expected1 {
  title: string
}

interface Expected2 {
  title: string
  completed: boolean
}

type MyPick<T, K extends keyof T> = {
  [key in K] : T[key]
}
type Exp1 = MyPick<Todo,'title'>

type Exp2 = MyPick<Todo, 'title' | 'completed'>

