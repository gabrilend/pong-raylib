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
        DrawRectangleRec
        (
            GetRect(),
            WHITE
        );
    }

    Rectangle GetRect()
    {
        return Rectangle
        { 
            x - (width / 2), 
            y - (height / 2), 
            10, 
            100
        };
    }
};

int main(){
    const int WINDOW_WIDTH  = 800;
    const int WINDOW_HEIGHT = 600;
    const int PADDLE_SIZE   = 100;
    const int CIRCLE_SIZE   = 5;
    const int INITIAL_BALL_SPEED = 200;
    const char* winnerText = nullptr;

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

        if (IsKeyDown(KEY_W))
        {
            leftPaddle.y -= leftPaddle.speed * GetFrameTime();
        }

        if (IsKeyDown(KEY_S))
        {
            leftPaddle.y += leftPaddle.speed * GetFrameTime();
        }

        if (IsKeyDown(KEY_UP))
        {
            rightPaddle.y -= rightPaddle.speed * GetFrameTime();
        }

        if (IsKeyDown(KEY_DOWN))
        {
            rightPaddle.y += rightPaddle.speed * GetFrameTime();
        }

        if (CheckCollisionCircleRec(
                Vector2{ball.x, ball.y},
                ball.radius,
                leftPaddle.GetRect()))
            {
                if (ball.speedX < 0)
                {
                    ball.speedX *= -1.1f;
                    ball.speedY = (ball.y - leftPaddle.y) /
                                  (leftPaddle.height / 2) *
                                  ball.speedX;
                }
            }

        if (CheckCollisionCircleRec(
                Vector2{ball.x, ball.y},
                ball.radius,
                rightPaddle.GetRect()))
            {   
                if (ball.speedX > 0)
                {
                    ball.speedX *= -1.1f;
                    ball.speedY = (ball.y - rightPaddle.y) /
                                  (rightPaddle.height / 2) *
                                  -ball.speedX;
                }
            }

        if (ball.x < 0)
        {
            winnerText = "Right Player Wins!";
        }
        if (ball.x > GetScreenWidth())
        {
            winnerText = "Left Player Wins!";
        }
        if (winnerText && IsKeyPressed(KEY_SPACE))
        {
            ball.x = GetScreenWidth() / 2;
            ball.y = GetScreenHeight() / 2;
            ball.speedX = 300;
            ball.speedY = 300;
            winnerText = nullptr;
        }

        BeginDrawing();
            ClearBackground(BLACK); 
            
            ball.Draw();
            leftPaddle.Draw();
            rightPaddle.Draw();

            if (winnerText)
            {
                int textWidth = MeasureText(winnerText, 60);
                DrawText(winnerText,
                         (GetScreenWidth() / 2) - (textWidth / 2),
                         (GetScreenHeight() / 2) - 30,
                         60,
                         YELLOW
                );
            }

            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

