#include <raylib.h>
#include <string>
#include "Game.hpp"
using namespace std;
string FormatWithLeadingZeros(int number, int width)
{
    string NumberText = to_string(number);
    int leadingZeros = width - NumberText.length();
    return NumberText = string(leadingZeros, '0') + NumberText;
}
int main() 
{
    int OffSet = 50;
    const int Window_Width = 1550;
    const int Window_Height = 800;
    InitWindow(Window_Width + OffSet,Window_Height + (OffSet * 2),"The Space Invaders");
    InitAudioDevice();

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    Texture2D ShipLives = LoadTexture("Graphics/heart.png");
    
    SetTargetFPS(144);
    Texture2D SpaceBackground = LoadTexture("Graphics/spacebackground.png");
    double MessageDisplayTime = 6.0;
    double TimeElapsed = 0.0;
    Game Game;
    while (WindowShouldClose() == false)
    {
        // UpdateMusicStream(Game.EntryMusic);  
        BeginDrawing();
        TimeElapsed += GetFrameTime(); // Get time in seconds for last frame drawn (delta time)
        DrawTexture(SpaceBackground,0,0,WHITE);
        if (TimeElapsed < MessageDisplayTime){
            UpdateMusicStream(Game.EntryMusic);  
            DrawTextEx(font," Welcome to Space Invaders ", {400, 390}, 60, 4, WHITE);
        }
        if (TimeElapsed >= MessageDisplayTime){
            UpdateMusicStream(Game.Music);
            Game.Input();
            Game.Update();
            DrawRectangleRoundedLines({10,10,Window_Width + 30,Window_Height + 80},0.18f,20,BLUE);
            DrawLineEx({25,Window_Height + 30},{Window_Width + 25,Window_Height + 30},3,BLUE);
            if(Game.Run)
            {
                DrawTextEx(font, "LEVEL 01", {Window_Width - 200, Window_Height + 45}, 32, 2.5, BLUE);                
            }
            else if (Game.Won)
            {
                DrawTextEx(font, "YOU WIN", {Window_Width - 200, Window_Height + 45}, 30, 3.5, BLUE);
                DrawTextEx(font, "Press Enter to Play Again", {Window_Width - 1100, Window_Height - 380}, 50, 3.5, BLUE);
            }
            else
            {
                DrawTextEx(font, "GAME OVER", {Window_Width - 200, Window_Height + 45}, 30, 3.5, BLUE);                
            }
            float x = 75.0;
            for (int i = 0; i < Game.Lives; i++)
            {
                DrawTextureV(ShipLives, {x, 840}, WHITE);
                x += 50;
            }
                DrawTextEx(font, "SCORE" , {60, 30}, 30, 3.5, BLUE);
                string ScoreText = FormatWithLeadingZeros(Game.score, 5);
                DrawTextEx(font, ScoreText.c_str(), {63, 62}, 32, 5, BLUE);
                DrawTextEx(font, "HIGHSCORE" , {Window_Width - 230, 30}, 30, 3.5, BLUE);
                string HighScoreText = FormatWithLeadingZeros(Game.HighScore, 5);
                DrawTextEx(font, HighScoreText.c_str(), {Window_Width - 190, 62}, 32, 5, BLUE);
                Game.Draw();
        }
            EndDrawing();
    }
    UnloadTexture(SpaceBackground);
    CloseWindow();
    CloseAudioDevice();
}