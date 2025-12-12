import numpy as np
import matplotlib.pyplot as plt


def generate_key(shape):
    return np.random.randint(0, 256, shape, dtype=np.uint8)


def encrypt_xor(image, key):
    return np.bitwise_xor(image, key)


def decrypt_xor(encrypted_image, key):
    return encrypt_xor(encrypted_image, key)


def encrypt_modulo(image, key):
    return (image.astype(np.uint16) + key.astype(np.uint16)) % 256


def decrypt_modulo(encrypted_image, key):
    return (encrypted_image.astype(np.int16) - key.astype(np.int16)) % 256


original_img = plt.imread("saturn.jpg")
height, width, channels = original_img.shape

key_img = generate_key(original_img.shape)

enc_xor = encrypt_xor(original_img, key_img)
dec_xor = decrypt_xor(enc_xor, key_img)

enc_mod = encrypt_modulo(original_img, key_img)
dec_mod = decrypt_modulo(enc_mod, key_img)

fig, axes = plt.subplots(2, 4, figsize=(16, 8))


axes[0, 0].imshow(original_img)
axes[0, 0].set_title("Oryginał")
axes[0, 0].axis("off")

axes[0, 1].imshow(key_img)
axes[0, 1].set_title("Klucz")
axes[0, 1].axis("off")

axes[0, 2].imshow(enc_xor)
axes[0, 2].set_title("Zaszumiony (Metoda XOR)")
axes[0, 2].axis("off")

axes[0, 3].imshow(dec_xor)
axes[0, 3].set_title("Odszyfrowany (XOR)")
axes[0, 3].axis("off")

axes[1, 0].imshow(original_img)
axes[1, 0].set_title("Oryginał")
axes[1, 0].axis("off")

axes[1, 1].imshow(key_img)
axes[1, 1].set_title("Ten sam Klucz")
axes[1, 1].axis("off")

axes[1, 2].imshow(enc_mod)
axes[1, 2].set_title("Zaszumiony (Metoda Modulo +)")
axes[1, 2].axis("off")

axes[1, 3].imshow(dec_mod)
axes[1, 3].set_title("Odszyfrowany (Modulo -)")
axes[1, 3].axis("off")

plt.tight_layout()
plt.show()
