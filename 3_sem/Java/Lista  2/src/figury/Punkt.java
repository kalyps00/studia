package figury;

public class Punkt {
    private double x;
    private double y;

    public Punkt(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    public void przesun(Wektor v) {
        this.x += v.dx;
        this.y += v.dy;
    }

    public void obroc(Punkt p, double kat) {
        double dx = x - p.x;
        double dy = y - p.y;
        double cos = Math.cos(kat);
        double sin = Math.sin(kat);
        this.x = p.x + dx * cos - dy * sin;
        this.y = p.y + dx * sin + dy * cos;
    }

    public void odbij(Prosta prosta) {
        // Odbicie punktu względem prostej Ax + By + C = 0
        double d = (prosta.a * x + prosta.b * y + prosta.c) / (prosta.a * prosta.a + prosta.b * prosta.b);
        this.x = x - 2 * prosta.a * d;
        this.y = y - 2 * prosta.b * d;
    }

    @Override
    public String toString() {
        return String.format("(%.2f, %.2f)", x, y);
    }
}
