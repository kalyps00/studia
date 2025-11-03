package wyrażenia;

import java.util.HashMap;
import java.util.Map;

public class Zmienna extends Wyrazenie {
    private final String nazwa;
    
    private static Map<String, Double> wartościZmiennych = new HashMap<>();
    
    public Zmienna(String nazwa) {
        this.nazwa = nazwa;
    }
    
    public static void ustawWartość(String nazwa, double wartość) {
        wartościZmiennych.put(nazwa, wartość);
    }
    
    @Override
    public double oblicz() {
        Double wartość = wartościZmiennych.get(nazwa);
        if (wartość == null) {
            throw new IllegalArgumentException("Zmienna '" + nazwa + "' nie ma przypisanej wartości");
        }
        return wartość;
    }
    
    @Override
    public String toString() {
        return nazwa;
    }
    
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Zmienna zmienna = (Zmienna) obj;
        return nazwa.equals(zmienna.nazwa);
    }
}
