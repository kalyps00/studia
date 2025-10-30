package wyrażenia;

public class Dziel extends Wyrazenie {
    private final Wyrazenie lewy;
    private final Wyrazenie prawy;
    
    public Dziel(Wyrazenie lewy, Wyrazenie prawy) {
        this.lewy = lewy;
        this.prawy = prawy;
    }
    
    @Override
    public double oblicz() {
        double dzielnik = prawy.oblicz();
        if (dzielnik == 0.0) {
            throw new ArithmeticException("Dzielenie przez zero");
        }
        return lewy.oblicz() / dzielnik;
    }
    
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        
        if (lewy instanceof Dodaj || lewy instanceof Odejmij) {
            sb.append("(").append(lewy).append(")");
        } else {
            sb.append(lewy);
        }
        
        sb.append(" / ");
        
        if (prawy instanceof Dodaj || prawy instanceof Odejmij || prawy instanceof Mnoz || prawy instanceof Dziel) {
            sb.append("(").append(prawy).append(")");
        } else {
            sb.append(prawy);
        }
        
        return sb.toString();
    }
    
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Dziel dziel = (Dziel) obj;
        return lewy.equals(dziel.lewy) && prawy.equals(dziel.prawy);
    }
}
