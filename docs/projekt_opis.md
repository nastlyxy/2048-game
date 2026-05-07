# Specyfikacja Projektu: Gra Logiczna "2048"

## Informacje ogólne
Projekt semestralny z przedmiotu Programowanie Niskopoziomowe w C. Głównym celem projektu jest implementacja klasycznej gry logicznej 2048 w rozszerzonym wariancie z planszą 5x5. Projekt spełnia wszystkie wymagania na ocenę 5.0 (Premium).

## Zrealizowane funkcjonalności
* **Dynamiczne zarządzanie pamięcią:** Stan gry i plansza (tablica dwuwymiarowa) są alokowane dynamicznie. Brak wycieków pamięci został potwierdzony narzędziem Valgrind (0 bytes in use at exit).
* **Zaawansowany interfejs graficzny (GUI):** Zastosowano bibliotekę SDL2 oraz SDL2_ttf do płynnego renderowania okna gry, kolorowych kafelków i typografii.
* **Pełna kontrola graficzna i "inteligentny kursor":** Aplikacja na bieżąco weryfikuje dopuszczalność ruchów. Po najechaniu myszą na interaktywne przyciski kierunkowe, system komunikuje się z warstwą logiczną i zmienia ikonę kursora (wskaźnik/zakaz), blokując wykonanie błędnych akcji.
* **Operacje plikowe (I/O):** Możliwość zapisu (klawisz 'S') i odczytu (klawisz 'L') aktualnego stanu gry do pliku tekstowego, co pozwala na kontynuację przerwanej rozgrywki.
* **Architektura modularna:** Kod został podzielony na hermetyczne moduły (logika, wejście/wyjście, interfejs, plik główny).

## Wymagania systemowe
* Kompilator GCC
* Program `make`
* Biblioteki: `libsdl2-dev`, `libsdl2-ttf-dev`