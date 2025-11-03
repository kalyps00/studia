package wyrażenia;

public class Dodaj extends Wyrazenie {
    private final Wyrazenie lewy;
    private final Wyrazenie prawy;
    
    public Dodaj(Wyrazenie lewy, Wyrazenie prawy) {
        this.lewy = lewy;
        this.prawy = prawy;
    }
    
    @Override
    public double oblicz() {
        return lewy.oblicz() + prawy.oblicz();
    }
    
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        
        if (lewy instanceof Odejmij || lewy instanceof Dodaj) {
            sb.append("(").append(lewy).append(")");
        } else {
            sb.append(lewy);
        }
        
        sb.append(" + ");
        
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
        Dodaj dodaj = (Dodaj) obj;  
        return lewy.equals(dodaj.lewy) && prawy.equals(dodaj.prawy);
    }
}