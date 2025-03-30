#ifndef STR1_H_
#define STR1_H_

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

struct guner {
    int shootX;
    int shootY;
    int speed_gun = 10;
};

struct Alien {
    int x;
    int y;
    int speed = 5;
    int speed_gun = 5;
    int yDir;
    int ySpeed;

    Alien(int posX = 0, int posY = 0, int s = 0) : x(posX), y(posY), speed(s) {
        yDir = (rand() % 2 == 0) ? 1 : -1;
        ySpeed = 1 + rand() % 2;
    }
};

struct Coin {
    int x, y;
    int coin_speed;
    Coin(int _x = 0, int _y = 0, int _coin_speed = 0)
        : x(_x), y(_y), coin_speed(_coin_speed) {}
    bool collected = false; // Đánh dấu đã ăn chưa
};

// Chỉ khai báo với extern
extern int alien_spawn_timer;
extern int alien2_spawn_timer;
extern int coin_spawn_timer;
extern int spaceshipX;
extern int spaceshipY;
extern int spaceshipSpeed;
extern int ANIMATION_SPEED; // Độ trễ giữa các frame (ms)

#endif // STR1_H_
