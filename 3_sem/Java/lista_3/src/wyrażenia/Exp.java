package wyrażenia;

public class Exp extends Wyrazenie {
    private final Wyrazenie argument;
    
    public Exp(Wyrazenie argument) {
        this.argument = argument;
    }
    
    @Override
    public double oblicz() {
        return Math.exp(argument.oblicz());
    }
    
    @Override
    public String toString() {
        return "exp(" + argument + ")";
    }
    
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Exp exp = (Exp) obj;
        return argument.equals(exp.argument);
    }
}
