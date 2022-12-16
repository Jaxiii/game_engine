#pragma once

#ifndef TILEMAP_H
#define TILEMAP_H

#include <iostream>
#include <fstream>
#include "game_object.hpp"
#include "tile_set.hpp"

using namespace std;

class TileMap : public Component {
  public:
    TileMap(GameObject &associated, string file, TileSet *tileSet);
    void Load(string file);
    void SetTileSet(TileSet *tileSet);
    int& At(int x, int y, int z = 0);
    void Render();
    void RenderLayer(int layer, int cameraX = 0,
                    int cameraY = 0);
    int GetWidth();
    int GetHeight();
    int GetDepth();
    bool Is(string type);
    void Update(float delta_time);

private:
  vector<int> tileMatrix;
  TileSet *tileSet;
  int mapWidth;
  int mapHeight;
  int mapDepth;
};

#endif