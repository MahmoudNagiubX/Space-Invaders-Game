#pragma once
#include <raylib.h>
class Alien 
{
    public:
    Alien(int Type, Vector2 Position);
    static Texture2D AlienTexture[3];
    Vector2 position;
    Vector2 speed;
    int Type;
    static void UnloadAliens();
    int GetType();
    void draw();
    void Update(int Direction);
    Rectangle GetAlienRec();
    private:
};
