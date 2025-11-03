package wyrażenia;

public class Odejmij extends Wyrazenie {
    private final Wyrazenie lewy;
    private final Wyrazenie prawy;
    
    public Odejmij(Wyrazenie lewy, Wyrazenie prawy) {
        this.lewy = lewy;
        this.prawy = prawy;
    }
    
    @Override
    public double oblicz() {
        return lewy.oblicz() - prawy.oblicz();
    }
    
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        
        if (lewy instanceof Odejmij || lewy instanceof Dodaj) {
            sb.append("(").append(lewy).append(")");
        } else {
            sb.append(lewy);
        }
        
        sb.append(" - ");
        
        if (prawy instanceof Odejmij || prawy instanceof Dodaj) {
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
        Odejmij odejmij = (Odejmij) obj;
        return lewy.equals(odejmij.lewy) && prawy.equals(odejmij.prawy);
    }
}
