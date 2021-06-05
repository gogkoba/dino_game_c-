#pragma once
#include <raylib-cpp.hpp>

extern int form; // variable for determining the running posture

struct Player { // creating a player structure
    Vector2 position;
    float speed;
    bool canJump;
    int dead;
};

struct EnvItem { // create the structure of the environment
    Rectangle rect;
    Color color;
    float speed;
};

struct Testinf { // create the structure of the environment
    int space;
    int down;
};

extern void Playernow(Player *player, EnvItem *envItems, int envItemsLength,
                      float delta, Testinf test);
