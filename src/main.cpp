#include <fmt/core.h>
#include <raylib-cpp.hpp>
#include <string>

int G = 625;
int PLAYER_JUMP_SPD = 700;

typedef struct Player {
    Vector2 position;
    float speed;
    bool canJump;
    int dead;
} Player;

typedef struct EnvItem {
    Rectangle rect;
    Color color;
    float speed;
} EnvItem;

auto count = 0;
auto form = 0;
std::string livetime = "";

void Playernow(Player *player, EnvItem *envItems, int envItemsLength,
               float delta) {
    if (IsKeyDown(KEY_SPACE) && player->canJump == true) {
        player->speed = -PLAYER_JUMP_SPD;
        player->canJump = false;
    }
    if (IsKeyDown(KEY_DOWN) && player->canJump == true &&
        !IsKeyDown(KEY_SPACE)) {
        if (form == 0) {
            player->position.y += 50;
        }
        form = 1;

    } else {
        if (form == 1) {
            form = 0;
            player->position.y -= 50;
        }
    }

    auto stopmove = 0;

    if (player->position.y + player->speed * delta >= 500) {
        player->speed = 0;
        player->canJump = true;
        stopmove = 1;
    }

    for (int i = 1; i < envItemsLength; i++) {
        auto xen = envItems[i].rect.x;
        auto yen = envItems[i].rect.y;
        auto width = envItems[i].rect.width;
        auto height = envItems[i].rect.height;
        auto plwidth = 150;
        auto plheight = 100;
        if (form == 0) {
            plwidth = 100;
            plheight = 150;
        }

        if (625 + plwidth >= (xen + envItems[i].speed * delta) &&
            650 <= (xen + envItems[i].speed * delta + width) &&
            (player->position.y + player->speed * delta + plheight) >= yen &&
            (player->position.y + player->speed * delta) <= yen + height) {
            player->dead = 1;
        }
    }
    player->position.y += player->speed * delta;
    if (stopmove == 0) {
        player->speed += G * delta;
    }
    for (int i = 1; i < envItemsLength; i++) {
        envItems[i].rect.x += envItems[i].speed * delta;
        if (envItems[i].rect.x + envItems[i].rect.width < 0) {
            envItems[i].rect.x = std::rand() % 2000 + 1600;
        }
    }
    for (int i = 1; i < envItemsLength; i++) {
        if (envItems[i].speed > -400) {
            envItems[i].speed -= 0.25;
        }
    }
}

int main() {

    const int screenWidth = 1600;
    const int screenHeight = 900;

    raylib::Window window(screenWidth, screenHeight, "Dino");

    Player player = {0};
    player.position = {735, 500};
    player.speed = 0;
    player.canJump = false;
    player.dead = 0;

    EnvItem envItems[] = {{{0, 650, 1600, 250}, DARKGRAY, 0},
                          {{1600, 450, 90, 200}, RED, -200},
                          {{2700, 350, 80, 50}, RED, -300}};

    auto envItemsLength = sizeof(envItems) / sizeof(envItems[0]);

    Texture2D dino1 = LoadTexture("dino-1.png");
    Texture2D dino2 = LoadTexture("dino-1(1).png");
    Texture2D dino3 = LoadTexture("dino-2.png");
    Texture2D dino4 = LoadTexture("dino-2(2).png");

    SetTargetFPS(60);

    while (!window.ShouldClose()) {
        if (player.dead == 1) {
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("You are dead", 600, 300, 60, WHITE);
            DrawText("You have lived:", 460, 500, 60, WHITE);
            DrawText(livetime.c_str(), 1025, 500, 60, WHITE);
            DrawText("press space to continue", 400, 700, 60, WHITE);
            if (IsKeyDown(KEY_SPACE)) {
                window.Close();
                main();
            }
            EndDrawing();

        } else {
            float deltaTime = GetFrameTime();
            Playernow(&player, envItems, envItemsLength, deltaTime);
            BeginDrawing();

            ClearBackground(LIGHTGRAY);
            for (int i = 0; i < envItemsLength; i++) {
                DrawRectangleRec(envItems[i].rect, envItems[i].color);
            }

            if (form == 0) {
                Rectangle playerRN = {650, player.position.y, 100, 150};
                if (count < 10) {
                    DrawTexture(dino1, 650, player.position.y, RED);
                    count += 1;
                } else {
                    DrawTexture(dino2, 650, player.position.y, RED);
                    count += 1;
                    if (count == 20) {
                        count = 0;
                    }
                }
            } else {
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

            const std::string time = fmt::format("{:.0f}", GetTime());
            DrawText(time.c_str(), 1500, 30, 20, DARKGRAY);
            if (player.dead == 1) {
                livetime = time;
            }
            EndDrawing();
        }
    }
    UnloadTexture(dino1);
    UnloadTexture(dino2);
    UnloadTexture(dino3);
    UnloadTexture(dino4);
    return 0;
}
