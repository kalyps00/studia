import figury.*;

public class Main {
    public static void main(String[] args) {
        // Test Punkt
        Punkt p = new Punkt(1, 2);
        System.out.println("Punkt: " + p);
        Wektor v = new Wektor(3, 4);
        p.przesun(v);
        System.out.println("Punkt po przesunięciu: " + p);
        p.obroc(new Punkt(0, 0), Math.PI / 2);
        System.out.println("Punkt po obrocie o 90° wokół (0,0): " + p);
        Prosta prosta = new Prosta(1, -1, 0);
        p.odbij(prosta);
        System.out.println("Punkt po odbiciu względem prostej x-y=0: " + p);

        // Test Wektor
        Wektor v2 = new Wektor(-1, 2);
        Wektor v3 = Wektor.zloz(v, v2);
        System.out.println("Złożenie wektorów: " + v3);

        // Test Prosta
        Prosta p2 = new Prosta(2, -2, 1);
        System.out.println("Czy proste równoległe: " + Prosta.rownolegle(prosta, p2));
        System.out.println("Czy proste prostopadłe: " + Prosta.prostopadle(prosta, new Prosta(1, 1, 0)));
        try {
            Punkt przeciecie = Prosta.przeciecie(prosta, new Prosta(1, 1, 0));
            System.out.println("Punkt przecięcia: " + przeciecie);
        } catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
        }

        // Test Odcinek
        Odcinek odc = new Odcinek(new Punkt(0, 0), new Punkt(1, 1));
        System.out.println("Odcinek: " + odc);
        odc.przesun(new Wektor(1, 0));
        System.out.println("Odcinek po przesunięciu: " + odc);
        odc.obroc(new Punkt(0, 0), Math.PI / 2);
        System.out.println("Odcinek po obrocie: " + odc);
        odc.odbij(new Prosta(0, 1, 0));
        System.out.println("Odcinek po odbiciu względem osi OX: " + odc);

        // Test Trojkat
        Trojkat t = new Trojkat(new Punkt(0, 0), new Punkt(1, 0), new Punkt(0, 1));
        System.out.println("Trojkat: " + t);
        t.przesun(new Wektor(1, 1));
        System.out.println("Trojkat po przesunięciu: " + t);
        t.obroc(new Punkt(0, 0), Math.PI / 2);
        System.out.println("Trojkat po obrocie: " + t);
        t.odbij(new Prosta(1, 0, 0));
        System.out.println("Trojkat po odbiciu względem osi OY: " + t);
    }
}
