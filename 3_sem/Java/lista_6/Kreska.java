package lista_6;

import java.awt.*;

public class Kreska {
    protected Point poczatek, koniec;
    protected Color kolor;

    public Kreska(Point pocz, Point kon, Color kol) {
        this.poczatek = pocz;
        this.koniec = kon;
        this.kolor = kol;
    }

    public void rysuj(Graphics g) {
        g.setColor(kolor);
        g.drawLine(poczatek.x, poczatek.y, koniec.x, koniec.y);
    }
}