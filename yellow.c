#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_BALLS 50

typedef struct Particle{
    Vector2 position;
    Vector2 velocity;
    float radius;
    Color color;
    bool active;
}Particle;

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "[core]");
   

   Particle particles[MAX_BALLS] = {0};
   Vector2 mousePos = {0};

   bool mouseClicked = false;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // updated mouse input
        mouseClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
        mousePos = GetMousePosition();


        //SPAWN THE PARTICLES
        if(mouseClicked){
            for(int i = 0; i < MAX_BALLS; i++){
                if(!particles[i].active){
                    particles[i].active = true;
                    particles[i].position = mousePos;
                    particles[i].velocity.x = (float)GetRandomValue(-100, 100) / 50.0f;
                    particles[i].velocity.y = (float)GetRandomValue(-100, 100) / 50.0f;
                    particles[i].radius = (float) GetRandomValue(1, 10);
                    particles[i].color = (Color){250, 225, 201, 255};

                }
            }
        }

        //Update particle LifeTime and Position
        for(int i = 0; i < MAX_BALLS; i++){
            if (particles[i].active) {
                particles[i].position.x += particles[i].velocity.x;
                particles[i].position.y += particles[i].velocity.y;
                particles[i].radius -= 0.05f;

                if(particles[i].radius <= 0){
                    particles[i].active = false;
                }
            }
        }

        
        BeginDrawing();

            //Draw Particle
            for (int i = 0; i < MAX_BALLS; i++) {
            if (particles[i].active) {
                DrawCircleV(particles[i].position, particles[i].radius, particles[i].color);
            }
        }


            
            ClearBackground(LIGHTGRAY);

            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
            //DrawCircleV(ballPos, 20, MAROON);

            //if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            // ballPos = GetMousePosition();  
            //}

            

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}