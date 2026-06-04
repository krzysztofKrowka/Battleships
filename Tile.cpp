//
// Created by Krzysztof on 4.06.2026.
//

#include "Tile.h"

Tile::Tile(bool isShip, bool isShot)  {
    this->isShip = isShip;
    this->isShot = isShot;
}
Tile::Tile() {
    this->isShip = false;
    this->isShot = false;
}
