package wyrażenia;

public abstract class Wyrazenie implements Obliczalny {
    
    public static Wyrazenie suma(Wyrazenie... wyr) {
        if (wyr.length == 0) {
            return new Liczba(0.0);
        }
        Wyrazenie result = wyr[0];
        for (int i = 1; i < wyr.length; i++) {
            result = new Dodaj(result, wyr[i]);
        }
        return result;
    }
    
    public static Wyrazenie iloczyn(Wyrazenie... wyr) {
        if (wyr.length == 0) {
            return new Liczba(1.0);
        }
        Wyrazenie result = wyr[0];
        for (int i = 1; i < wyr.length; i++) {
            result = new Mnoz(result, wyr[i]);
        }
        return result;
    }
}
