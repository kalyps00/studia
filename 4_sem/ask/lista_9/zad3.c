
void compute2(long *a, long *b, long k) {
    long n = 1 << k;

    for (long i = 0; i < n; i++) {
        a[i*n] = 0;
        a[i] = 0;
    }

    for (long i = 1; i < n; i++) {
        for (long j = 1; j < n; j++) {
            a[j*n + i] = i * j;
        }
    }

    for (long i = 1; i < n; i++) {
        for (long j = 1; j < n; j++) {
            b[i*n + j] = a[i*n + j] - a[(i-1)*n + (j-1)];
        }
    }
}



void compute2(long *a, long *b, long k) {
    long n = 1 << k;

    for (long i = 0; i < n; i++) {
        a[i * n] = 0;
        a[i] = 0;
    }

    // idziemy wierszami: a[i*n + j]
    for (long i = 1; i < n; i++) {
        for (long j = 1; j < n; j++) {
            a[i * n + j] = i * j;
        }
    }

    for (long i = 1; i < n; i++) {
        for (long j = 1; j < n; j++) {
            b[i * n + j] = a[i * n + j] - a[(i - 1) * n + (j - 1)];
        }
    }
}


void compute2(long *a, long *b, long k) {
    long n = 1 << k;

    for (long i = 0; i < n; i++) {
        a[i * n] = 0;
        a[i] = 0;
    }

    // Dwie operacje wewnątrz jednej pętli
    for (long i = 1; i < n; i++) {
        for (long j = 1; j < n; j++) {
            a[i * n + j] = i * j;
            b[i * n + j] = a[i * n + j] - a[(i - 1) * n + (j - 1)];
        }
    }
}

void compute2(long *a, long *b, long k) {
    long n = 1 << k;

    for (long i = 0; i < n; i++) {
        a[i * n] = 0;
        a[i] = 0;
    }

    for (long i = 1; i < n; i++) {
        for (long j = 1; j < n; j++) {
            a[i * n + j] = i * j;
            // Zastąpienie odczytu z tablicy obliczeniami bezpośrednio z indeksów
            b[i * n + j] = i + j - 1; 
        }
    }
}

void compute2(long *a, long *b, long k) {
    long n = 1 << k;

    for (long i = 0; i < n; i++) {
        a[i * n] = 0;
        a[i] = 0;
    }

    for (long i = 1; i < n; i++) {
        // Obliczamy offset wiersza raz dla całej pętli 'j'
        long in = i * n; 
        for (long j = 1; j < n; j++) {
            a[in + j] = i * j;
            b[in + j] = i + j - 1;
        }
    }
}