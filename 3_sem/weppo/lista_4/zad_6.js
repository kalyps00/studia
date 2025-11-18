class Queue {
  constructor() {
    this.items = [];
  }

  push(element) {
    this.items.push(element);
  }

  Pop() {
    return this.isEmpty() ? "Queue is empty" : this.items.shift(); // pop() i mamy LIFO
  }

  isEmpty() {
    return this.items.length === 0;
  }

  size() {
    return this.items.length;
  }
}

function Tree(val, left, right) {
  this.left = left;
  this.right = right;
  this.val = val;
}

Tree.prototype[Symbol.iterator] = function* () {
  const queue = new Queue();
  queue.push(this);
  while (!queue.isEmpty()) {
    const node = queue.Pop();

    if (node.left) queue.push(node.left);
    if (node.right) queue.push(node.right);

    yield node.val;
  }
};

let root = new Tree(1, new Tree(2, new Tree(3)), new Tree(4));
/*  1
   / \
  2  4
 /
3 
*/
for (let e of root) {
  console.log(e);
}
