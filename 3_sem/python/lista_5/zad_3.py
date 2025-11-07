import requests
from bs4 import BeautifulSoup
import re
from collections import Counter

urls = ["https://www.forbes.pl/", "https://uwr.edu.pl/", "https://www.youtube.com/"]


def scrape(url):
    try:
        response = requests.get(url)
        response.raise_for_status()
        soup = BeautifulSoup(response.text, features="html.parser")
        return soup.get_text(separator=" ")
    except Exception:
        return ""


def cnt_words(counter, index, url):
    for word, cnt in counter.items():
        if not word:
            continue
        entry = index.setdefault(word, {"total": 0, "pages": {}})
        entry["total"] += cnt
        entry["pages"][url] = cnt


def make_index(urls):
    index = {}
    for url in urls:
        text = scrape(url)
        words = re.findall(r"\w+", text.lower())
        cnt_words(Counter(words), index, url)
    return index


def most_common_word(index) -> tuple[str | None, int]:
    if not index:
        return (None, 0)
    word, data = max(index.items(), key=lambda key_val: key_val[1]["total"])
    return (word, data["total"])


def pages_with_word(index, word) -> list[str]:
    if word not in index:
        return list("")
    return list(index.get(word.lower(), {})["pages"].keys())


if __name__ == "__main__":
    index = make_index(urls)
    word, total = most_common_word(index)

    print(f"Most common word: {word}, occurrences: {total}")
    print("Pages with this word:", pages_with_word(index, word))
