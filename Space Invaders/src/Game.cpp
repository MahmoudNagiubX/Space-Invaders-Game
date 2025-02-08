#include "Game.hpp"
#include <fstream>
using namespace std;
 Game::Game() // Default constructor for Game
{   
    Music = LoadMusicStream("Sounds/Batman.ogg");
    EntryMusic = LoadMusicStream("Sounds/Star Wars.ogg");
    ExplosionSound = LoadSound("Sounds/explosion.ogg");
    PlayMusicStream(Music);
    PlayMusicStream(EntryMusic);
    IntialGame();
}
Game::~Game() // Destructor for Game
{
    // Unloads all resources loaded by the game also clears the vector of laser objects.
    Alien::UnloadAliens();
    UnloadMusicStream(Music);
    UnloadMusicStream(EntryMusic);
    UnloadSound(ExplosionSound);
}
void Game::Update() // Updates all the laser objects in the game. This function is called every frame from main
{
    if(Run)
    {
        double CurrentTime = GetTime();
        if (Aliens.empty()) 
        { // All aliens destroyed
            GameWin();
            return; // Exit early to stop further updates
        }
        if (CurrentTime - TimeLastMysteryShipSpawn > MysteryShipSpawnTimer)
        {
            MysteryShip.Spawn();
            TimeLastMysteryShipSpawn = GetTime();
            MysteryShipSpawnTimer = GetRandomValue(10, 20);
        }
        for (auto& laser: Ship.LaserBeam)
        {
            laser.Update();  
        }
            DeleteInactiveLasers();
            MoveAliens();
            AlienShootLasers();
        for(auto& Laser: AlienLasers)
        {
            Laser.Update();
        }
            MysteryShip.Update();
            CheckForCollision();
    }
    else
    {
        if(IsKeyPressed(KEY_ENTER))
        {
            Reset();
            IntialGame();
        }
    }
}
void Game::Draw() // Draws all the elements in the game. This function is called every frame from main. It iterates over all the laser objects in the Ship's vector and calls their Draw() functions.
{
    Ship.Draw();
    for (auto& laser: Ship.LaserBeam)
    {
        laser.Draw();
    }
    for (auto& obstacle: Obstacles)
    {
        obstacle.Draw();
    }
    for (auto& alien: Aliens)
    {
        alien.draw();
    }
    for(auto& laser: AlienLasers)
    {
        laser.Draw();
    }
        MysteryShip.Draw();
}

void Game::Input()
{
    if(Run)
    {
        if (IsKeyDown(KEY_RIGHT))
        {
            Ship.MoveRight();
        }
        if (IsKeyDown(KEY_LEFT))
        {
            Ship.MoveLeft();
        }
        if (IsKeyDown(KEY_UP))
        {
            Ship.MoveUp();
        }
        if (IsKeyDown(KEY_DOWN))
        {
            Ship.MoveDown();
        }
        if (IsKeyDown(KEY_SPACE))
        {
            Ship.FireLaser();
        }
    }
}
void Game::DeleteInactiveLasers()
{
    for (auto it = Ship.LaserBeam.begin(); it != Ship.LaserBeam.end();)
    {
        if (!it->Active)
        {
            it = Ship.LaserBeam.erase(it);
        }
        else
        {
            ++it;
        }
    }
    for (auto it = AlienLasers.begin(); it != AlienLasers.end();)
    {
        if (!it->Active)
        {
            it = AlienLasers.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
// Creates and returns a vector of 4 Obstacle objects positioned horizontally in the bottom part of the screen.
// The Obstacle objects are positioned so that the gap between them and the left and right edges of the screen
// and the gap between them is equal. The obstacles are positioned 100 pixels above the bottom of the screen.
// The width of each obstacle is calculated by multiplying the width of the obstacle grid by 3.
vector<Obstacle> Game::CreateObstacles()
{
    int ObstacleWidth = Obstacle::grid[0].size()*3;
    float Gap = (GetScreenWidth() - (4 * ObstacleWidth)) / 5; // Calculate the gap between obstacles
    for (int i = 0; i < 4; i++)
    {
        float OffSetX = (i + 1) * Gap + 1 * ObstacleWidth;
        Obstacles.push_back(Obstacle({OffSetX, float(GetScreenHeight() - 290)}));
    }
        return Obstacles;
}
vector<Alien> Game::CreateAliens() // Creates and returns a vector of 55 Alien objects arranged in a 5x11 grid
{
    // The aliens are positioned at the top of the screen and are evenly spaced
    vector <Alien> Aliens;
    for (int Row = 0; Row < 5; Row++)
    {
        for(int Column = 0; Column < 15; Column++)
        {   
            int AlienType;
            if(Row ==0)
            {
                AlienType = 3;
            }
            else if(Row == 1 || Row == 2)
            {
                AlienType = 2;
            }
            else
            {
                AlienType = 1;
            }
            float X = 130 + Column * 80; // Size Of Alien
            float Y = 130 + Row * 80;
            Aliens.push_back(Alien(AlienType, {X, Y})); // The size of each alien is 55x55 pixels.
        }
    }
    return Aliens;  
}
    void Game::MoveAliens()
    {
        for (auto& alien: Aliens)
        {
            if(alien.position.x + alien.AlienTexture[alien.Type-1].width > GetScreenWidth() - 20)
            {
                AliensDirection = -1;
                MoveDownAliens(0);
            }
            if (alien.position.x < 20)
            {
                AliensDirection = 1;
                MoveDownAliens(0);
            }
                alien.Update(AliensDirection);
        }
    }
    void Game::AlienShootLasers()
    {
        double CurrentTime = GetTime();
        if(CurrentTime - TimeLastLaserShootByAlien >= AlienLaserShootTimer && !Aliens.empty())
        {
        int RandomIndex = GetRandomValue(0, Aliens.size() - 1);
        Alien& alien = Aliens[RandomIndex];
        AlienLasers.push_back(Laser({alien.position.x + alien.AlienTexture[alien.Type-1].width/2, 
        alien.position.y + alien.AlienTexture[alien.Type-1].height}, 3));
        TimeLastLaserShootByAlien = GetTime();
        }
    }
    void Game::MoveDownAliens(int Distance)
    {
        for(auto& alien: Aliens)
        {
            alien.position.y += Distance;
        }
    }
    void Game::CheckForCollision()
    {
        // Space Ship Laser
        for(auto& laser: Ship.LaserBeam)
        {
            auto it = Aliens.begin();
            while(it != Aliens.end())
            {
                if(CheckCollisionRecs(laser.GetLaserRec(), it->GetAlienRec()))
                {
                    PlaySound(ExplosionSound);
                    if(it -> Type == 1)
                    {
                        score += 100;
                    }
                    else if (it -> Type == 2)
                    {
                        score += 200;
                    }
                    else if(it -> Type == 3)
                    {
                        score += 300;
                    }
                    CheckForHighscore();
                    it = Aliens.erase(it);
                    laser.Active = false;
                }
                else
                {
                    ++it;
                }
            }
                for(auto& obstacle: Obstacles)
                {
                    auto it = obstacle.shieldsVector.begin();
                    while(it != obstacle.shieldsVector.end())
                    {
                        if(CheckCollisionRecs(laser.GetLaserRec(), it->GetShieldRec()))
                        {
                            it = obstacle.shieldsVector.erase(it);
                            laser.Active = false;
                        }
                        else
                        {
                            ++it;
                        }
                    }
                }
                    if(CheckCollisionRecs(laser.GetLaserRec(), MysteryShip.GetMysteryShipRec()))
                    {
                        MysteryShip.Alive = false;
                        laser.Active = false;
                        score += 500;
                        CheckForHighscore();
                        PlaySound(ExplosionSound);
                    }
        }
        // Alien Laser
        for(auto& laser: AlienLasers)
        {
           if(CheckCollisionRecs(laser.GetLaserRec(), Ship.GetShipRec()))
           {
            laser.Active = false;
            Lives--;
            if(Lives == 0)
                {
                     GameOver();
                }
           }
            for(auto& obstacle: Obstacles)
                {
                    auto it = obstacle.shieldsVector.begin();
                    while(it != obstacle.shieldsVector.end())
                    {
                        if(CheckCollisionRecs(laser.GetLaserRec(), it->GetShieldRec()))
                        {
                            it = obstacle.shieldsVector.erase(it);
                            laser.Active = false;
                        }
                        else
                        {
                            ++it;
                        }
                    }
                }
        }
    // Alien collision with Obstacles
    for(auto& Alien: Aliens)
    {
        // for(auto& obstacle: Obstacles)
        // {
        //     auto it = obstacle.shieldsVector.begin();
        //     while(it != obstacle.shieldsVector.end())
        //     {
        //         if(CheckCollisionRecs(Alien.GetAlienRec(), it->GetShieldRec()))
        //         {
        //             it = obstacle.shieldsVector.erase(it);
        //         }
        //         else
        //         {
        //             it++;
        //         }
        //     }
        // }
            if(CheckCollisionRecs(Alien.GetAlienRec(), Ship.GetShipRec()))
            {
                GameOver();
            }
        }
    }
void Game::GameOver()
{
    Run = false;
}
void Game::GameWin()
{
    Run = false;
    Won = true;
}
void Game::IntialGame()
{
    Obstacles = CreateObstacles();
    Aliens = CreateAliens();
    AliensDirection = 1;
    TimeLastLaserShootByAlien = 0.0f;
    TimeLastMysteryShipSpawn = 0.0f;
    MysteryShipSpawnTimer = GetRandomValue(10.0, 20.0);
    Lives = 3;
    score = 0;
    HighScore = LoadHighscoreFromFile();
    Run = true;
}
void Game::CheckForHighscore()
{
    if(score > HighScore)
    {
        HighScore = score;
        SaveHighscoreToFile(HighScore);
    }
}
void Game::SaveHighscoreToFile(int highscore)
{
    ofstream file("highscore.txt");
    if(file.is_open())
    {
        file << highscore;
        file.close();
    }
    else
    {
        cerr << "Failed to Save Highscore to File" << endl;
    }
}
int Game::LoadHighscoreFromFile()
{
    int LoadedHighscore = 0;
    ifstream file("highscore.txt");
    if(file.is_open())
    {
        file >> LoadedHighscore;
        file.close();
    }
    else
    {
        cerr << "Failed to Load Highscore from File" << endl;
    }
    return LoadedHighscore;
}
void Game::Reset()
{
    Ship.Reset();
    Aliens.clear();
    AlienLasers.clear();
    Obstacles.clear();
    Won = false;
}

