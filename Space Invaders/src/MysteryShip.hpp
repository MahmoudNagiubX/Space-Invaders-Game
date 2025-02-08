#pragma once
#include <raylib.h>
#include "SpaceShip.hpp"
using namespace std;
class MysteryShip {
    public:
    MysteryShip();
    ~MysteryShip();
    void Draw();
    void Update();
    void Spawn();
    Rectangle GetMysteryShipRec();
    bool Alive;
    
    private:
    Texture2D MysteryShipTexture;
    Vector2 Position;
    int Speed;
};