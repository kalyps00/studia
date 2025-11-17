import obliczenia.Wymierna;
import rozgrywka.Gra;
import rozgrywka.exceptions.*;

import java.io.FileInputStream;
import java.io.IOException;
import java.time.Duration;
import java.time.Instant;
import java.util.Locale;
import java.util.Scanner;
import java.util.logging.LogManager;
import java.util.logging.Logger;

public class Zgadywanka {
    private static final Logger logger = Logger.getLogger(Zgadywanka.class.getName());

    public static void main(String[] args) {
        try (FileInputStream fis = new FileInputStream("logging.properties")) {
            LogManager.getLogManager().readConfiguration(fis);
        } catch (IOException e) {
            System.err.println("Nie udało się wczytać logging.properties: " + e.getMessage());
        }

        Scanner sc = null;
        try {
            sc = new Scanner(System.in).useLocale(Locale.US);
            System.out.print("Witaj! Podaj swoje imię: ");
            String imie = sc.nextLine().trim();
            logger.info("Gracz: " + imie);

            Gra gra = new Gra();
            int zakres = 0;
            while (true) {
                try {
                    System.out.print("Podaj zakres (liczba całkowita z przedziału [5,20]): ");
                    String line = sc.nextLine().trim();
                    zakres = Integer.parseInt(line);
                    gra.start(zakres);
                    break;
                } catch (NumberFormatException nfe) {
                    System.out.println("To nie jest poprawna liczba całkowita, spróbuj ponownie.");
                } catch (IllegalArgumentException iae) {
                    System.out.println("Błędny zakres: " + iae.getMessage());
                } catch (AssertionError ae) {
                    System.err.println("Asercja nie powiodła się (wylosowany licznik >= mianownik). Program kończy działanie.");
                    logger.severe("Asercja startu gry nie powiodła się: " + ae.getMessage());
                    return;
                }
            }

            logger.info("Rozpoczęto grę. Zakres=" + zakres + ", max prób=" + gra.getMaksIlośćPrób());
            Instant start = Instant.now();

            System.out.println("Rozpoczęto grę. Masz maksymalnie " + gra.getMaksIlośćPrób() + " prób.");
            System.out.println("Wpisz ułamek w formacie a/b (np. 3/7), lub 'poddaj' by się poddać.");

            while (!gra.isFinished()) {
                System.out.print("Twoja próba: ");
                String attempt = sc.nextLine().trim();
                if (attempt.equalsIgnoreCase("poddaj") || attempt.equalsIgnoreCase("quit")) {
                    logger.info(imie + " poddał się.");
                    System.out.println("Poddajesz się. Koniec gry.");
                    break;
                }
                try {
                    Wymierna guess = parseFraction(attempt, zakres);
                    logger.info(imie + " zgadł: " + guess + " (próba " + (gra.getLicznikPrób()+1) + ")");
                    int res = gra.zgadnij(guess);
                    if (res == -2) {
                        System.out.println("Brak dostępnych prób.");
                        break;
                    } else if (res == 0) {
                        System.out.println("Zgadłeś! To jest " + guess);
                        logger.info(imie + " wygrał. Trafił: " + guess + " po " + gra.getLicznikPrób() + " próbach.");
                        break;
                    } else if (res < 0) {
                        System.out.println("Za mało.");
                    } else {
                        System.out.println("Za dużo.");
                    }
                } catch (InvalidFormatException ife) {
                    System.out.println("Błędny format ułamka: " + ife.getMessage());
                } catch (DenominatorTooLargeException dtle) {
                    System.out.println("Mianownik za duży: " + dtle.getMessage());
                } catch (OutOfRangeException ore) {
                    System.out.println("Ułamek poza (0,1): " + ore.getMessage());
                } catch (Exception e) {
                    System.out.println("Wystąpił błąd: " + e.getMessage());
                    logger.warning("Błąd podczas próby: " + e);
                }
            }

            Instant koniec = Instant.now();
            Duration czas = Duration.between(start, koniec);
            logger.info("Czas trwania gry: " + czas.toSeconds() + " s, próby: " + gra.getLicznikPrób());

            if (gra.isOdgadniete()) {
                System.out.println("Gratulacje! Wygrałeś.");
            } else if (gra.getLicznikPrób() >= gra.getMaksIlośćPrób()) {
                System.out.println("Wyczerpałeś wszystkie próby. Przegrałeś.");
                logger.info("Gracz przegrał. Wylosowana liczba: " + gra.getLiczba());
            } else {
                System.out.println("Koniec gry.");
            }
        } finally {
            if (sc != null) sc.close();
        }
    }

    private static Wymierna parseFraction(String s, int maxDenominator) throws InvalidFormatException, DenominatorTooLargeException, OutOfRangeException {
        if (!s.contains("/")) throw new InvalidFormatException("Oczekiwano formatu a/b");
        String[] parts = s.split("/");
        if (parts.length != 2) throw new InvalidFormatException("Zbyt wiele lub zbyt mało części po podziale '/'");
        try {
            int a = Integer.parseInt(parts[0].trim());
            int b = Integer.parseInt(parts[1].trim());
            if (b > maxDenominator) throw new DenominatorTooLargeException("Mianownik " + b + " jest większy niż dopuszczalny " + maxDenominator);
            Wymierna w = new Wymierna(a, b);
            // (0,1)
            if (!(w.compareTo(new Wymierna(0,1)) > 0 && w.compareTo(new Wymierna(1,1)) < 0)) {
                throw new OutOfRangeException("Ułamek musi należeć do (0,1): podano " + w);
            }
            return w;
        } catch (NumberFormatException nfe) {
            throw new InvalidFormatException("Elementy nie są poprawnymi liczbami całkowitymi");
        } catch (IllegalArgumentException iae) {
            throw new InvalidFormatException("Niepoprawny ułamek: " + iae.getMessage());
        }
    }
}
