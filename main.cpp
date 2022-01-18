#include "raylib.h"

struct Ball
{
    float x, y;
    float radius;
    float speedX;
    float speedY;

    void Draw()
    {
        DrawCircle
        (
            (int) x,
            (int) y,
            radius,
            WHITE
         );
    }
};

struct Paddle
{
    float x, y;
    float speed;
    float width, height;

    void Draw()
    {
        DrawRectangle
        (
            x - (width / 2),
            y - (width / 2),
            width,
            height,
            WHITE
        );
    }
};

int main(){
    const int WINDOW_WIDTH  = 800;
    const int WINDOW_HEIGHT = 600;
    const int PADDLE_SIZE   = 100;
    const int CIRCLE_SIZE   = 5;
    const int INITIAL_BALL_SPEED = 200;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pong");
    SetWindowState(FLAG_VSYNC_HINT);

    Ball ball;
    ball.x = GetScreenWidth() / 2.0f;
    ball.y = GetScreenHeight() / 2.0f;
    ball.radius = CIRCLE_SIZE;
    ball.speedX = INITIAL_BALL_SPEED;
    ball.speedY = INITIAL_BALL_SPEED;

    Paddle leftPaddle;
    leftPaddle.x = 50;
    leftPaddle.y = GetScreenHeight() / 2 - (PADDLE_SIZE / 2);
    leftPaddle.width = 10;
    leftPaddle.height = 100;
    leftPaddle.speed = 300;
    //leftPaddle.color = WHITE;

    Paddle rightPaddle;
    rightPaddle.x = GetScreenWidth() - (PADDLE_SIZE / 2) - 10;
    rightPaddle.y = GetScreenHeight() / 2 - (PADDLE_SIZE / 2);
    rightPaddle.width = 10;
    rightPaddle.height = 100;
    rightPaddle.speed = 300;
    //rightPaddle.color = WHITE;

    while (!WindowShouldClose())
    {
        ball.x += ball.speedX * GetFrameTime();
        ball.y += ball.speedY * GetFrameTime();

        if ((ball.y > GetScreenHeight()) || (ball.y < 0))
        {
            ball.speedY *= -1;
        }

        BeginDrawing();
            ClearBackground(BLACK); 
            
            ball.Draw();
            leftPaddle.Draw();
            rightPaddle.Draw();

            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
