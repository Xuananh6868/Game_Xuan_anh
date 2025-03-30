#ifndef GAME_H
#define GAME_H

#include "Common.h"
#include "str1.h"
#include "struct1.h"
#include "SDLHelper.h"
#include "object.h"
#include "LevelManager.h"
#include <vector>


class Game {
public:
    Game();
    ~Game();
    bool init();
    void run();
    void cleanup();
    void resetGame();

private:
    // Texture
    SDL_Texture* background;
    SDL_Texture* spaceship;
    SDL_Texture* shoot;
    SDL_Texture* alien_shoot;
    SDL_Texture* alien_2;
    SDL_Texture* alien_gun;
    SDL_Texture* alien_gun_2;
    SDL_Texture* coin_game;
    SDL_Texture* frame_point;
    SDL_Texture* coin_game1;
    SDL_Texture* spriteSheet;
    SDL_Texture* spriteSheet_2;
    SDL_Texture* heart_health;
    SDL_Texture* win;

    int bgX;
    bool running;
    SDL_Event e;
    int dem=0;
    int lv;
    int heart;
    bool isInvincible;
    Uint32 invincibleTimer;
    const Uint32 INVINCIBLE_DURATION;
    enum GameState { PLAYING, GAME_OVER };
    GameState gameState;


    std::vector<guner> gun;
    std::vector<Alien> aliens;
    std::vector<Alien> aliens_2;
    std::vector<Alien> alienBullets;
    std::vector<Alien> alienBullets_2;
    std::vector<Coin> coins;

    // Trạng thái phím
    bool keyUp, keyDown, keyLeft, keyRight, keySpace;
        Mix_Music* bgMusic;
};

#endif // GAME_H
