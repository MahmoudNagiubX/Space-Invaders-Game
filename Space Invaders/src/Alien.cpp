#include "Alien.hpp"
#include "Game.hpp"

Texture2D Alien::AlienTexture[3] = {}; // texture array initialization
// Load the correct alien texture based on the type, set the initial position of the alien
Alien::Alien(int Type, Vector2 Position) // Constructor for Alien
{
    this -> Type = Type; // Type int representing the type of alien
    this -> position = Position; // Position Vector2 representing the initial position of the alien
    if(AlienTexture[Type-1].id == 0) // OpenGL texture id
    {
        if (Type == 1)
        {
            AlienTexture[0] = LoadTexture("Graphics/AlienOne1.png");
        }
        else if (Type == 2)
        {
            AlienTexture[1] = LoadTexture("Graphics/AlienTwo2.png");    
        }
        else if (Type == 3)
        {
            AlienTexture[2] = LoadTexture("Graphics/AlienThree2.png");    
        }
        else
        {
            AlienTexture[0] = LoadTexture("Graphics/AlienOne1.png");
        }
    }
}
// Draws the alien on the screen at its current position using the loaded texture
void Alien::draw()
{
    DrawTextureV(AlienTexture[Type-1], position, WHITE);
}
void Alien::UnloadAliens()
{
    for (int i = 0; i < 3; i++) // Fix: Loop only over valid indices
    {
        if (AlienTexture[i].id != 0) // Ensure texture was loaded before unloading
        {
            UnloadTexture(AlienTexture[i]);
            AlienTexture[i].id = 0; // Reset ID to avoid double unloading
        }
    }
}
int Alien::GetType()
{
    return Type;
}
void Alien::Update(int Direction)
{
    position.x += Direction;
}
Rectangle Alien::GetAlienRec()
{
    return {position.x, position.y, float(AlienTexture[Type-1].width), float(AlienTexture[Type-1].height)};
}
