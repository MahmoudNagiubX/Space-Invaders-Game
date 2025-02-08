#include "MysteryShip.hpp"
#include "raylib.h"

MysteryShip::MysteryShip()
{
    MysteryShipTexture = LoadTexture("Graphics/mystery.png");
    Alive = false;
}
MysteryShip::~MysteryShip()
{
    UnloadTexture(MysteryShipTexture);
}
void MysteryShip::Spawn()
{
    Position.y = 90;
    int Side = GetRandomValue(0, 1);
    if (Side == 0)
    {
        Position.x = 20;
        Speed = 2;
    }
    else
    {
        Position.x = GetScreenWidth() - MysteryShipTexture.width;
        Speed = -2;
    }
        Alive = true;
}
Rectangle MysteryShip::GetMysteryShipRec()
{
    if(Alive)
    {
        return {Position.x, Position.y, float(MysteryShipTexture.width), float(MysteryShipTexture.height)};
    }
    else
    {
        return {Position.x, Position.y,0, 0};
    }
}
void MysteryShip::Update()
{
    Position.x += Speed;
    if (Position.x < 0 || Position.x > GetScreenWidth() - MysteryShipTexture.width)
    {
        Alive = false;
    }
}
 void MysteryShip::Draw() 
 {
    if(Alive)
    {
        DrawTextureV(MysteryShipTexture, Position, WHITE);
    }
 }