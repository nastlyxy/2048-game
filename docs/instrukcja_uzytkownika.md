# Instrukcja Użytkownika

## Kompilacja i uruchomienie
Aby skompilować grę, otwórz terminal w głównym katalogu projektu i wpisz polecenie:
`make`

Następnie uruchom aplikację poleceniem:
`./game`

## Zasady gry
Celem gry jest przesuwanie kafelków na planszy 5x5. Kiedy dwa kafelki z taką samą wartością zderzą się podczas przesunięcia, łączą się w jeden kafelek o wartości równej ich sumie. Po każdym ruchu na losowym pustym polu pojawia się nowa liczba (2 lub 4). Gra kończy się, gdy plansza się zapełni i nie będzie możliwy żaden ruch.

## Sterowanie
Gra oferuje dwa niezależne sposoby sterowania:

1. **Sterowanie klawiaturą:**
   * Strzałka w lewo / w prawo / w górę / w dół - przesunięcie kafelków w wybranym kierunku.
   * Klawisz S - szybki zapis stanu gry.
   * Klawisz L - wczytanie zapisanego stanu gry.

2. **Sterowanie myszą (inteligentny interfejs):**
   * Na dole ekranu znajduje się panel z przyciskami kierunkowymi (L, D, U, R).
   * Najedź kursorem na przycisk. System sprawdzi, czy ruch w danym kierunku jest dozwolony (np. czy kafelki nie są zablokowane na krawędzi).
   * Jeśli ruch jest możliwy: przycisk zaświeci się na zielono, a kursor zmieni się w dłoń. Kliknij lewym przyciskiem myszy, aby wykonać ruch.
   * Jeśli ruch jest zablokowany: przycisk zaświeci się na czerwono, a kursor zmieni się w znak zakazu. Kliknięcie zostanie zignorowane.

Zakończenie działania aplikacji odbywa się poprzez standardowe zamknięcie okna programu (X).