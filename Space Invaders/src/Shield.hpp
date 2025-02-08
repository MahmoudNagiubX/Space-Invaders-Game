#pragma once
#include <raylib.h>

class Shield {
    public:
    Shield(Vector2 Position);
    void draw();
    Rectangle GetShieldRec();
    
    private:
    Vector2 position;
};