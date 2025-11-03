package wyrażenia;

public class Sin extends Wyrazenie {
    private final Wyrazenie argument;
    
    public Sin(Wyrazenie argument) {
        this.argument = argument;
    }
    
    @Override
    public double oblicz() {
        return Math.sin(argument.oblicz());
    }
    
    @Override
    public String toString() {
        return "sin(" + argument + ")";
    }
    
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Sin sin = (Sin) obj;
        return argument.equals(sin.argument);
    }
}
