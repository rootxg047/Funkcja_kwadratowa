#include <stdio.h>  // Do wypisywania na ekran (printf)
#include <stdlib.h> // Do obsługi błędów (exit)

int main(int argc, char *argv[]) {
    // argc - liczba argumentów (zawsze co najmniej 1, bo argv[0] to nazwa programu)
    // argv - tablica stringów z argumentami

    if (argc == 1) {
        // Brak argumentów - tryb interaktywny (na razie prosty komunikat)
        printf("Witaj! To narzędzie quad. Wpisz współczynniki: a b c\n");
        // Tu później dodamy czytanie z stdin
    } else if (argc == 4) {
        // Argumenty: quad a b c
        printf("Otrzymałem argumenty: a=%s, b=%s, c=%s\n", argv[1], argv[2], argv[3]);
        // Tu później parsowanie na double i obliczenia
    } else {
        // Błąd - zła liczba argumentów
        printf("Użycie: quad a b c  (lub quad -f plik.txt)\n");
        return 1;  // Zwróć 1, by wskazać błąd
    }

    return 0;  // Sukces
}
