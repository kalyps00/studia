#include "csapp.h"

bool f_lock(const char *path)
{
    if (access(path, F_OK) == 0)
        return false;
    (void)Open(path, O_CREAT | O_WRONLY, 0700);
    return true;
}

void f_unlock(const char *path)
{
    Unlink(path);
}

bool f_lock(const char *path)
{
    // O_EXCL -> jeżeli plik istnieje, to open zwróci błąd
    // tymsamym sprawdzamy czy sitnieje i otworzenie jako 1 operacja atomowa
    int fd = open(path, O_CREAT | O_EXCL | O_WRONLY, 0700);
    if (fd < 0)
        return false;
    Close(fd); // zeby deskryptory nie wyciekaly, zamykamy deskryptor
    return true;
}
int main(void)
{
    const char *lock = "/tmp/test.lock";
    unlink(lock); // sprzątanie przed testem

    Fork(); // od teraz kod poniżej wykonują 2 procesy równolegle

    for (int i = 0; i < 10000; i++)
    {
        while (!f_lock(lock))
            ; // aktywne czekanie na blokadę
        f_unlock(lock);
    }
    return 0;
}