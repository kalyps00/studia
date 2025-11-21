import requests
from bs4 import BeautifulSoup
import re
from collections import Counter
import threading
import time

urls = ["https://www.forbes.pl/", "https://uwr.edu.pl/", "https://www.youtube.com/"]
lock = threading.Lock()


def scrape(url):
    try:
        response = requests.get(url, timeout=10)
        response.raise_for_status()
        soup = BeautifulSoup(response.text, features="html.parser")
        return soup.get_text(separator=" ")
    except Exception:
        return ""


def cnt_words(counter, index, url):
    for word, cnt in counter.items():
        if not word:
            continue
        with lock:  # chaneg
            entry = index.setdefault(word, {"total": 0, "pages": {}})
            entry["total"] += cnt
            entry["pages"][url] = cnt


def worker(url, index):
    text = scrape(url)
    words = re.findall(r"\w+", text.lower())
    cnt_words(Counter(words), index, url)


def make_index(urls):
    index = {}
    threads = []
    for url in urls:
        t = threading.Thread(target=worker, args=(url, index))
        threads.append(t)
        t.start()
    for t in threads:
        t.join()

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
    start_time = time.time()

    index = make_index(urls)
    word, total = most_common_word(index)

    print(f"Most common word: {word}, occurrences: {total}")
    print("Pages with this word:", pages_with_word(index, word))

    end_time = time.time()
    print(f"Execution time: {end_time - start_time:.2f} seconds")
