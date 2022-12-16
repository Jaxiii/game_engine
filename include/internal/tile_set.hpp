#pragma once

#ifndef TILESET_H
#define TILESET_H

#include <iostream>
#include "sprite.hpp"
#include "game_object.hpp"

class TileSet {
  public:
    TileSet(GameObject& associated, int tileWidth, int tileHeight, std::string file);
    void RenderTile(unsigned index, float x, float y);
    int GetTileWidth();
    int GetTileHeight();

  private:
    Sprite tileSet;
    int rows;
    int columns;
    int tileWidth;
    int tileHeight;
    int tilesNumber;
};

#endif