#pragma once
#include <raylib-cpp.hpp>

extern int form; ///< variable for determining the running posture

/**
 * structure storing user data
 */
struct Player {       // creating a player structure
    Vector2 position; ///< player location
    float speed;      ///< player speed (vertical)
    bool canJump;     ///< variable allowing to jump
    int dead;         ///< player touched the object
};

/**
 * structure storing objects data
 */
struct EnvItem {    // create the structure of the environment
    Rectangle rect; ///< location and dimensions
    Color color;    ///< color
    float speed;    ///< speed (horizontal)
};

/**
 * structure for testing
 */
struct Testinf { // create the structure of the environment
    int space;   ///< parameter responsible for simulating pressing space
    int down;    ///< parameter responsible for simulating pressing down
};
/**
 * the function in which the states of the
 * player and the environment are determined,
 * their position changes.
 * \param player to work with the player's position
 * \param envItems to work with the position of objects
 * \param envItemsLength number of objects
 * \param delta to measure time
 * \param test for testing
 * \
 */
extern void Playernow(Player *player, EnvItem *envItems, int envItemsLength,
                      float delta, Testinf test);
