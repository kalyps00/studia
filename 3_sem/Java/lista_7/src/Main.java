import structures.SimpleList;
import java.util.Date;
import java.util.Iterator;

public class Main {
    public static void main(String[] args) {
        System.out.println("=== Testing SimpleList<Integer> ===");
        testIntegerList();
        
        System.out.println("\n=== Testing SimpleList<String> ===");
        testStringList();
        
        System.out.println("\n=== Testing SimpleList<Date> ===");
        testDateList();
    }

    private static void testIntegerList() {
        SimpleList<Integer> list = new SimpleList<>();
        System.out.println("Empty: " + list.empty());
        
        list.insert(10, 0);
        list.insert(5, 0);
        list.insert(20, 2);
        list.insert(15, 2);
        
        System.out.println("List: " + list); // [5, 10, 15, 20]
        System.out.println("Size: " + list.size());
        System.out.println("Min: " + list.min());
        System.out.println("Max: " + list.max());
        System.out.println("At 2: " + list.at(2));
        System.out.println("Index of 10: " + list.index(10));
        System.out.println("Search 20: " + list.search(20));
        System.out.println("Search 99: " + list.search(99));
        
        list.remove(Integer.valueOf(10));
        System.out.println("After removing 10: " + list);
        
        list.remove(0);
        System.out.println("After removing at 0: " + list);
        
        System.out.println("Iterating:");
        for (Integer i : list) {
            System.out.print(i + " ");
        }
        System.out.println();
        
        // Fail-fast test
        try {
            for (Integer i : list) {
                list.insert(99, 0);
            }
        } catch (IllegalStateException e) {
            System.out.println("Caught expected exception: " + e.getMessage());
        }
    }

    private static void testStringList() {
        SimpleList<String> list = new SimpleList<>();
        list.insert("Banana", 0);
        list.insert("Apple", 0);
        list.insert("Cherry", 2);
        
        System.out.println("List: " + list);
        System.out.println("Min: " + list.min());
        System.out.println("Max: " + list.max());
        
        list.remove("Banana");
        System.out.println("After removing Banana: " + list);
    }

    private static void testDateList() {
        SimpleList<Date> list = new SimpleList<>();
        Date d1 = new Date(1000000000L);
        Date d2 = new Date(2000000000L);
        Date d3 = new Date(1500000000L);
        
        list.insert(d1, 0);
        list.insert(d2, 1);
        list.insert(d3, 1);
        
        System.out.println("List: " + list);
        System.out.println("Min: " + list.min());
        System.out.println("Max: " + list.max());
    }
}
