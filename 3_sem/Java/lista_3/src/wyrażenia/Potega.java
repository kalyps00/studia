package wyrażenia;

public class Potega extends Wyrazenie {
    private final Wyrazenie podstawa;
    private final Wyrazenie wykładnik;
    
    public Potega(Wyrazenie podstawa, Wyrazenie wykładnik) {
        this.podstawa = podstawa;
        this.wykładnik = wykładnik;
    }
    
    @Override
    public double oblicz() {
        return Math.pow(podstawa.oblicz(), wykładnik.oblicz());
    }
    
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        
        if (podstawa instanceof Dodaj || podstawa instanceof Odejmij || 
            podstawa instanceof Mnoz || podstawa instanceof Dziel) {
            sb.append("(").append(podstawa).append(")");
        } else {
            sb.append(podstawa);
        }
        
        sb.append("^");
        
        if (wykładnik instanceof Dodaj || wykładnik instanceof Odejmij || 
            wykładnik instanceof Mnoz || wykładnik instanceof Dziel) {
            sb.append("(").append(wykładnik).append(")");
        } else {
            sb.append(wykładnik);
        }
        
        return sb.toString();
    }
    
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Potega potega = (Potega) obj;
        return podstawa.equals(potega.podstawa) && wykładnik.equals(potega.wykładnik);
    }
}
