#include "../include/internal/tile_map.hpp"
#include "../include/internal/camera.hpp"

TileMap::TileMap(GameObject &associated, string file, TileSet *tileSet) : Component::Component(associated),
                                                                               tileSet(tileSet) {
    TileMap::Load(file.c_str());
}

void TileMap::Load(string file) {
    int tile;
    char separator;
    ifstream file_object;
    file_object.open(file.c_str());
    if (file_object) {
        file_object >> mapWidth >> separator >> mapHeight >> separator >> mapDepth >> separator;
    }
    for (int i = 0; i < (mapWidth * mapHeight * mapDepth); i++) {
        file_object >> tile >> separator;
        tileMatrix.push_back(tile-1);
    }
}

void TileMap::SetTileSet(TileSet* tileSet) {
    this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z) {
    int index = x + (y * mapWidth) + (z * mapWidth * mapHeight);
    int& reference = tileMatrix[index];

    return reference;
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    for (int x = 0; x < mapWidth; x++) {
        for (int y = 0; y < mapHeight; y++) {
            tileSet->RenderTile(At(x, y, layer),
                                (float)((x + cameraX * layer * 0.25) * tileSet->GetTileWidth()),
                                (float)((y + cameraY * layer * 0.25) * tileSet->GetTileHeight()));
        }
    }
}

void TileMap::Render() {
    for (int i = 0; i < mapDepth; i++) {   
        RenderLayer(i, Camera::pos.x, Camera::pos.y);
    }
}

int TileMap::GetWidth() {
    return mapWidth;
}

int TileMap::GetHeight() {
    return mapHeight;
}

int TileMap::GetDepth() {
    return mapDepth;
}

void TileMap::Update(float delta_time) {}

bool TileMap::Is(string type) {
    return type == "TileMap" ? true : false;
}

