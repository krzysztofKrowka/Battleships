//
// Created by Krzysztof on 4.06.2026.
//

#include "Game.h"
#include <stdexcept>
#include <time.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>

void revealSurroundingIfSunk(std::vector<std::vector<Tile>>& map, int r, int c) {
    std::vector<std::pair<int, int>> shipTiles;
    shipTiles.push_back({r, c});

    // Przeszukujemy 4 kierunki, aby znaleźć wszystkie segmenty tego statku
    int dirs[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    for (int i = 0; i < 4; ++i) {
        int nr = r + dirs[i][0];
        int nc = c + dirs[i][1];
        while (nr >= 0 && nr < 10 && nc >= 0 && nc < 10 && map[nr][nc].isShip) {
            shipTiles.push_back({nr, nc});
            nr += dirs[i][0];
            nc += dirs[i][1];
        }
    }

    // Sprawdzamy, czy wszystkie segmenty znalezionego statku są trafione
    bool isSunk = true;
    for (const auto& tile : shipTiles) {
        if (!map[tile.first][tile.second].isShot) {
            isSunk = false;
            break;
        }
    }

    // Jeśli cały statek zatonął, zaznaczamy wszystkie sąsiednie pola (3x3 dla każdego segmentu) jako ostrzelane
    if (isSunk) {
        for (const auto& tile : shipTiles) {
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    int nr = tile.first + dr;
                    int nc = tile.second + dc;
                    if (nr >= 0 && nr < 10 && nc >= 0 && nc < 10) {
                        if (!map[nr][nc].isShip) {
                            map[nr][nc].isShot = true; // Automatyczne „pudło” wokół zatopionego statku
                        }
                    }
                }
            }
        }
    }
}

void Game::printGame() {
    #if defined(_WIN32)
        system("cls");
    #else
        system("clear");
    #endif
    const std::string RESET = "\033[0m";
    const std::string RED = "\033[31m";   // Trafiony statek
    const std::string BLUE = "\033[34m";  // Pudło (woda)
    const std::string GREEN = "\033[32m"; // Twoje statki

    // 3. Nagłówki plansz
    std::cout << "  PLANSZA GRACZA                PLANSZA PRZECIWNIKA\n";
    std::cout << "  1 2 3 4 5 6 7 8 9 10          1 2 3 4 5 6 7 8 9 10\n";
    // 4. Rysowanie plansz wiersz po wierszu
    for (int r = 0; r < 10; ++r) {

        // --- PLANSZA GRACZA ---
        char rowLetter = 'A' + r;
        std::cout << rowLetter << " ";
        for (int c = 0; c < 10; ++c) {
            const Tile& pTile = playerMap[r][c];

            if (pTile.isShot) {
                if (pTile.isShip) {
                    std::cout << RED << "X " << RESET; // Trafiony własny statek
                } else {
                    std::cout << BLUE << "O " << RESET; // Pudło przeciwnika
                }
            } else {
                if (pTile.isShip) {
                    std::cout << GREEN << "# " << RESET; // Nietrafiony własny statek
                } else {
                    std::cout << "~ "; // Zwykła woda
                }
            }
        }

        // --- ODSTĘP MIĘDZY PLANSZAMI ---
        std::cout << "        ";
        std::cout << rowLetter << " "; // Numer wiersza dla planszy przeciwnika

        // --- PLANSZA PRZECIWNIKA ---
        for (int c = 0; c < 10; ++c) {
            const Tile& eTile = enemyMap[r][c];

            if (eTile.isShot) {
                if (eTile.isShip) {
                    std::cout << RED << "X " << RESET; // Trafiony statek przeciwnika
                } else {
                    std::cout << BLUE << "O " << RESET; // Twoje pudło
                }
            } else {
                std::cout << "~ "; // Ukryte pole (niezależnie czy jest tam statek, pokazujemy wodę)
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

bool Game::enemyShot() {
    srand ( time(NULL) );
    int randomRow = rand()%10;
    int randomCol = rand()%10;
    while (playerMap[randomRow][randomCol].isShot) {
        randomRow = rand()%10;
        randomCol = rand()%10;
    }
    playerMap[randomRow][randomCol].isShot = true;
    if (playerMap[randomRow][randomCol].isShip) {
        revealSurroundingIfSunk(playerMap, randomRow, randomCol);
    }
    return playerMap[randomRow][randomCol].isShip;
}

bool Game::playerShot(int row, int col) {
    if (!enemyMap[row][col].isShot && row<10 && col<10) {
        enemyMap[row][col].isShot = true;
        if (enemyMap[row][col].isShip) {
            revealSurroundingIfSunk(enemyMap, row, col);
        }
        return enemyMap[row][col].isShip;
    }
    throw std::invalid_argument( "This place is incorrect");
}


bool canPlaceShip(const std::vector<std::vector<Tile>>& map, int r1, int c1, int r2, int c2, int expectedLength) {
    // 1. Sprawdzenie zakresu planszy
    if (r1 < 0 || r1 >= 10 || c1 < 0 || c1 >= 10 || r2 < 0 || r2 >= 10 || c2 < 0 || c2 >= 10) {
        return false;
    }

    // 2. Statek musi być w linii prostej (poziomo lub pionowo)
    if (r1 != r2 && c1 != c2) {
        return false;
    }

    // 3. Sprawdzenie długości
    int actualLength = (r1 == r2) ? std::abs(c1 - c2) + 1 : std::abs(r1 - r2) + 1;
    if (actualLength != expectedLength) {
        return false;
    }

    // 4. Sprawdzenie, czy pola nie są już zajęte
    int startR = std::min(r1, r2);
    int endR = std::max(r1, r2);
    int startC = std::min(c1, c2);
    int endC = std::max(c1, c2);
    int checkStartR = std::max(0, startR - 1);
    int checkEndR = std::min(9, endR + 1);
    int checkStartC = std::max(0, startC - 1);
    int checkEndC = std::min(9, endC + 1);
    for (int r = checkStartR; r <= checkEndR; ++r) {
        for (int c = checkStartC; c <= checkEndC; ++c) {
            if (map[r][c].isShip) {
                return false; // Wykryto stykający się bokiem lub rogiem statek
            }
        }
    }

    return true;
}

// Funkcja pomocnicza: Umieszcza statek na planszy
void placeShip(std::vector<std::vector<Tile>>& map, int r1, int c1, int r2, int c2) {
    int startR = std::min(r1, r2);
    int endR = std::max(r1, r2);
    int startC = std::min(c1, c2);
    int endC = std::max(c1, c2);

    for (int r = startR; r <= endR; ++r) {
        for (int c = startC; c <= endC; ++c) {
            map[r][c].isShip = true;
        }
    }
}
bool parseInput(const std::string& input, int& row, int& col) {
    if (input.length() < 2 || input.length() > 3) return false;

    char letter = std::toupper(input[0]);
    if (letter < 'A' || letter > 'J') return false;
    row = letter - 'A'; // 'A' -> 0, 'B' -> 1, itd.

    std::string numPart = input.substr(1);
    for (char c : numPart) {
        if (!std::isdigit(c)) return false;
    }

    col = std::stoi(numPart) - 1;
    if (col < 0 || col >= 10) return false;

    return true;
}
void sleep_millis(unsigned int ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
bool Game::playGame() {
    int shipLenghts[7] = {5,4,3,2,2,1,1};
    int i = 0;
    srand(time(NULL));
    for (int i = 0; i < 7; ++i) {
        bool placed = false;
        while (!placed) {
            int r1 = rand() % 10;
            int c1 = rand() % 10;
            int direction = rand() % 2; // 0 - poziomo, 1 - pionowo

            // Obliczamy koniec statku na podstawie wylosowanego kierunku
            int r2 = (direction == 1) ? r1 + shipLenghts[i] - 1 : r1;
            int c2 = (direction == 0) ? c1 + shipLenghts[i] - 1 : c1;

            if (canPlaceShip(enemyMap, r1, c1, r2, c2, shipLenghts[i])) {
                placeShip(enemyMap, r1, c1, r2, c2);
                placed = true;
            }
        }
    }
    while (i!=7) {
        printGame();
        string tile1,tile2;
        cout<<"Dodaj statek podając kratkę początku i końca o długości: "<<shipLenghts[i]<<"\n";
        cin>>tile1;
        cin>>tile2;
        int r1, c1, r2, c2;
        if (!parseInput(tile1, r1, c1) || !parseInput(tile2, r2, c2)) {
            std::cout << "Niepoprawny format! Uzywaj liter A-J oraz cyfr 1-10 (np. A8).\n";
            std::cout << "Wcisnij ENTER, aby sprobowac ponownie...";
            std::cin.ignore(10000, '\n');
            std::cin.get();
            continue;
        }
        if (canPlaceShip(playerMap, r1, c1, r2, c2, shipLenghts[i])) {
            placeShip(playerMap, r1, c1, r2, c2);
            i++;
        } else {
            std::cout << "Blad! Statek nie moze byc tak umieszczony (zla dlugosc, kolizja lub stykanie sie).\n";
            std::cout << "Wcisnij ENTER, aby sprobowac ponownie...";
            std::cin.ignore(10000, '\n');
            std::cin.get();
        }
    }
    printGame();
    std::cout << "Wszystkie statki rozstawione! Rozpoczynamy gre.\n";
    int enemyHitCount = 0;
    int playerHitCount = 0;
    while (true) {
        std::cout<<"Tura gracza. Wybierz kratkę w którą chcesz strzelić"<<endl;
        string tile;
        cin>>tile;
        int r, c;
        if (!parseInput(tile, r, c)) {
            std::cout<<"Zła kratka\n";
            continue;
        }
        if (enemyMap[r][c].isShot) {
            std::cout<<"Już trafiono w tą kratkę\n";
            continue;
        }
        bool ship = playerShot(r,c);
        if (ship) {
            playerHitCount++;
            printGame();
            std::cout<<"Trafiony!"<<endl;
        }
        else {
            printGame();
            std::cout<<"Pudło"<<endl;
        }
        if (playerHitCount==20) {
            break;
        }
        std::cout<<"Tura przeciwnika"<<endl;
        sleep_millis(5000);
        ship = enemyShot();

        if (ship) {
            enemyHitCount++;
            printGame();
            std::cout<<"Trafiony!"<<endl;
        }
        else {
            printGame();
            std::cout<<"Pudło"<<endl;
        }

        if (enemyHitCount==20) {
            break;
        }
    }
    printGame();
    if (playerHitCount==20) {
        std::cout<<"Wygrana!"<<endl;
        return true;
    }
    std::cout<<"Przegrana!"<<endl;
    return false;

}
