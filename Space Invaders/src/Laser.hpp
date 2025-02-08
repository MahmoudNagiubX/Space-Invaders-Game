#pragma once
#include <raylib.h>
class Laser
{
    public:
        Laser(Vector2 Position, int Speed);
        void Draw();
        void Update();
        Rectangle GetLaserRec();
        bool Active;
    private:
        Vector2 Position;
        int Speed;
};
