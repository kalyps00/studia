import wyrażenia.*;

public class Main {
    public static void main(String[] args) {
        // Ustawienie wartości zmiennej x
        Zmienna.ustawWartość("x", 1.618);
        
        System.out.println("=== PROGRAM TESTOWY - WYRAŻENIA ARYTMETYCZNE ===");
        System.out.println("Zmienna x = 1.618\n");
        
        // Test 1: 7 + 5 * x - 1
        System.out.println("Test 1: 7 + 5 * x - 1");
        Wyrazenie w1 = new Odejmij(
            new Dodaj(
                new Liczba(7),
                new Mnoz(
                    new Liczba(5),
                    new Zmienna("x")
                )
            ),
            new Liczba(1)
        );
        System.out.println("Wyrażenie: " + w1);
        System.out.println("Wartość:   " + w1.oblicz());
        System.out.println();
        
        // Test 2: ~ (2 - x) * e
        System.out.println("Test 2: ~ (2 - x) * e");
        Wyrazenie w2 = new Mnoz(
            new Negacja(
                new Odejmij(
                    new Liczba(2),
                    new Zmienna("x")
                )
            ),
            Stała.E
        );
        System.out.println("Wyrażenie: " + w2);
        System.out.println("Wartość:   " + w2.oblicz());
        System.out.println();
        
        // Test 3: (3 * π - 1) / (! x + 5)
        System.out.println("Test 3: (3 * π - 1) / (! x + 5)");
        Wyrazenie w3 = new Dziel(
            new Odejmij(
                new Mnoz(
                    new Liczba(3),
                    Stała.Pi
                ),
                new Liczba(1)
            ),
            new Dodaj(
                new Odwrotność(
                    new Zmienna("x")
                ),
                new Liczba(5)
            )
        );
        System.out.println("Wyrażenie: " + w3);
        System.out.println("Wartość:   " + w3.oblicz());
        System.out.println();
        
        // Test 4: sin((x + 13) * π / (1 - x))
        System.out.println("Test 4: sin((x + 13) * π / (1 - x))");
        Wyrazenie w4 = new Sin(
            new Dziel(
                new Mnoz(
                    new Dodaj(
                        new Zmienna("x"),
                        new Liczba(13)
                    ),
                    Stała.Pi
                ),
                new Odejmij(
                    new Liczba(1),
                    new Zmienna("x")
                )
            )
        );
        System.out.println("Wyrażenie: " + w4);
        System.out.println("Wartość:   " + w4.oblicz());
        System.out.println();
        
        // Test 5: exp(5) + x * log(e, x)
        System.out.println("Test 5: exp(5) + x * log(e, x)");
        Wyrazenie w5 = new Dodaj(
            new Exp(
                new Liczba(5)
            ),
            new Mnoz(
                new Zmienna("x"),
                new Log(
                    Stała.E,
                    new Zmienna("x")
                )
            )
        );
        System.out.println("Wyrażenie: " + w5);
        System.out.println("Wartość:   " + w5.oblicz());
        System.out.println();
        
        // Testy metod statycznych suma() i iloczyn()
        System.out.println("=== TESTY METOD STATYCZNYCH ===");
        System.out.println("Test suma(1, 2, 3, 4): " + Wyrazenie.suma(
            new Liczba(1),
            new Liczba(2),
            new Liczba(3),
            new Liczba(4)
        ).oblicz());
        
        System.out.println("Test iloczyn(2, 3, 4): " + Wyrazenie.iloczyn(
            new Liczba(2),
            new Liczba(3),
            new Liczba(4)
        ).oblicz());
        
        System.out.println();
        
        // Testy pól statycznych
        System.out.println("=== TESTY PÓL STATYCZNYCH ===");
        System.out.println("Liczba.ZERO = " + Liczba.ZERO.oblicz());
        System.out.println("Liczba.JEDEN = " + Liczba.JEDEN.oblicz());
        System.out.println("Stała.Pi = " + Stała.Pi.oblicz());
        System.out.println("Stała.E = " + Stała.E.oblicz());
    }
}
