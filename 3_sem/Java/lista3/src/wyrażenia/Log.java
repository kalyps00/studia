package wyrażenia;

public class Log extends Wyrazenie {
    private final Wyrazenie podstawa;
    private final Wyrazenie argument;
    
    public Log(Wyrazenie podstawa, Wyrazenie argument) {
        this.podstawa = podstawa;
        this.argument = argument;
    }
    
    @Override
    public double oblicz() {
        double pBase = podstawa.oblicz();
        double arg = argument.oblicz();
        if (pBase <= 0 || pBase == 1.0) {
            throw new ArithmeticException("Nieprawidłowa podstawa logarytmu");
        }
        if (arg <= 0) {
            throw new ArithmeticException("Argument logarytmu musi być dodatni");
        }
        return Math.log(arg) / Math.log(pBase);
    }
    
    @Override
    public String toString() {
        return "log(" + podstawa + ", " + argument + ")";
    }
    
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Log log = (Log) obj;
        return podstawa.equals(log.podstawa) && argument.equals(log.argument);
    }
}
