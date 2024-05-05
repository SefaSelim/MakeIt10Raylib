#include "raylib.h"
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

const int screenWidth = 800;
const int screenHeight = 500;

const int halfScreenWidth = 400;
const int halfScreenHeight = 250;

const int radiusOfMainCircle = 200;

int maxCircles = 15;

int numberOfCircle = 6;
int numberOfCircle2 = numberOfCircle;

float degreeBetweenCircles = 360 / numberOfCircle;

bool inGame = false;
bool inMenu = true;

float tanX;
float posX;
float sinX;
int x;

bool LostEnabled = false;

Color colorOfStartButton = LIGHTGRAY;

struct Circle
{
    Vector2 Position;
    Vector2 Velocity;
    bool isActive;
};

std::vector<Circle> Circles;
std::vector<int> circArr;

float findLowerY(float x)
{
    return sqrt(pow(radiusOfMainCircle, 2) - pow(x - 400, 2)) + halfScreenHeight;
}

float findUpperY(float x)
{
    return -sqrt(pow(radiusOfMainCircle, 2) - pow(x - 400, 2)) + halfScreenHeight;
}

Vector2 CirclePosition = {400, 250};
Vector2 CircleVelocity;
bool isCircleMoving = false;
float mouseX, mouseY, mouseAngle;
bool isAdding = false;
float queue;
int CircleQueue;

void drawCircles()
{

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        isCircleMoving = true;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CirclePosition.x == halfScreenWidth && CirclePosition.y == halfScreenHeight)
    {

        // queue finding placeholder
        queue = atan(tanX) * 180 / PI;

        if (queue >= 0 && GetMouseX() >= 400)
        {
            queue = 90 - queue;
        }
        else if (queue >= 0)
        {
            queue = 270 - queue;
        }
        else if (GetMouseX() >= 400 && queue < 0)
        {
            queue = 90 - queue;
        }
        else
        {
            queue = 270 - queue;
        }

        CircleQueue = queue / degreeBetweenCircles;

        mouseX = GetMousePosition().x - 400;
        mouseY = GetMousePosition().y - 250;

        mouseAngle = mouseY / mouseX;

        if (abs(mouseX) > abs(mouseY))
        {
            mouseX > 0 ? mouseX = 5 : mouseX = -5;
            mouseY = mouseX * mouseAngle;
        }
        else
        {
            mouseY > 0 ? mouseY = 5 : mouseY = -5;
            mouseX = mouseY / mouseAngle;
        }
    }

    if (isCircleMoving == true)
    {
        CirclePosition.x += mouseX;
        CirclePosition.y += mouseY;
    }
    DrawCircleV(CirclePosition, 20, BLUE);
    DrawText(TextFormat("%d", circArr[numberOfCircle2]), CirclePosition.x - 5, CirclePosition.y - 8, 20, WHITE);
    if (sqrt(pow(CirclePosition.x - halfScreenWidth, 2) + pow(CirclePosition.y - halfScreenHeight, 2)) > 200)
    {
        CirclePosition = {halfScreenWidth, halfScreenHeight};
        isCircleMoving = false;
        isAdding = true;
    }
}

void drawGameScreen()
{
    ClearBackground(RAYWHITE);

    // DrawCircleLines(halfScreenWidth,halfScreenHeight,radiusOfMainCircle,BLACK);
    // equation of circle == (x-400)² + (y+250)² = 200²

    tanX = (halfScreenHeight - GetMousePosition().y) / (GetMousePosition().x - halfScreenWidth);
    posX = (sqrt(pow(radiusOfMainCircle, 2) / (pow(tanX, 2) + 1))) + halfScreenWidth;

    GetMousePosition().x > halfScreenWidth ?: posX = -(sqrt(pow(radiusOfMainCircle, 2) / (pow(tanX, 2) + 1))) + halfScreenWidth;
}

int main()
{
    srand(time(NULL)*10);

    Rectangle startButton = {halfScreenWidth - 175, halfScreenHeight - 75, 350, 150};

    for (int i = 1; i <= maxCircles; i++)
        circArr.push_back(rand() % 9 + 1);

    // Definitions
    InitWindow(screenWidth, screenHeight, "Make It 10");
    Texture2D background = LoadTexture("resources/background.png");
    Texture2D menubackground = LoadTexture("resources/Menubackground.png");
    SetTargetFPS(60);

    // Setting

    int x = halfScreenWidth;
    Vector2 c1;

    int score = 0,highscore=0;

    while (!WindowShouldClose())
    {
        if (score>highscore)
        {
            highscore = score;
        }
        


        degreeBetweenCircles = (float)360 / numberOfCircle;


        BeginDrawing();



        if (inGame)
        {
            DrawTexture(background, 0, 0, WHITE);
            DrawText(TextFormat("Score : %d",score),0,0,40,WHITE);

        Vector2 circle1 = {posX, GetMouseY() > halfScreenHeight ? findLowerY(posX) : findUpperY(posX)};

        DrawCircleV(circle1, 20, LIGHTGRAY);

            int j = 0;
            j = 0;
            for (float i = 0; i < 359; i += degreeBetweenCircles, j++)
            {
                x = radiusOfMainCircle * sin(i * PI / 180) + halfScreenWidth;
                c1 = {x, (i <= 90 || i >= 270) ? findUpperY(x) : findLowerY(x)};

                if (numberOfCircle == maxCircles - 1)
                {
                    c1.x += rand() % 5;
                    c1.y += rand() % 5;
                }

                if (circArr[j] == 11)
                {
                    DrawCircleV(c1, 20, RED);
                }
                else if (circArr[j] == 10)
                {
                    DrawCircleV(c1, 20, ORANGE);
                }
                else
                {
                    DrawCircleV(c1, 20, BLUE);
                }

                DrawText(TextFormat("%d", circArr[j]), c1.x - 5, c1.y - 8, 20, WHITE);
            }

            drawGameScreen();
            drawCircles();
        }

        else if (inMenu == true)
        {
            ClearBackground(RAYWHITE);
            DrawTexture(menubackground, 0, 0, WHITE);
            DrawRectangle(halfScreenWidth - 175, halfScreenHeight - 75, 350, 150, colorOfStartButton);
            DrawText("START", halfScreenWidth - 70, halfScreenHeight - 20, 40, BLACK);

            if (CheckCollisionPointRec(GetMousePosition(), startButton))
            {
                colorOfStartButton = RED;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    inGame = true;
                    inMenu = false;
                    LostEnabled = false;
                }
            }
            else
            {
                colorOfStartButton = LIGHTGRAY;
                DrawText("START", halfScreenWidth - 70, halfScreenHeight - 20, 40, WHITE);
            }

            if (LostEnabled)
            {
                DrawText("LOST", 200, 50, 150, RED);
                DrawText(TextFormat("HIGHSCORE : %d",highscore), 150, 350, 65, RED);
                score = 0;
            }
        }
        if (inGame)
        {
            if (isAdding)
            {

                circArr.emplace(circArr.begin() + CircleQueue + 1, circArr[numberOfCircle2]);
                numberOfCircle++;
                numberOfCircle2 += 2;
                isAdding = false;
                
            }
        }
        EndDrawing();

        if (IsKeyPressed(KEY_Y))
        {
            inGame = false;
            inMenu = true;
        }

        // control mechanism
        for (int i = 0, j = 1, k = 2; i < numberOfCircle; i++, j++, k++)
        {
            k = k % numberOfCircle;
            j = j % numberOfCircle;

            if (circArr[i] + circArr[j] + circArr[k] == 10)
            {
                circArr.erase(circArr.begin() + k);
                circArr.erase(circArr.begin() + j);
                circArr.erase(circArr.begin() + i);
                numberOfCircle -= 2;
                numberOfCircle2 -= 4;
                circArr.emplace(circArr.begin() + i, 10);
                circArr.push_back(rand() % 9 + 1);
                circArr.push_back(rand() % 9 + 1);
                score += 10;
            }
            if (circArr[i] == 10 && circArr[j] == 10 && circArr[k] == 10)
            {
                circArr.erase(circArr.begin() + k);
                circArr.erase(circArr.begin() + j);
                circArr.erase(circArr.begin() + i);
                numberOfCircle -= 2;
                numberOfCircle2 -= 4;
                circArr.emplace(circArr.begin() + i, 11);
                circArr.push_back(rand() % 9 + 1);
                circArr.push_back(rand() % 9 + 1);
                score += 25;
            }
            if (circArr[i] + circArr[j] == 10)
            {
                circArr.erase(circArr.begin() + j);
                circArr.erase(circArr.begin() + i);
                numberOfCircle--;
                numberOfCircle2 -= 2;
                circArr.emplace(circArr.begin() + i, 10);
                circArr.push_back(rand() % 9 + 1);
                score += 10;
            }


        }

        if (numberOfCircle >= maxCircles)
        {
            inMenu = true;
            inGame = false;
            numberOfCircle = 6;
            numberOfCircle2 = numberOfCircle;
            for (int i = 1; i <= maxCircles; i++)
                circArr.erase(circArr.begin());
            for (int i = 1; i <= maxCircles; i++)
                circArr.push_back(rand() % 9 + 1);
            LostEnabled = true;
        }
    }

    CloseWindow();
    return 0;
}
