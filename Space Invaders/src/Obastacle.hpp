#pragma once
#include <raylib.h>
#include <vector>
#include "Shield.hpp"
using namespace std;

class Obstacle
{
public: 
    Obstacle(Vector2 Position);
    void Draw();
    vector<Shield> shieldsVector;    
    static vector<vector<int>> grid;
    Vector2 position;
private:
};

