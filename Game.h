//
// Created by Krzysztof on 4.06.2026.
//
#include <vector>
using namespace std;
#include "Tile.h"
#ifndef BATTLESHIPS_GAME_H
#define BATTLESHIPS_GAME_H


class Game {
    public:
    vector<vector<Tile>> playerMap = vector<vector<Tile>>(10, vector<Tile>(10));
    vector<vector<Tile>> enemyMap = vector<vector<Tile>>(10,vector<Tile>(10));

    void printGame();

    bool playerShot(int row,int col);
    bool enemyShot();

    bool playGame();
};


#endif //BATTLESHIPS_GAME_H