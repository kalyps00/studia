package wyrażenia;

import java.util.HashMap;
import java.util.Map;

public class Stała extends Wyrazenie {
    private final String nazwa;
    private final double wartość;
    
    private static Map<String, Double> wartościStałych = new HashMap<>();
    
    public static final Stała Pi = new Stała("π", Math.PI);
    public static final Stała E = new Stała("e", Math.E);
    
    public Stała(String nazwa, double wartość) {
        this.nazwa = nazwa;
        this.wartość = wartość;
        wartościStałych.put(nazwa, wartość);
    }
    
    @Override
    public double oblicz() {
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
        Stała stała = (Stała) obj;
        return nazwa.equals(stała.nazwa) && Double.compare(stała.wartość, wartość) == 0;
    }
}
