import random
import re

# Lista polskich stopwordów
stopwords = {
    "i", "oraz", "a", "ale", "lub", "że", "to", "na", "po", "do", "z", "w", "się", 
    "nie", "o", "jak", "tak", "jest", "by", "dla", "za", "ten", "ta", "te", "być"
}

def clean_word(word):
    """Oczyść słowo z niechcianych znaków."""
    return re.sub(r'[^a-ząćęłńóśźż]', '', word.lower())

def get_valid_words(filename):
    """Przetwarzaj plik i zwróć listę 5-literowych słów (bez stopwordów)."""
    with open(filename, 'r', encoding='utf-8') as f:
        words = re.findall(r'\b\w+\b', f.read().lower())
    return [
        clean_word(word) for word in words 
        if clean_word(word) not in stopwords and len(clean_word(word)) == 5
    ]

def play_wordle(word_list):
    """Gra w Wordle."""
    secret_word = random.choice(word_list)
    attempts = 6
    print("Witaj w grze Wordle! Masz 6 prób, aby zgadnąć 5-literowe słowo.")
    
    for _ in range(attempts):
        guess = input("Podaj słowo: ").strip().lower()
        
        if len(guess) != len(secret_word):
            print(f"Słowo musi mieć {len(secret_word)} liter. Spróbuj ponownie!")
            continue
        
        # Ocena zgadywanego słowa
        result = []
        for g_char, s_char in zip(guess, secret_word):
            if g_char == s_char:
                result.append(f"[{g_char.upper()}]")  # Zgadza się dokładnie
            elif g_char in secret_word:
                result.append(f"({g_char})")          # Zgadza się litera, ale nie pozycja
            else:
                result.append(g_char)                # Nie zgadza się
        
        print(" ".join(result))
        
        if guess == secret_word:
            print("Gratulacje! Zgadłeś hasło!")
            return
    
    print(f"Niestety, przegrałeś! Hasłem było: {secret_word}")

if __name__ == "__main__":
    word_list = get_valid_words("1984.txt")
    if not word_list:
        print("Nie znaleziono odpowiednich słów do gry.")
    else:
        play_wordle(word_list)
