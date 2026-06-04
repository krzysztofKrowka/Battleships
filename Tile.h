//
// Created by Krzysztof on 4.06.2026.
//

#ifndef BATTLESHIPS_TILE_H
#define BATTLESHIPS_TILE_H


class Tile {
    public:
    bool isShip;
    bool isShot;
    Tile(bool isShip, bool isShot);
    Tile();
};


#endif //BATTLESHIPS_TILE_H