package wyrażenia;

public class Mnoz extends Wyrazenie {
    private final Wyrazenie lewy;
    private final Wyrazenie prawy;
    
    public Mnoz(Wyrazenie lewy, Wyrazenie prawy) {
        this.lewy = lewy;
        this.prawy = prawy;
    }
    
    @Override
    public double oblicz() {
        return lewy.oblicz() * prawy.oblicz();
    }
    
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        
        if (lewy instanceof Dodaj || lewy instanceof Odejmij) {
            sb.append("(").append(lewy).append(")");
        } else {
            sb.append(lewy);
        }
        
        sb.append(" * ");
        
        if (prawy instanceof Dodaj || prawy instanceof Odejmij) {
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
        Mnoz mnoz = (Mnoz) obj;
        return lewy.equals(mnoz.lewy) && prawy.equals(mnoz.prawy);
    }
}
