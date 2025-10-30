w = input("Enter a word: ")
def is_palindrom(word):
    new_word = "".join(c.lower() for c in word if c.isalnum())
    return new_word == new_word[::-1]
print(is_palindrom(w))