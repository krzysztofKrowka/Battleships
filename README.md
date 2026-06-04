# Gra w Statki (Battleships)

Klasyczna gra w statki (Battleships) zaimplementowana w języku C++ jako projekt akademicki na ocenę 5.0. Rozgrywka toczy się w trybie tekstowym w terminalu przeciwko komputerowi (AI).

## 🚀 Funkcjonalności projektu (Wkład własny)

Projekt zawiera pełną, spójną mechanikę gry wzbogaconą o zaawansowane reguły i elementy niestandardowe:
* **System współrzędnych 1-10:** Plansza odwzorowana w klasycznym stylu (Wiersze: `A-J`, Kolumny: `1-10`), z pełnym parsowaniem wejścia użytkownika (obsługa formatu np. `A8` lub `J10`).
* **Pełnoprawne zasady rozstawiania statków:** Statki generowane przez komputer oraz ustawiane przez gracza **nie mogą stykać się bokami ani rogami (skosami)**.
* **Automatyczne odkrywanie pól wokół zatopionego statku:** Po zniszczeniu wszystkich masztów danego statku, gra automatycznie oznacza kafelki wokół niego jako "ostrzelane" (pudła), ułatwiając dalszą rozgrywkę.
* **Efekty dźwiękowe (Biblioteka niestandardowa):** Wykorzystanie zewnętrznej biblioteki audio do odtwarzania dźwięków wystrzałów, trafień i chybień.
* **Pełna kolorystyka ANSI:** Czytelne rozróżnienie własnych statków (zielony), trafień (czerwony) oraz chybień (niebieski).

## 📦 Użyte biblioteki

1. **Biblioteka standardowa C++ (STL):** `<iostream>`, `<vector>`, `<thread>`, `<chrono>`, `<cstdlib>`, `<ctime>`.
2. **Biblioteka niestandardowa (Zewnętrzna):** **miniaudio.h** (v1.0+) – Lekka biblioteka audio (single-header) użyta do obsługi efektów dźwiękowych w grze bez narzucania ciężkich zależności systemowych.

## 🛠️ Instrukcja uruchomienia i obsługi

Program obsługuje parametry startowe z poziomu wiersza poleceń (terminala).

### Wyświetlenie pomocy (-h / --help)
Aby wyświetlić instrukcję i zasady gry w terminalu, należy uruchomić program z odpowiednią flagą:

```bash
.\Battleships.exe -h
```

lub

```bash
.\Battleships.exe --help
```

### Normalne uruchomienie gry
Aby po prostu zagrać, uruchom program bez żadnych argumentów z poziomu terminala lub środowiska IDE (np. CLion):

```bash
.\Battleships.exe
```

## 🎮 Jak grać?

1. **Faza rozstawiania:** Gra poprosi Cię o podanie współrzędnych początku i końca dla 7 statków o różnych długościach (5, 4, 3, 2, 2, 1, 1). Wpisz je oddzielone spacją, np.: `A1 A5`.
2. **Faza bitwy:** Na zmianę z komputerem wybieracie jedną kratkę, w którą oddawany jest strzał (np. `G7`).
3. **Cel gry:** Zatopienie wszystkich 20 masztów przeciwnika zanim on zrobi to z Twoją flotą.

## 🤖 Informacja o użyciu AI
Zgodnie z regulaminem zaliczenia przedmiotu, autor oświadcza, że podczas tworzenia projektu posiłkował się asystentem AI w celu:
* Skonstruowania algorytmu przeszukiwania sąsiednich kafelków (odkrywanie pól wokół zatopionego statku),
* Integracji zewnętrznej biblioteki `miniaudio.h` z plikiem konfiguracyjnym CMake,
* Zoptymalizowania bufora strumienia wejściowego `std::cin`.

Wkład własny obejmuje architekturę klas, logikę pętli gry oraz integrację wszystkich elementów w spójną całość.