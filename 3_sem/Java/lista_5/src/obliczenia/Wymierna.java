package obliczenia;

/**
 * Klasa reprezentująca liczbę wymierną w postaci nieskracalnego ułamka.
 * Reprezentacja: licznik/mianownik, gdzie mianownik zawsze > 0.
 */
public class Wymierna implements Comparable<Wymierna> {
    private int licznik;
    private int mianownik = 1;

    /**
     * Tworzy 0/1.
     */
    public Wymierna() {
        this(0, 1);
    }

    /**
     * Tworzy k/1 (deleguje do konstruktora dwuargumentowego).
     *
     * @param k wartość licznika; tworzy ułamek postaci k/1
     */
    public Wymierna(int k) {
        this(k, 1);
    }

    /**
     * Tworzy liczbę k/m w postaci nieskracalnego ułamka.
     * @throws IllegalArgumentException gdy mianownik == 0
    *
    * @param k licznik ułamka
    * @param m mianownik ułamka (nie może być 0)
     */
    public Wymierna(int k, int m) {
        if (m == 0) throw new IllegalArgumentException("Mianownik nie może być 0");
        // znak -> licznik
        if (m < 0) {
            k = -k;
            m = -m;
        }
        if (k == 0) {
            this.licznik = 0;
            this.mianownik = 1;
            return;
        }
        int g = nwd(Math.abs(k), Math.abs(m));
        this.licznik = k / g;
        this.mianownik = m / g;
    }

    private static int nwd(int a, int b) {
        if (b == 0) return a;
        return nwd(b, a % b);
    }

    /**
     * Zwraca wartość licznika ułamka.
     * @return licznik
     */
    public int getLicznik() {
        return licznik;
    }

    /**
     * Zwraca wartość mianownika ułamka.
     * @return mianownik
     */
    public int getMianownik() {
        return mianownik;
    }

    @Override
    public String toString() {
        return licznik + "/" + mianownik;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Wymierna w = (Wymierna) obj;
        return this.licznik == w.licznik && this.mianownik == w.mianownik;
    }

    @Override
    public int compareTo(Wymierna o) {
        long left = (long) this.licznik * o.mianownik;
        long right = (long) o.licznik * this.mianownik;
        return Long.compare(left, right);
    }

    /**
     * Zwraca sumę dwóch ułamków a + b.
     * @param a pierwszy składnik
     * @param b drugi składnik
     * @return nowy obiekt {@code Wymierna} reprezentujący a+b
     */
    public static Wymierna dodaj(Wymierna a, Wymierna b) {
        long num = (long) a.licznik * b.mianownik + (long) b.licznik * a.mianownik;
        long den = (long) a.mianownik * b.mianownik;
        return fromLongs(num, den);
    }

    /**
     * Zwraca różnicę a - b.
     * @param a pierwszy składnik
     * @param b drugi składnik
     * @return wynik a-b jako {@code Wymierna}
     */
    public static Wymierna odejmij(Wymierna a, Wymierna b) {
        long num = (long) a.licznik * b.mianownik - (long) b.licznik * a.mianownik;
        long den = (long) a.mianownik * b.mianownik;
        return fromLongs(num, den);
    }

    /**
     * Zwraca iloczyn dwóch ułamków.
     * @param a pierwszy czynnik
     * @param b drugi czynnik
     * @return iloczyn a*b jako {@code Wymierna}
     */
    public static Wymierna mnoz(Wymierna a, Wymierna b) {
        long num = (long) a.licznik * b.licznik;
        long den = (long) a.mianownik * b.mianownik;
        return fromLongs(num, den);
    }

    /**
     * Dzieli a przez b.
     * @param a dzielna
     * @param b dzielnik
     * @return wynik a/b jako {@code Wymierna}
     * @throws ArithmeticException gdy próba dzielenia przez 0
     */
    public static Wymierna dziel(Wymierna a, Wymierna b) {
        if (b.licznik == 0) throw new ArithmeticException("Dzielenie przez zero");
        long num = (long) a.licznik * b.mianownik;
        long den = (long) a.mianownik * b.licznik;
        if (den < 0) { num = -num; den = -den; }
        return fromLongs(num, den);
    }

    private static Wymierna fromLongs(long num, long den) {
        if (den == 0) throw new ArithmeticException("Mianownik zero przy budowie ułamka");
        if (num == 0) return new Wymierna(0,1);
        long a = Math.abs(num);
        long b = Math.abs(den);
        long g = nwdLong(a, b);
        a /= g; b /= g;
        if (a > Integer.MAX_VALUE || b > Integer.MAX_VALUE) {
            throw new ArithmeticException("Przepełnienie przy konwersji ułamka do int");
        }
        int ai = (int) ( (num < 0) ? -a : a );
        int bi = (int) b;
        return new Wymierna(ai, bi);
    }

    private static long nwdLong(long a, long b) {
        if (b == 0) return a;
        return nwdLong(b, a % b);
    }
}
