package wyrażenia;

public class Negacja extends Wyrazenie {
    private final Wyrazenie argument;
    
    public Negacja(Wyrazenie argument) {
        this.argument = argument;
    }
    
    @Override
    public double oblicz() {
        return -argument.oblicz();
    }
    
    @Override
    public String toString() {
        if (argument instanceof Dodaj || argument instanceof Odejmij || 
            argument instanceof Mnoz || argument instanceof Dziel ||
            argument instanceof Negacja || argument instanceof Odwrotność) {
            return "~(" + argument + ")";
        }
        return "~" + argument;
    }
    
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Negacja negacja = (Negacja) obj;
        return argument.equals(negacja.argument);
    }
}
