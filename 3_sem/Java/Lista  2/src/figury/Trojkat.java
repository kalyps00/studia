package figury;

public class Trojkat {
    private Punkt p1;
    private Punkt p2;
    private Punkt p3;

    public Trojkat(Punkt p1, Punkt p2, Punkt p3) {
        if (p1 == null || p2 == null || p3 == null) {
            throw new IllegalArgumentException("Punkty nie mogą być null.");
        }
        if (areCollinear(p1, p2, p3)) {
            throw new IllegalArgumentException("Punkty są współliniowe.");
        }
        if (equals(p1, p2) || equals(p1, p3) || equals(p2, p3)) {
            throw new IllegalArgumentException("Punkty muszą być różne.");
        }
        this.p1 = new Punkt(p1.getX(), p1.getY());
        this.p2 = new Punkt(p2.getX(), p2.getY());
        this.p3 = new Punkt(p3.getX(), p3.getY());
    }

    private boolean equals(Punkt a, Punkt b) {
        return a.getX() == b.getX() && a.getY() == b.getY();
    }

    private boolean areCollinear(Punkt a, Punkt b, Punkt c) {
        return (b.getX() - a.getX()) * (c.getY() - a.getY()) - (b.getY() - a.getY()) * (c.getX() - a.getX()) == 0;
    }

    public Punkt getP1() { return new Punkt(p1.getX(), p1.getY()); }
    public Punkt getP2() { return new Punkt(p2.getX(), p2.getY()); }
    public Punkt getP3() { return new Punkt(p3.getX(), p3.getY()); }

    public void przesun(Wektor v) {
        p1.przesun(v);
        p2.przesun(v);
        p3.przesun(v);
    }

    public void obroc(Punkt p, double kat) {
        p1.obroc(p, kat);
        p2.obroc(p, kat);
        p3.obroc(p, kat);
    }

    public void odbij(Prosta prosta) {
        p1.odbij(prosta);
        p2.odbij(prosta);
        p3.odbij(prosta);
    }

    @Override
    public String toString() {
        return String.format("Trojkat[%s, %s, %s]", p1, p2, p3);
    }
}
