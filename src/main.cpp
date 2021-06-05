#include "lib.hpp"
#include <fmt/core.h>
#include <raylib-cpp.hpp>
#include <string>

auto count = 0; // variable for calculating animation

std::string livetime = ""; // variable for outputting the result

int main() {

    const int screenWidth = 1600; // indicate the size of the screen
    const int screenHeight = 900;

    raylib::Window window(screenWidth, screenHeight,
                          "Dino"); // create a window with these parameters

    Player player = {0};
    player.position = {735, 500};
    player.speed = 0;
    player.canJump = false;
    player.dead = 0;

    EnvItem envItems[] = {{{0, 650, 1600, 250}, DARKGRAY, 0},
                          {{1600, 450, 90, 200}, RED, -200},
                          {{2700, 350, 80, 50}, RED, -300}};

    Testinf test = {0};
    test.down = 0;
    test.space = 0;

    auto envItemsLength = sizeof(envItems) / sizeof(envItems[0]);

    Texture2D dino1 = LoadTexture("dino-1.png"); // loading textures
    Texture2D dino2 = LoadTexture("dino-1(1).png");
    Texture2D dino3 = LoadTexture("dino-2.png");
    Texture2D dino4 = LoadTexture("dino-2(2).png");

    SetTargetFPS(60); // fps of the game itself

    while (!window.ShouldClose()) { // main loop
        if (player.dead == 1) { // if the player is dead, display his results
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("You are dead", 600, 300, 60, WHITE);
            DrawText("You have lived:", 460, 500, 60, WHITE);
            DrawText(livetime.c_str(), 1025, 500, 60, WHITE);
            DrawText("press enter to continue", 400, 700, 60, WHITE);
            if (IsKeyDown(KEY_ENTER)) { // If the player presses space restarts
                                        // the game
                window.Close();
                main();
            }
            EndDrawing();

        } else {
            float deltaTime =
                GetFrameTime(); // parameter necessary for movement
            Playernow(&player, envItems, envItemsLength, deltaTime,
                      test); // updating the player state
            BeginDrawing();

            ClearBackground(LIGHTGRAY); // paint the whole window gray
            for (int i = 0; i < envItemsLength;
                 i++) { // draw the whole environment
                DrawRectangleRec(envItems[i].rect, envItems[i].color);
            }

            if (form == 0) { // if the player is in the first form
                Rectangle playerRN = {650, player.position.y, 100, 150};
                if (count < 10) { // the player starts a step
                    DrawTexture(dino1, 650, player.position.y, RED);
                    count += 1;
                } else { // the player finishes the step
                    DrawTexture(dino2, 650, player.position.y, RED);
                    count += 1;
                    if (count == 20) {
                        count = 0;
                    }
                }
            } else { // if the player is in the second form
                Rectangle playerRL = {650, player.position.y, 150, 100};
                if (count < 10) {
                    DrawTexture(dino3, 650, player.position.y, RED);
                    count += 1;
                } else {
                    DrawTexture(dino4, 650, player.position.y, RED);
                    count += 1;
                    if (count == 20) {
                        count = 0;
                    }
                }
            }

            const std::string time = fmt::format(
                "{:.0f}", GetTime()); // determine the time of the game

            DrawText(time.c_str(), 1500, 30, 20, DARKGRAY);
            if (player.dead == 1) {
                livetime =
                    time; // if the player is dead, record the time of his death
            }
            EndDrawing();
        }
    }
    UnloadTexture(dino1); // unload textures
    UnloadTexture(dino2);
    UnloadTexture(dino3);
    UnloadTexture(dino4);
    return 0;
}
