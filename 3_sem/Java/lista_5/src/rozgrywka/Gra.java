package rozgrywka;

import obliczenia.Wymierna;

/**
 * Reprezentuje stan pojedynczej gry.
 */
public class Gra {
    private int zakres;
    private Wymierna liczba;
    private int maksIlośćPrób;
    private int licznikPrób;
    private boolean odgadniete;

    public Gra() {
        this.zakres = 0;
        this.liczba = null;
        this.maksIlośćPrób = 0;
        this.licznikPrób = 0;
        this.odgadniete = false;
    }

    /**
     * Rozpoczyna rozgrywkę według polecenia 
     */
    public void start(int z) {
        if (z < 5 || z > 20) throw new IllegalArgumentException("Zakres poza dopuszczalnym przedziałem");
        zakres = z;
        int licz = (int) (Math.random() * zakres) + 1;
        int mian = (int) (Math.random() * zakres) + 1;
        
        liczba = new Wymierna(licz, mian);
        maksIlośćPrób = (int) Math.ceil(3.0 * Math.log(zakres));
        licznikPrób = 0;
        odgadniete = false;
        assert licz < mian : "Wylosowany fragment nie spełnia 0 < licznik < mianownik";
    }

    public int getZakres() { return zakres; }
    public Wymierna getLiczba() { return liczba; }
    public int getMaksIlośćPrób() { return maksIlośćPrób; }
    public int getLicznikPrób() { return licznikPrób; }
    public boolean isOdgadniete() { return odgadniete; }

    /**
     * Wykonaj próbę zgadywania podaną przez użytkownika.
     * Zwraca -1 gdy za mało, 1 gdy za dużo, 0 gdy trafiono.
     */
    public int zgadnij(Wymierna probe) {
        if (licznikPrób >= maksIlośćPrób) return -2; // brak prób
        licznikPrób++;
        int cmp = probe.compareTo(liczba);
        if (cmp == 0) {
            odgadniete = true;
            return 0;
        }
        return cmp < 0 ? -1 : 1;
    }

    public boolean isFinished() {
        return odgadniete || licznikPrób >= maksIlośćPrób;
    }
}
