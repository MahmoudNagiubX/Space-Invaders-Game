#include "Laser.hpp"  
Laser::Laser(Vector2 Position, int Speed)  // Constructor for a Laser object
{
    this -> Position = Position;  // Position Vector2 representing the position of the laser
    this -> Speed = Speed;  // Speed int representing the speed of the laser
    Active = true;
}
void Laser::Draw()
{
    if (Active) // Only draws if the laser is active
        DrawRectangle(Position.x,Position.y,5,14,GREEN);  // Draws the laser on the screen as an orange rectangle at its current position
}
void Laser::Update()
{
    Position.y += Speed; // Updates the position of the laser based on its speed
    
        if(Active) 
        {   // Checks if the laser is out of the screen
            if (Position.y > GetScreenHeight() - 100 || Position.y < 25)
            {
                Active = false;            
            }
        }
}

Rectangle Laser::GetLaserRec()
{
    Rectangle rec;
    rec.x = Position.x;
    rec.y = Position.y;
    rec.width = 5;
    rec.height = 14;
    return rec;
}
