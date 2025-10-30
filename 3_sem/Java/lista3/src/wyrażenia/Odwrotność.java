package wyrażenia;

public class Odwrotność extends Wyrazenie {
    private final Wyrazenie argument;
    
    public Odwrotność(Wyrazenie argument) {
        this.argument = argument;
    }
    
    @Override
    public double oblicz() {
        double wartość = argument.oblicz();
        if (wartość == 0.0) {
            throw new ArithmeticException("Odwrotność zera");
        }
        return 1.0 / wartość;
    }
    
    @Override
    public String toString() {
        if (argument instanceof Dodaj || argument instanceof Odejmij || 
            argument instanceof Mnoz || argument instanceof Dziel ||
            argument instanceof Negacja || argument instanceof Odwrotność) {
            return "!(" + argument + ")";
        }
        return "!" + argument;
    }
    
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Odwrotność odwrotność = (Odwrotność) obj;
        return argument.equals(odwrotność.argument);
    }
}
