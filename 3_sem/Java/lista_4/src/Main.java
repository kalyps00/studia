import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        ArraySetVar s = new ArraySetVar(10);
        s.set("a", 1.0);
        s.set("b", 2.0);
        s.set("c", 3.14);

        System.out.println("Original: " + s);
        System.out.println("Names: " + Arrays.toString(s.names()));
        System.out.println("Search 'b': " + s.search("b") + ", get b: " + s.get("b"));

        ArraySetVar copy = s.clone();
        copy.set("b", 0.5);

        System.out.println("After cloning and modifying copy:");
        System.out.println("Original: " + s);
        System.out.println("Copy:     " + copy);

        // test PairProb
        try {
            PairProb p = new PairProb("p", 0.7);
            System.out.println("PairProb ok: " + p);
            p.set(1.0);
            System.out.println("PairProb after set: " + p);
            p.set(1.5); // should throw
        } catch (Exception e) {
            System.out.println("Expected exception: " + e);
        }

        // test deletion
        s.del("b");
        System.out.println("After deleting 'b' from original: " + s);

        // test clear
        s.clear();
        System.out.println("After clear original (size=" + s.size() + "): " + s);
    }
}
