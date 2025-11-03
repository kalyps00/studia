package figury;

public class Odcinek {
    private Punkt p1;
    private Punkt p2;

    public Odcinek(Punkt p1, Punkt p2) {
        if (p1 == null || p2 == null) {
            throw new IllegalArgumentException("Punkty nie mogą być null.");
        }
        if (p1.getX() == p2.getX() && p1.getY() == p2.getY()) {
            throw new IllegalArgumentException("Punkty muszą być różne.");
        }
        this.p1 = new Punkt(p1.getX(), p1.getY());
        this.p2 = new Punkt(p2.getX(), p2.getY());
    }

    public Punkt getP1() {
        return new Punkt(p1.getX(), p1.getY());
    }

    public Punkt getP2() {
        return new Punkt(p2.getX(), p2.getY());
    }

    public void przesun(Wektor v) {
        p1.przesun(v);
        p2.przesun(v);
    }

    public void obroc(Punkt p, double kat) {
        p1.obroc(p, kat);
        p2.obroc(p, kat);
    }

    public void odbij(Prosta prosta) {
        p1.odbij(prosta);
        p2.odbij(prosta);
    }

    @Override
    public String toString() {
        return String.format("Odcinek[%s, %s]", p1, p2);
    }
}
