#include "catch.hpp"
#include "lib.hpp"

TEST_CASE("doing nothing") {
    Player player = {0};
    player.position = {735, 500};
    player.speed = 0;
    player.canJump = false;
    player.dead = 0;

    EnvItem envItems[] = {{{0, 650, 1600, 250}, DARKGRAY, 0},
                          {{1600, 450, 90, 200}, RED, -200},
                          {{2700, 350, 80, 50}, RED, -300}};

    auto envItemsLength = sizeof(envItems) / sizeof(envItems[0]);

    float deltaTime = 0.0161;

    Testinf test = {0};
    test.down = 0;
    test.space = 0;

    for (int i = 0; i < 300; i++) { // 237 - min
        Playernow(&player, envItems, envItemsLength, deltaTime, test);
    }
    REQUIRE(player.dead == 1);
}

TEST_CASE("Can you move?") {
    Player player = {0};
    player.position = {735, 500};
    player.speed = 0;
    player.canJump = false;
    player.dead = 0;

    EnvItem envItems[] = {{{0, 650, 1600, 250}, DARKGRAY, 0},
                          {{1600, 450, 90, 200}, RED, -200},
                          {{2700, 350, 80, 50}, RED, -300}};

    auto envItemsLength = sizeof(envItems) / sizeof(envItems[0]);

    float deltaTime = 0.0161;

    Testinf test = {0};
    test.down = 0;
    test.space = 1;

    for (int i = 0; i < 300; i++) {
        Playernow(&player, envItems, envItemsLength, deltaTime, test);
        if (player.speed != 0) {
            break;
        }
    }
    REQUIRE(player.speed != 0);
}

TEST_CASE("can you jump?") {
    Player player = {0};
    player.position = {735, 500};
    player.speed = 0;
    player.canJump = false;
    player.dead = 0;

    EnvItem envItems[] = {{{0, 650, 1600, 250}, DARKGRAY, 0},
                          {{1600, 450, 90, 200}, RED, -200},
                          {{2700, 350, 80, 50}, RED, -300}};

    auto envItemsLength = sizeof(envItems) / sizeof(envItems[0]);

    float deltaTime = 0.0161;

    Testinf test = {0};
    test.down = 0;
    test.space = 0;

    for (int i = 0; i < 300; i++) {
        Playernow(&player, envItems, envItemsLength, deltaTime, test);
        if (i == 200) {
            test.space = 1;
        }
    }
    REQUIRE(player.dead == 0);
}

TEST_CASE("transformation") {
    Player player = {0};
    player.position = {735, 500};
    player.speed = 0;
    player.canJump = false;
    player.dead = 0;

    EnvItem envItems[] = {{{0, 650, 1600, 250}, DARKGRAY, 0},
                          {{1600, 450, 90, 200}, RED, -200},
                          {{2700, 350, 80, 50}, RED, -300}};

    auto envItemsLength = sizeof(envItems) / sizeof(envItems[0]);

    float deltaTime = 0.0161;

    Testinf test = {0};
    test.down = 1;
    test.space = 0;

    for (int i = 0; i < 30; i++) {
        Playernow(&player, envItems, envItemsLength, deltaTime, test);
    }
    REQUIRE(player.position.y == 550);
}
