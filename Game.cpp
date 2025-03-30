#include "Game.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

// Hàm tạo: khởi tạo giá trị ban đầu, sử dụng hằng số INVINCIBLE_DURATION = 2000 (ms)
Game::Game()
 : bgX(0), running(true), dem(0), heart(3),
    isInvincible(false), invincibleTimer(0),
    INVINCIBLE_DURATION(2000), keyUp(false), keyDown(false),
    keyLeft(false), keyRight(false), keySpace(false),
gameState(PLAYING) // Trạng thái ban đầu là đang chơi
{
    srand(time(0));
}
Game::~Game() {
}

bool Game::init() {
    // Load texture (tên file giữ nguyên)
    background    = loadTexture("photo/background.png");
    spaceship     = loadTexture("photo/spaceship.png");
    shoot         = loadTexture("photo/playerBullet.png");
    alien_shoot   = loadTexture("photo/Anh02.png");
    alien_2       = loadTexture("photo/alien1.png");
    alien_gun     = loadTexture("photo/Alien_gun.png");
    alien_gun_2   = loadTexture("photo/Alien_gun_lv2.png");
    coin_game     = loadTexture("photo/coin.png");
    frame_point   = loadTexture("photo/Frame_coin.png");
    coin_game1    = loadTexture("photo/coin1.png");
    spriteSheet   = loadTexture("photo/destroy1.png");
    spriteSheet_2 = loadTexture("photo/frame_point2.png");
    heart_health  = loadTexture("photo/heart.png");
    win           = loadTexture("photo/win.png");
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048); // Khởi tạo SDL_mixer
    bgMusic = Mix_LoadMUS("music/nhac_game.mp3");
    Mix_PlayMusic(bgMusic, -1); // Phát nhạc lặp vô hạn

    return true;
}

void Game::run() {
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = false;
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:    keyUp = true; break;
                    case SDLK_DOWN:  keyDown = true; break;
                    case SDLK_LEFT:  keyLeft = true; break;
                    case SDLK_RIGHT: keyRight = true; break;
                    case SDLK_SPACE: keySpace = true; break;
                    case SDLK_RETURN: // Nhấn ENTER để chơi lại
                    if (gameState == GAME_OVER) {
                    resetGame();
                    }break;
                    case SDLK_ESCAPE: // Nhấn ESC để thoát
                    running = false;
                    break;
                    }
            }
            if (e.type == SDL_KEYUP) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:    keyUp = false; break;
                    case SDLK_DOWN:  keyDown = false; break;
                    case SDLK_LEFT:  keyLeft = false; break;
                    case SDLK_RIGHT: keyRight = false; break;
                    case SDLK_SPACE: keySpace = false; break;
                }
            }
        }

        // Cập nhật vị trí tàu vũ trụ theo phím
        if (keyUp)
            spaceshipY -= spaceshipSpeed;
        if (keyDown)
            spaceshipY += spaceshipSpeed;
        if (keyLeft)
            spaceshipX -= spaceshipSpeed;
        if (keyRight)
            spaceshipX += spaceshipSpeed;
        if (keySpace) {
            gun.push_back({ spaceshipX + 150, spaceshipY + 54 });
            keySpace = false; // tránh bắn liên tục
        }

        // Giới hạn vị trí tàu không ra ngoài màn hình
        if (spaceshipX < 0)
            spaceshipX = 0;
        if (spaceshipX > SCREEN_WIDTH - 150)
            spaceshipX = SCREEN_WIDTH - 150;
        if (spaceshipY < 0)
            spaceshipY = 0;
        if (spaceshipY > SCREEN_HEIGHT - 100)
            spaceshipY = SCREEN_HEIGHT - 100;

        // Di chuyển background
        bgX -= 1.7;
        if (bgX <= -SCREEN_WIDTH)
            bgX = 0;

        SDL_RenderClear(anh.renderer);

        SDL_Rect bgRect1 = { bgX, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_Rect bgRect2 = { bgX + SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_RenderCopy(anh.renderer, background, NULL, &bgRect1);
        SDL_RenderCopy(anh.renderer, background, NULL, &bgRect2);

        renderTexture(frame_point, 0, 0);
        renderTexture(coin_game1, 85, 3);
        renderTexture(heart_health, 80, 35);

        // Cập nhật và vẽ đạn của spaceship
        for (auto& bullet : gun) {
            bullet.shootX += bullet.speed_gun;
            renderTexture(shoot, bullet.shootX, bullet.shootY);
        }

        // Sinh coin
        coin_spawn_timer++;
        if (coin_spawn_timer >= 300) {
            int coinCount = 2 + rand() % 2; // 2 hoặc 3 coin
            for (int i = 0; i < coinCount; ++i) {
                int randomY = rand() % (SCREEN_WIDTH - 50);
                int randomSpeed = 3 + rand() % 2;
                coins.emplace_back(SCREEN_WIDTH, randomY, randomSpeed);
            }
            coin_spawn_timer = 0;
        }
            lv=dem/15+1;
        // Spawn và di chuyển alien
        if (lv%2==1 && lv<=4) {
            alien_spawn_timer++;
            if (alien_spawn_timer >= 250-lv*5) {
                int randomY = rand() % (SCREEN_HEIGHT - 100);
                aliens.emplace_back(SCREEN_WIDTH, randomY, 1 + rand() % 3);
                alien_spawn_timer = 0;
            }
        } else if(lv%2==0 && lv<=4) {
            alien2_spawn_timer++;
            if (alien2_spawn_timer >= 250-lv*5) {
                int randomY = rand() % (SCREEN_HEIGHT - 100);
                aliens_2.emplace_back(SCREEN_WIDTH, randomY, 1 + rand() % 3);
                alien2_spawn_timer = 0;
            }
        }
            else if(lv<=10 && lv >=5){
                alien_spawn_timer++;
            if (alien_spawn_timer >= 250-lv*5) {
                int randomY = rand() % (SCREEN_HEIGHT - 100);
                aliens.emplace_back(SCREEN_WIDTH, randomY, 1 + rand() % 3);
                alien_spawn_timer = 0;
            }
                        alien2_spawn_timer++;
            if (alien2_spawn_timer >= 250-lv*5) {
                int randomY = rand() % (SCREEN_HEIGHT - 100);
                aliens_2.emplace_back(SCREEN_WIDTH, randomY, 1 + rand() % 3);
                alien2_spawn_timer = 0;
            }
        }
            else {
                renderTexture(win,170,100);
                 char Text[100];
                snprintf(Text, sizeof(Text), "BAN DA THANG CHON ESC OR ENTER");
                SDL_Color Blue  = {64, 224, 208, 255};
                renderText(Text, SCREEN_WIDTH/2-200, 300, Blue);
                SDL_RenderPresent(anh.renderer);
                SDL_Delay(50);
                continue;
        }


        // Cập nhật và vẽ alien nhóm 1
        for (auto& alien : aliens) {
            alien.x -= alien.speed;
            alien.y += alien.yDir * alien.ySpeed;
            if (alien.y <= 0 || alien.y >= SCREEN_HEIGHT - 100)
                alien.yDir *= -1;
            renderTexture(alien_shoot, alien.x, alien.y);
            if (rand() % 200 < lv)
                alienBullets.push_back({ alien.x, alien.y + 50 });
        }

        // Cập nhật và vẽ alien nhóm 2
        for (auto& alien2 : aliens_2) {
            alien2.x -= alien2.speed;
            alien2.y += alien2.yDir * alien2.ySpeed;
            if (alien2.y <= 0 || alien2.y >= SCREEN_HEIGHT - 100)
                alien2.yDir *= -1;
            renderTexture(alien_2, alien2.x, alien2.y);
            if (rand() % 200 < lv)
                alienBullets_2.push_back({ alien2.x, alien2.y + 50 });
        }

        // Vẽ đạn của alien
        for (auto& bullet : alienBullets) {
            bullet.x -= bullet.speed_gun;
            renderTexture(alien_gun, bullet.x, bullet.y);
        }
        for (auto& bullet : alienBullets_2) {
            bullet.x -= bullet.speed_gun;
            renderTexture(alien_gun_2, bullet.x, bullet.y);
        }

        // Vẽ coin
        for (auto& coin : coins) {
            coin.x -= coin.coin_speed;
            renderTexture(coin_game, coin.x, coin.y);
        }

        // Xử lý va chạm giữa đạn của spaceship và alien
        for (auto bulletIt = gun.begin(); bulletIt != gun.end(); ) {
            bool hit = false;

            // Va chạm với quái LV1
            for (auto alienIt = aliens.begin(); alienIt != aliens.end(); ) {
                if (checkCollision(bulletIt->shootX, bulletIt->shootY, 30, 10,
                                   alienIt->x, alienIt->y, 100, 100)) {
                    renderAnimation(spriteSheet, alienIt->x + 3, alienIt->y + 5, 5, 90, 80);
                    alienIt = aliens.erase(alienIt);
                    hit = true;
                    break;
                } else {
                    ++alienIt;
                }
            }

            // Va chạm với quái LV2
            for (auto alienIt = aliens_2.begin(); alienIt != aliens_2.end(); ) {
                if (checkCollision(bulletIt->shootX, bulletIt->shootY, 30, 10,
                                   alienIt->x, alienIt->y, 108, 130)) {
                    renderAnimation(spriteSheet_2, alienIt->x + 3, alienIt->y + 15, 5, 100, 130);
                    alienIt = aliens_2.erase(alienIt);
                    hit = true;
                    break;
                } else {
                    ++alienIt;
                }
            }

            if (hit)
                bulletIt = gun.erase(bulletIt);
            else
                ++bulletIt;
        }

        // "Ăn" coin
        for (auto coinIt = coins.begin(); coinIt != coins.end(); ) {
            if (checkCollision(spaceshipX, spaceshipY, 75, 75,
                               coinIt->x, coinIt->y, 50, 50)) {
                coinIt = coins.erase(coinIt);
                dem++;
            } else if (coinIt->x < -100) {
                coinIt = coins.erase(coinIt);
            } else {
                ++coinIt;
            }
        }

        // Kiểm tra va chạm giữa spaceship và alien/đạn của alien
        if (isInvincible) {
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime > invincibleTimer + INVINCIBLE_DURATION) {
                isInvincible = false;
                std::cout << "Invincibility ended! Spaceship can be hit again." << std::endl;
            }
        }

        bool collisionHandled = false;
        for (auto& alien : aliens) {
            if (!collisionHandled && !isInvincible &&
                checkCollision(spaceshipX, spaceshipY, 50, 50,
                               alien.x, alien.y, 40, 40)) {
                heart--;
                alien.x = -100;
                std::cout << "Lost a life! Lives remaining: " << heart << std::endl;
                if (heart == 0) {
                    std::cout << "Game Over!" << std::endl;
                    gameState = GAME_OVER;
                    break;
                } else {
                    isInvincible = true;
                    invincibleTimer = SDL_GetTicks();
                    collisionHandled = true;
                }
            }
        }

        // Va chạm giữa spaceship và quái LV2
        for (auto& alien : aliens_2) {
            if (!collisionHandled && !isInvincible &&
                checkCollision(spaceshipX, spaceshipY, 50, 50,
                               alien.x, alien.y, 108, 130)) {
                heart--;
                alien.x = -100;
                std::cout << "Lost a life! Lives remaining: " << heart << std::endl;
                if (heart == 0) {
                    std::cout << "Game Over!" << std::endl;
                    gameState = GAME_OVER;
                    break;
                } else {
                    isInvincible = true;
                    invincibleTimer = SDL_GetTicks();
                    collisionHandled = true;
                }
            }
        }

        // Va chạm giữa spaceship và đạn của alien nhóm 1
        for (auto& alien_bullet : alienBullets) {
            if (!collisionHandled && !isInvincible &&
                checkCollision(spaceshipX, spaceshipY, 75, 75,
                               alien_bullet.x, alien_bullet.y, 40, 40)) {
                heart--;
                alien_bullet.x = -100;
                std::cout << "Lost a life! Lives remaining: " << heart << std::endl;
                if (heart == 0) {
                    std::cout << "Game Over!" << std::endl;
                    gameState = GAME_OVER;
                    break;
                } else {
                    isInvincible = true;
                    invincibleTimer = SDL_GetTicks();
                    collisionHandled = true;
                }
            }
        }

        // Va chạm giữa spaceship và đạn của alien nhóm 2
        for (auto& alien_bullet : alienBullets_2) {
            if (!collisionHandled && !isInvincible &&
                checkCollision(spaceshipX, spaceshipY, 75, 75,
                               alien_bullet.x, alien_bullet.y, 40, 40)) {
                heart--;
                alien_bullet.x = -100;
                std::cout << "Lost a life! Lives remaining: " << heart << std::endl;
                if (heart == 0) {
                    std::cout << "Game Over!" << std::endl;
                    gameState = GAME_OVER;
                    break;
                } else {
                    isInvincible = true;
                    invincibleTimer = SDL_GetTicks();
                    collisionHandled = true;
                }
            }
        }
        if (gameState == GAME_OVER) {

                char Text[100];
                snprintf(Text, sizeof(Text), "BAN DA THUA CHON ESC OR ENTER");
                SDL_Color Blue  = {64, 224, 208, 255};
                renderText(Text, SCREEN_WIDTH/2-200, 300, Blue);
                SDL_RenderPresent(anh.renderer);
                SDL_Delay(50);
                continue; // Không xử lý game khi đã chết

        }

        // Vẽ spaceship (nhấp nháy khi bất tử)
        if (!isInvincible || (SDL_GetTicks() % 500 < 250))
            renderTexture(spaceship, spaceshipX, spaceshipY);

        // Vẽ thông tin coin và số mạng
        char coinText[32];
        char heartText[50];
        char levelText[20];
        snprintf(coinText, sizeof(coinText), "Coin: %d", dem);
        snprintf(heartText, sizeof(heartText), "Lives: %d", heart);
        snprintf(levelText, sizeof(levelText), "Lv: %d  Esc" , lv );
        SDL_Color Blue  = {64, 224, 208, 255};
        SDL_Color Green = {57, 255, 20, 255};
        renderText(coinText, 4, 10, Blue);
        renderText(heartText, 5, 40, Green);
        renderText(levelText, SCREEN_WIDTH-100, 5, Green);

        SDL_RenderPresent(anh.renderer);
        SDL_Delay(13);

        // Xóa các đối tượng đã ra ngoài màn hình
        aliens.erase(
            remove_if(aliens.begin(), aliens.end(),
                      [](Alien& a) { return a.x < -100; }),
            aliens.end());
        aliens_2.erase(
            remove_if(aliens_2.begin(), aliens_2.end(),
                      [](Alien& a) { return a.x < -100; }),
            aliens_2.end());
        alienBullets.erase(
            remove_if(alienBullets.begin(), alienBullets.end(),
                      [](Alien& h) { return h.x < -100; }),
            alienBullets.end());
        gun.erase(
            remove_if(gun.begin(), gun.end(),
                      [](guner& b) { return b.shootX > SCREEN_WIDTH; }),
            gun.end());
    }
}

void Game::cleanup() {
    SDL_DestroyTexture(spaceship);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(shoot);
    SDL_DestroyTexture(alien_shoot);
    SDL_DestroyTexture(alien_gun);
    SDL_DestroyTexture(coin_game);
    SDL_DestroyTexture(spriteSheet);
    SDL_DestroyTexture(win);
    Mix_FreeMusic(bgMusic);
    Mix_CloseAudio();
    quitSDL();
}
void Game::resetGame() {
    dem = 0;
    heart = 3;
    spaceshipX = 100;
    spaceshipY = SCREEN_HEIGHT / 2;
    gun.clear();
    aliens.clear();
    aliens_2.clear();
    alienBullets.clear();
    alienBullets_2.clear();
    coins.clear();
    isInvincible = false;
    invincibleTimer = 0;
    gameState = PLAYING; // Chơi lại game
}


