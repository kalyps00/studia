from collections import Counter
import matplotlib.pyplot as plt
from wordcloud import WordCloud

# Rozszerzona lista polskich stopwords
STOPWORDS = {
    "a", "mu", "i", "oraz", "na", "w", "z", "się", "że", "to", "nie", "do", "jak", "o", "jest", 
    "ale", "po", "czy", "tak", "co", "dla", "dla", "za", "od", "by", "wśród", "tym", 
    "może", "jakże", "też", "jestem", "już", "mówi", "o", "więc", "bardziej", "bardzo", 
    "wszystko", "nic", "tutaj", "na", "przez", "dlaczego", "ponieważ", "każdy", "czyli", 
    "tu", "tam", "nas", "jej", "jego", "go", "jej", "mój", "mój", "nasz", "wasz", 
    "ich", "my", "wy", "ja", "ty", "on", "ona", "ono", "się", "na", "po", "pod", 
    "także", "choć", "aż", "innych", "tego", "zawsze", "teraz", "też", "gdy", "dlatego"
}

# Wczytanie pliku i usunięcie stopwords
with open("1984.txt", "r", encoding="utf-8") as file:
    text = file.read().lower()

words = [word for word in text.split() if word not in STOPWORDS]
word_counts = Counter(words)

# Generowanie chmury słów
wordcloud = WordCloud(width=800, height=400, background_color="white").generate_from_frequencies(word_counts)

# Wyświetlanie chmury słów
plt.figure(figsize=(10, 5))
plt.imshow(wordcloud, interpolation="bilinear")
plt.axis("off")
plt.show()
