#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


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
    

    Rectangle rect = { 50, 50, 70, 40};
    char* text = "water";
    Color textColor = {0, 0, 190, 100};
    Color rectColor = {50, 0, 255, 100};
    
    // .   50, 50, 70, 40, (Color){0, 0, 190, 100}
 
   bool mouseClicked = false;

   bool selectMode = false;
   bool shapeDrawn = false;
   Rectangle selectRect = {0};
   Vector2 startPoint = { 0 };
   Vector2 endPoint = { 0 };

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------











    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
    
        
        if(IsKeyPressed(KEY_B)){
            selectMode = true;         
			shapeDrawn = false;
        }

        if(selectMode){
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                startPoint = GetMousePosition();
            }
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                endPoint = GetMousePosition();

                selectRect.x = fminf(startPoint.x, endPoint.x);
                selectRect.y = fminf(startPoint.y, endPoint.y);
                selectRect.width = fabsf(endPoint.x - startPoint.x);
                selectRect.height = fabsf(endPoint.y - startPoint.y);

                shapeDrawn = true;
            } else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                selectMode = false;
            }
        }
        // updated mouse input
        mouseClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
        mousePos = GetMousePosition();


        
        //SPAWN THE PARTICLES WHEN 'P' KEY IS PRESSED
        if(IsKeyPressed(KEY_P)){
        for(int i = 0; i < MAX_BALLS; i++){
            if(!particles[i].active){
                particles[i].active = true;
                particles[i].position = mousePos;
                particles[i].velocity.x = (float)GetRandomValue(-100, 100) / 50.0f;
                particles[i].velocity.y = (float)GetRandomValue(-100, 100) / 50.0f;
                particles[i].radius = (float) GetRandomValue(1, 10);

                int colorIndex = GetRandomValue(0, 2);
                switch(colorIndex){
                    case 0:
                        particles[i].color = (Color){255, 255, 137, 255}; // #ffff89
                        break;
                    case 1:
                        particles[i].color = (Color){227, 51, 30, 255}; // #e3331e
                        break;
                    case 2:
                        particles[i].color = (Color){18, 10, 2, 255}; // #120a02
                        break;
                }

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

    // ... Rest of the code ...





        
        BeginDrawing();


            if(shapeDrawn) {
                DrawRectangleRec(selectRect, (Color){255, 0, 0, 100});
            }
            /*
            else if(selectMode) {
                DrawRectangleLinesEx(selectRect, 2, RED);
            }
            */
            ClearBackground(LIGHTGRAY);

            //Draw Particle
            for (int i = 0; i < MAX_BALLS; i++) {
                if (particles[i].active) {
                    DrawCircleV(particles[i].position, particles[i].radius, particles[i].color);
                }
            }

            DrawText("Press: P for Particles, Press B for Box Select", 190, 200, 20, WHITE);
            //water
            
           DrawRectangle(50, 50, 70, 40, textColor);
            

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}


                        
