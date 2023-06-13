# Lotnisko

Opis: tematem projektu jest stworzenie symulacji lotniksa z użuciem biblioteki ncurses. Są dwa pasy na lotnisku. Samoloty oczekują na lądowanie lub na start z lotniska.
Wątki: lądowanie samolotów na pasy oraz start samolotów
Zasobami: pasy

Sekcje krytyczne: operacja zwiększania liczby pasów

Zmienne warunkowe: liczba pasów, liczba samolotów

Deadlock: start/lądowanie samolotu kiedy pas jest zajęty  inny samolotem
