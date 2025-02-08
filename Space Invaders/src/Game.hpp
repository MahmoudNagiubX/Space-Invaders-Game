#pragma once
#include <raylib.h>
#include "SpaceShip.hpp"
#include "Obastacle.hpp"
#include "Alien.hpp"
#include "MysteryShip.hpp"
using namespace std;
class Game
{
    public:
        Game();
        ~Game();
        void Draw();
        void Update();
        void Input();
        bool Run;
        bool Won; 
        int Lives;
        int score;
        int HighScore;
        Music Music,EntryMusic;
    private:
        void DeleteInactiveLasers();
        vector<Obstacle> CreateObstacles();
        SpaceShip Ship;
        vector <Alien> CreateAliens();
        void MoveAliens();
        void AlienShootLasers();
        vector<Obstacle> Obstacles;
        vector<Alien> Aliens;
        int AliensDirection;
        void MoveDownAliens(int Distance);
        vector <Laser> AlienLasers;
        constexpr static float AlienLaserShootTimer = 0.35f;
        float TimeLastLaserShootByAlien;
        MysteryShip MysteryShip;
        float TimeLastMysteryShipSpawn;
        float MysteryShipSpawnTimer;
        void CheckForCollision();
        void GameOver();
        void GameWin();
        void Reset();
        void IntialGame();
        void CheckForHighscore();
        void SaveHighscoreToFile(int highscore);
        int LoadHighscoreFromFile();
        Sound ExplosionSound;
};

