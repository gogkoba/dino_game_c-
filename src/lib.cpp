#include "lib.hpp"
#include <raylib-cpp.hpp>
#include <string>

;
int G = 625;               // introduce gravity
int PLAYER_JUMP_SPD = 700; // introduce the jump force
int form = 0;              // variable for determining the running posture

void Playernow(Player *player, EnvItem *envItems, int envItemsLength,
               float delta,
               Testinf test) { // the function in which the states of the
                               // player and the environment are determined,
                               // their position changes.
    if ((IsKeyDown(KEY_SPACE) || test.space == 1) &&
        player->canJump == true) { // jump conditions
        player->speed = -PLAYER_JUMP_SPD;
        player->canJump = false;
    }
    if ((IsKeyDown(KEY_DOWN) || test.down == 1) && player->canJump == true &&
        !(IsKeyDown(KEY_SPACE) ||
          test.space == 1)) { // conditions for changing the running position
        if (form == 0) {
            player->position.y += 50;
        }
        form = 1;

    } else { // checking if you need to revert to standard form
        if (form == 1) {
            form = 0;
            player->position.y -= 50;
        }
    }

    auto stopmove = 0;

    if (player->position.y + player->speed * delta >=
        500) { // conditions for touching the floor and stopping falling
        player->speed = 0;
        player->canJump = true;
        stopmove = 1;
    }

    for (int i = 1; i < envItemsLength;
         i++) { // loop for checking the touch of elements
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
            (player->position.y + player->speed * delta) <=
                yen + height) { // the contact conditions themselves
            player->dead = 1;
        }
    }
    player->position.y +=
        player->speed * delta; // changing the position of the player
    if (stopmove ==
        0) { // if the player is not on the floor, we accelerate him down
        player->speed += G * delta;
    }
    for (int i = 1; i < envItemsLength;
         i++) { // a loop that returns items as they go off the screen to the
                // left
        envItems[i].rect.x += envItems[i].speed * delta;
        if (envItems[i].rect.x + envItems[i].rect.width < 0) {
            envItems[i].rect.x = std::rand() % 2000 + 1600;
        }
    }
    for (int i = 1; i < envItemsLength;
         i++) { // conditions for increasing the difficulty of the game
        if (envItems[i].speed > -400) {
            envItems[i].speed -= 0.25;
        }
    }
}
