#pragma once
#include <raylib.h>
#include "Laser.hpp"
#include <iostream>
#include <vector>
using namespace std;
class SpaceShip
{
    public:
        SpaceShip();
        ~SpaceShip();
        void Draw();
        void MoveRight();
        void MoveUp();
        void MoveDown();
        void MoveLeft();
        void FireLaser();
        Rectangle GetShipRec();
        vector<Laser> LaserBeam;
        void Reset();
    private:
        Texture2D Ship;
        Vector2 Position;
        double LastFireTime;
        Sound LaserSound;
};
