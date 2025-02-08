#include "SpaceShip.hpp"

const int MovmentSpeed = 3;
const int LaserSpeed = -4;
const int LaserOffset = -2;
const int BoundaryX = 20;
const int BoundaryYTop = 12;
const int BoundaryYBottom = 74;
const float FireCooldown = 0.3f;

/*Constructor for SpaceShip
Loads the ship texture from the Graphics file and sets the initial position 
the center of the screen */
SpaceShip::SpaceShip()
{
    Ship = LoadTexture("Graphics/Ship1.png");
    Position.x = (GetScreenWidth() - Ship.width)/2;
    Position.y = GetScreenHeight() - Ship.height - 100;
    LastFireTime = 0.0;
    LaserSound = LoadSound("Sounds/laser.ogg");
}
SpaceShip::~SpaceShip()
{
    UnloadTexture(Ship);  //Ship Unload When Closing The Game
    UnloadSound(LaserSound);
}
// Draws the spaceship on the screen at its current position using the loaded texture
void SpaceShip::Draw()
{
    DrawTextureV(Ship, Position, WHITE);
}
void SpaceShip::MoveRight()
{
    Position.x += MovmentSpeed;
    if (Position.x > GetScreenWidth() - Ship.width - BoundaryX)
    {
        Position.x = GetScreenWidth() - Ship.width - BoundaryX;
    }
}
void SpaceShip::MoveLeft()
{
    Position.x -= MovmentSpeed;
    if (Position.x < BoundaryX)
    {
        Position.x = BoundaryX;
    }
}
void SpaceShip::MoveUp()
{
    Position.y -= MovmentSpeed;
    if (Position.y < BoundaryYTop)
    {
        Position.y = BoundaryYTop;
    }
}
void SpaceShip::MoveDown()
{
    Position.y += MovmentSpeed;
    if (Position.y > GetScreenHeight() - Ship.height - BoundaryYBottom)
    {
        Position.y = GetScreenHeight() - Ship.height - BoundaryYBottom;
    }
}
// Creates a new laser beam at the ship's current position at the center of ship with the specified speed
void SpaceShip::FireLaser()
{
    if (GetTime() - LastFireTime >= FireCooldown)
    {
        LaserBeam.push_back(Laser({Position.x  + Ship.width/2 + LaserOffset, Position.y}, LaserSpeed));
        LastFireTime = GetTime();
        PlaySound(LaserSound);
    }
    
}

Rectangle SpaceShip::GetShipRec()
{
    return {Position.x, Position.y, float(Ship.width), float(Ship.height)};
}

void SpaceShip::Reset()
{
    Position.x = (GetScreenWidth() - Ship.width)/2.0f;
    Position.y = GetScreenHeight() - Ship.height - 100;
    LaserBeam.clear();
    LastFireTime = 0.0; // Reset fire timer
}
