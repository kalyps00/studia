package figury;

public final class Prosta {
    public final double a;
    public final double b;
    public final double c;

    public Prosta(double a, double b, double c) {
        if (a == 0 && b == 0) {
            throw new IllegalArgumentException("Współczynniki a i b nie mogą być jednocześnie zerowe.");
        }
        this.a = a;
        this.b = b;
        this.c = c;
    }

    public static Prosta przesun(Prosta p, Wektor v) {
        // Przesunięcie prostej o wektor v
        double newC = p.c - p.a * v.dx - p.b * v.dy;
        return new Prosta(p.a, p.b, newC);
    }

    public static boolean rownolegle(Prosta p1, Prosta p2) {
        return p1.a * p2.b == p2.a * p1.b;
    }

    public static boolean prostopadle(Prosta p1, Prosta p2) {
        return (p1.a * p2.a + p1.b * p2.b) == 0;
    }

    public static Punkt przeciecie(Prosta p1, Prosta p2) {
        double det = p1.a * p2.b - p2.a * p1.b;
        if (det == 0) {
            throw new IllegalArgumentException("Proste są równoległe i nie mają punktu przecięcia.");
        }
        double x = (p1.b * p2.c - p2.b * p1.c) / det;
        double y = (p2.a * p1.c - p1.a * p2.c) / det;
        return new Punkt(x, y);
    }

    @Override
    public String toString() {
        return String.format("%.2fx + %.2fy + %.2f = 0", a, b, c);
    }
}
