#include <iostream>

#include "Game.h"
void printHelp() {
    std::cout << "=================== GRA W STATKI ===================\n";
    std::cout << "Autor: Krzysztof\n\n";
    std::cout << "OPIS GRY:\n";
    std::cout << "Klasyczna gra w statki rozgrywana przeciwko komputerowi.\n";
    std::cout << "Plansza ma rozmiar 10x10 (wiersze A-J, kolumny 1-10).\n\n";
    std::cout << "JAK GRAC:\n";
    std::cout << "1. Rozstaw swoj flota podajac wspolrzedne poczatku i konca (np. A1 A5).\n";
    std::cout << "   Pamietaj! Statki nie moga sie stykac bokami ani rogami.\n";
    std::cout << "2. W swojej turze strzelaj podajac jedna kratke (np. G7).\n";
    std::cout << "3. Po zatopieniu statku, pola wokol niego zostana automatycznie odkryte.\n\n";
    std::cout << "PARAMETRY STARTOWE:\n";
    std::cout << "  -h, --help    Wyswietla te pomoc\n";
    std::cout << "====================================================\n";
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "-h" || arg == "--help") {
            printHelp();
            return 0;
        }
    }


    Game game;
    game.playGame();

    return 0;
}