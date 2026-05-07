
## Struktura plików
* `include/` - pliki nagłówkowe (`*.h`) definiujące publiczne interfejsy modułów.
* `src/main.c` - punkt wejścia programu, inicjalizacja generatora liczb pseudolosowych i wywołanie głównej pętli.
* `src/logic.c` - hermetyczny rdzeń aplikacji. Zawiera logikę domeny:
  * Alokację i zwalnianie struktury `GameState`.
  * Algorytmy przesuwania i scalania kafelków na planszy.
  * Obrót macierzy (optymalizacja kodu dla ruchów we wszystkich kierunkach).
* `src/io.c` - oddzielona warstwa operacji dyskowych. Odpowiada za bezpieczny zapis (`save_game`) i odczyt (`load_game`) stanu programu.
* `src/ui.c` - logika interfejsu graficznego (SDL2) odizolowana od rdzenia gry. Obsługuje pętlę zdarzeń, renderowanie widoku, typografię oraz weryfikację kursora myszy.

## Zarządzanie pamięcią
Kluczowa struktura `GameState` przechowująca m.in. wskaźnik na wskaźnik `int **board` jest tworzona dynamicznie funkcją `init_game()`. Każda alokacja `malloc` posiada swój odpowiednik zwalniający `free` w funkcji `free_game()`, co eliminuje wycieki pamięci. Moduł interfejsu odpowiedzialnie zarządza zasobami SDL (tekstury, powierzchnie, czcionki), niszcząc je po użyciu.