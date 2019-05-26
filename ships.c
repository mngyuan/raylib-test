/*******************************************************************************************
*
*   raylib [textures] example - Texture loading and drawing a part defined by a rectangle
*
*   This example has been created using raylib 1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include <math.h>

#define MAX_FRAME_SPEED     15
#define MIN_FRAME_SPEED      1
#define PIXEL_SCALE          6

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;

    SetConfigFlags(FLAG_MSAA_4X_HINT);

    InitWindow(screenWidth, screenHeight, "raylib [texture] example - texture rectangle");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D ships = LoadTexture("resources/ships.png");
    Texture2D ocean = LoadTexture("resources/ocean.png");

    // Rendering will happen like so
    // 1. An inner RenderTexture2D, which is by default y flipped because of OpenGL y coords
    // 2. An outer RenderTexture2D, which we use to scale and unflip
    // 3. A camera will look at these 2D textures
    Camera camera = { 0 };
    camera.position = (Vector3){ 8.0f, 8.0f, 8.0f };
    camera.target = (Vector3){ 0.0f, 1.5f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.type = CAMERA_PERSPECTIVE;
    SetCameraMode(camera, CAMERA_ORBITAL);

    RenderTexture2D target = LoadRenderTexture(screenWidth / PIXEL_SCALE, screenHeight / PIXEL_SCALE);
    RenderTexture2D targetFlipped = LoadRenderTexture(screenWidth / PIXEL_SCALE, screenHeight / PIXEL_SCALE);

    // Sprite setup
    Vector2 position = { 160.0f, 90.0f };
    Vector2 direction = {0, 1.0f};
    float speed = 1.0f;
    const float maxSpeed = 1.5f;
    const float accel = 0.1f;
    const float turnSpeed = PI / 2 / 60;
    Rectangle frameRec = { 0.0f, 0.0f, (float)ships.width/8, (float)ships.height/4 };
    int currentFrame = 0;

    int framesCounter = 0;
    int framesSpeed = 8;            // Number of spritesheet frames shown by second

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float speedFraction = speed / maxSpeed;
        float currentTurnSpeed = turnSpeed * speedFraction;
        if (IsKeyDown(KEY_LEFT)) {
            direction = (Vector2){
                direction.x * cos(-currentTurnSpeed) - direction.y * sin(-currentTurnSpeed),
                direction.x * sin(-currentTurnSpeed) + direction.y * cos(-currentTurnSpeed)
            };
        }
        if (IsKeyDown(KEY_RIGHT)) {
            direction = (Vector2){
                direction.x * cos(currentTurnSpeed) - direction.y * sin(currentTurnSpeed),
                direction.x * sin(currentTurnSpeed) + direction.y * cos(currentTurnSpeed)
            };
        }
        float angle = -atan2(direction.y, direction.x);
        if (angle < PI / 8 && angle > -PI / 8) currentFrame = 3; // E
        else if (angle < 3 * PI / 8 && angle > PI / 8) currentFrame = 7; // NE
        else if (angle < 5 * PI / 8 && angle > 3 * PI / 8) currentFrame = 6; // N
        else if (angle < 7 * PI / 8 && angle > 5 * PI / 8) currentFrame = 5; // NW
        else if (angle < -7 * PI / 8 || angle > 7 * PI / 8) currentFrame = 4; // W
        else if (angle < -5 * PI / 8 && angle > -7 * PI / 8) currentFrame = 0; // SW
        else if (angle < -3 * PI / 8 && angle > -5 * PI / 8) currentFrame = 1; // S
        else if (angle < -1 * PI / 8 && angle > -3 * PI / 8) currentFrame = 2; // SE
        if (IsKeyDown(KEY_UP)) speed = fmin(speed + accel, maxSpeed);
        else if (!IsKeyDown(KEY_DOWN)) speed = fmax(speed - accel / 24, 0);
        if (IsKeyDown(KEY_DOWN)) speed = fmax(speed - accel / 8, 0);
        position = (Vector2){ position.x + direction.x * speed, position.y + direction.y * speed };
        frameRec.x = (float)currentFrame*(float)ships.width/8;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera);
        BeginDrawing();

            ClearBackground(RAYWHITE);
            BeginTextureMode(target);
                ClearBackground(RAYWHITE);
                DrawTextureV(ocean, (Vector2) {0, 0}, WHITE);
                DrawTexture(ships, 15, 40, WHITE);
                DrawRectangleLines(15, 40, ships.width, ships.height, LIME);
                DrawRectangleLines(15 + frameRec.x, 40 + frameRec.y, frameRec.width, frameRec.height, RED);

                DrawText("FRAME SPEED: ", 165, 210, 10, DARKGRAY);
                /*DrawText(TextFormat("%02i FPS", framesSpeed), 575, 210, 10, DARKGRAY);*/
                DrawText("PRESS RIGHT/LEFT KEYS to CHANGE SPEED!", 290, 240, 10, DARKGRAY);

                for (int i = 0; i < MAX_FRAME_SPEED; i++)
                {
                    if (i < framesSpeed) DrawRectangle(250 + 21*i, 205, 20, 20, RED);
                    DrawRectangleLines(250 + 21*i, 205, 20, 20, MAROON);
                }

                DrawTextureRec(ships, frameRec, position, WHITE);  // Draw part of the texture

                DrawText("(c) Scarfy sprite by Eiden Marsal", screenWidth - 200, screenHeight - 20, 10, GRAY);
            EndTextureMode();

            BeginTextureMode(targetFlipped);
                DrawTextureRec(
                    target.texture,
                    (Rectangle){ 0, 0, target.texture.width, target.texture.height },
                    (Vector2) {0, 0},
                    WHITE
                );
            EndTextureMode();
            DrawTextureEx(targetFlipped.texture, (Vector2){ 0, 0}, 0.0f, (float)PIXEL_SCALE, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(ships);       // Texture unloading
    UnloadRenderTexture(target);

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
