package wyrażenia;

public class Liczba extends Wyrazenie {
    private final double wartość;
    
    public static final Liczba ZERO = new Liczba(0.0);
    public static final Liczba JEDEN = new Liczba(1.0);
    
    public Liczba(double wartość) {
        this.wartość = wartość;
    }
    
    @Override
    public double oblicz() {
        return wartość;
    }
    
    @Override
    public String toString() {
        return String.valueOf(wartość);
    }
    
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Liczba liczba = (Liczba) obj;
        return Double.compare(liczba.wartość, wartość) == 0;
    }
}
