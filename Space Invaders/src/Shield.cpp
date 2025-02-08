#include "Shield.hpp"
Shield::Shield(Vector2 position)
{
    this -> position = position;
}
void Shield::draw()
{
    DrawRectangle(position.x, position.y, 3, 3, {WHITE});
}

Rectangle Shield::GetShieldRec()
{
    Rectangle rec;
    rec.x = position.x;
    rec.y = position.y;
    rec.width = 3;
    rec.height = 3;
    return rec;
}
