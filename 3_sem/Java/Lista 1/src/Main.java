import java.util.Scanner;
public class Main {
    // tablica z wybranymi liczbami rzymskimi
    private static final String[] rzymskie = {
            "M", "CM", "D", "CD", "C","XC", "L", "XL", "X", "IX", "V", "IV", "I"
    };
    // tablica z odpowiadającymi liczbom rzymskim wartościami
    private static final int[] arabskie = {
            1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1
    };
    public static String rzymska(int n){
        if(n<=0 || n>=4000){
            throw new IllegalArgumentException("rok " + n + " jest spoza zakresu");
        }
        StringBuilder rok = new StringBuilder();
        for(int i=0;i<arabskie.length;i++){
            while(n>= arabskie[i]){
                n-= arabskie[i];
                rok.append(rzymskie[i]);
            }
        }
        return rok.toString();
    }
    public static String patron(int rok) {
        int index = (rok - 2025) % 12 + 5;
        if (index < 0) index += 12;
        String[] tablica= {
                "szczur", "bawół", "tygrys","królik","smok","wąż","koń","owca","małpa","kurczak","pies","świnia"
        };
        return switch (index % 12) {
            case 0 -> tablica[0];
            case 1 -> tablica[1];
            case 2 -> tablica[2];
            case 3 -> tablica[3];
            case 4 -> tablica[4];
            case 5 -> tablica[5];
            case 6 -> tablica[6];
            case 7 -> tablica[7];
            case 8 -> tablica[8];
            case 9 -> tablica[9];
            case 10 -> tablica[10];
            case 11 -> tablica[11];
            default -> throw new IllegalStateException("Nieprawidłowy rok: " + rok);
        };
    }
    static void main() {
        Scanner input = new Scanner(System.in);
        System.err.print("Podaj imie: ");
        String imie = input.nextLine().trim();
        System.err.print("Podaj rok urodzenia: ");
        int rok = input.nextInt();

        System.out.println("Cześć " + imie + "!");
        System.out.println("Twój rok urodzenia w systemie rzymskim to: " + rzymska(rok));
        System.out.println("Twój patron to "+ patron(rok));

    }
}