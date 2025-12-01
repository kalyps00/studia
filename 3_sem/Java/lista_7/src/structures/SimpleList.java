package structures;

import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.ConcurrentModificationException;

public class SimpleList<T extends Comparable<T>> implements SimpleSequence<T>, Iterable<T> {

    private class SimpleNode {
        SimpleNode prev, next;
        T data;

        SimpleNode(T data) {
            this.data = data;
        }

        // Recursive/Delegated implementations
        
        // Returns the node at relative index i
        SimpleNode getNode(int i) {
            if (i == 0) return this;
            if (next == null) throw new IndexOutOfBoundsException();
            return next.getNode(i - 1);
        }

        T min() {
            T minRest = (next != null) ? next.min() : data;
            return (data.compareTo(minRest) < 0) ? data : minRest;
        }

        T max() {
            T maxRest = (next != null) ? next.max() : data;
            return (data.compareTo(maxRest) > 0) ? data : maxRest;
        }

        boolean search(T el) {
            if (data.equals(el)) return true;
            if (next != null) return next.search(el);
            return false;
        }

        int index(T el, int currentIndex) {
            if (data.equals(el)) return currentIndex;
            if (next != null) return next.index(el, currentIndex + 1);
            return -1;
        }
    }

    private SimpleNode head;
    private int size;
    private int modCount;

    public SimpleList() {
        this.head = null;
        this.size = 0;
        this.modCount = 0;
    }

    @Override
    public void insert(T el, int pos) {
        if (el == null) throw new NullPointerException("Element cannot be null");
        if (pos < 0 || pos > size) throw new IndexOutOfBoundsException("Index: " + pos + ", Size: " + size);

        SimpleNode newNode = new SimpleNode(el);

        if (pos == 0) {
            newNode.next = head;
            if (head != null) {
                head.prev = newNode;
            }
            head = newNode;
        } else {
            // Delegate finding the position to the nodes or iterate
            // Since we need to insert *after* pos-1, let's find pos-1.
            // Using the "wrapper" idea, maybe we should use getNode on head.
            SimpleNode prevNode = head.getNode(pos - 1);
            newNode.next = prevNode.next;
            newNode.prev = prevNode;
            if (prevNode.next != null) {
                prevNode.next.prev = newNode;
            }
            prevNode.next = newNode;
        }
        size++;
        modCount++;
    }

    @Override
    public boolean remove(T el) {
        if (el == null) throw new NullPointerException("Element cannot be null");
        if (head == null) return false;

        SimpleNode current = head;
        while (current != null) {
            if (current.data.equals(el)) {
                removeNode(current);
                return true;
            }
            current = current.next;
        }
        return false;
    }

    @Override
    public T remove(int pos) {
        if (pos < 0 || pos >= size) throw new IndexOutOfBoundsException("Index: " + pos + ", Size: " + size);
        
        SimpleNode toRemove;
        if (pos == 0) {
            toRemove = head;
        } else {
            toRemove = head.getNode(pos);
        }
        
        T data = toRemove.data;
        removeNode(toRemove);
        return data;
    }

    private void removeNode(SimpleNode node) {
        if (node.prev != null) {
            node.prev.next = node.next;
        } else {
            head = node.next;
        }

        if (node.next != null) {
            node.next.prev = node.prev;
        }
        
        node.prev = null;
        node.next = null;
        size--;
        modCount++;
    }

    @Override
    public T min() {
        if (empty()) return null; // Or throw exception? Prompt doesn't specify. Usually null or exception.
        // Let's assume list is not empty or return null.
        // But T is object, so null is possible.
        if (head == null) return null;
        return head.min();
    }

    @Override
    public T max() {
        if (empty()) return null;
        if (head == null) return null;
        return head.max();
    }

    @Override
    public boolean search(T el) {
        if (el == null) throw new NullPointerException("Element cannot be null");
        if (head == null) return false;
        return head.search(el);
    }

    @Override
    public T at(int pos) {
        if (pos < 0 || pos >= size) throw new IndexOutOfBoundsException("Index: " + pos + ", Size: " + size);
        return head.getNode(pos).data;
    }

    @Override
    public int index(T el) {
        if (el == null) throw new NullPointerException("Element cannot be null");
        if (head == null) return -1;
        return head.index(el, 0);
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public boolean empty() {
        return size == 0;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("[");
        SimpleNode current = head;
        while (current != null) {
            sb.append(current.data);
            if (current.next != null) {
                sb.append(", ");
            }
            current = current.next;
        }
        sb.append("]");
        return sb.toString();
    }

    @Override
    public Iterator<T> iterator() {
        return new SimpleListIterator();
    }

    private class SimpleListIterator implements Iterator<T> {
        private SimpleNode current;
        private int expectedModCount;

        public SimpleListIterator() {
            this.current = head;
            this.expectedModCount = modCount;
        }

        @Override
        public boolean hasNext() {
            if (expectedModCount != modCount) {
                throw new IllegalStateException("List modified during iteration");
            }
            return current != null;
        }

        @Override
        public T next() {
            if (expectedModCount != modCount) {
                throw new IllegalStateException("List modified during iteration");
            }
            if (current == null) {
                throw new NoSuchElementException();
            }
            T data = current.data;
            current = current.next;
            return data;
        }
    }
}
