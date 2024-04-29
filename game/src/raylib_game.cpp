#include "raylib.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

const int screenWidth = 800;
const int screenHeight = 500;

const int halfScreenWidth = 400;
const int halfScreenHeight = 250;

const int radiusOfMainCircle = 200;



float tanX;
float posX;


findLowerY(float x)
{
    return sqrt(pow(radiusOfMainCircle,2)-pow(x-400,2))+halfScreenHeight;
}

findUpperY(float x)
{
    return -sqrt(pow(radiusOfMainCircle,2)-pow(x-400,2))+halfScreenHeight;
}


void updateGameScreen()
{

}

void drawGameScreen()
{
ClearBackground(RAYWHITE);

DrawCircleLines(halfScreenWidth,halfScreenHeight,radiusOfMainCircle,BLACK);
// equation of circle == (x-400)² + (y+250)² = 200²


tanX = (halfScreenHeight-GetMousePosition().y)/(GetMousePosition().x-halfScreenWidth);
posX = (sqrt(pow(radiusOfMainCircle,2)/(pow(tanX,2)+1)))+halfScreenWidth;
GetMousePosition().x > halfScreenWidth ? : posX = -(sqrt(pow(radiusOfMainCircle,2)/(pow(tanX,2)+1)))+halfScreenWidth;

DrawText(TextFormat("%f",tanX),250,250,30,BLACK);

Vector2 circle1 = {posX,GetMouseY()>halfScreenHeight ? findLowerY(posX):findUpperY(posX)};

DrawCircleV(circle1,20,BLACK);
DrawLine(halfScreenWidth,halfScreenHeight,GetMousePosition().x,GetMousePosition().y,BLUE);

}


int main()
{
//Definitions
InitWindow(screenWidth,screenHeight,"Math Game");
SetTargetFPS(60);

//Setting 


while (!WindowShouldClose())
{

    updateGameScreen();
    // 1. Event Handling 

    // 2. Updating Posisitons 

    // 3. Drawing 
BeginDrawing();

drawGameScreen();


EndDrawing();
}


CloseWindow();
    return 0;
}

