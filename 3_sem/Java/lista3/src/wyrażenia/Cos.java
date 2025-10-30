package wyrażenia;

public class Cos extends Wyrazenie {
    private final Wyrazenie argument;
    
    public Cos(Wyrazenie argument) {
        this.argument = argument;
    }
    
    @Override
    public double oblicz() {
        return Math.cos(argument.oblicz());
    }
    
    @Override
    public String toString() {
        return "cos(" + argument + ")";
    }
    
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Cos cos = (Cos) obj;
        return argument.equals(cos.argument);
    }
}
