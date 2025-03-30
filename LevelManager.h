#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "Common.h"
#include "def.h"
#include "SDLHelper.h"
#include <SDL_mixer.h>
#include <string>

class LevelManager {
public:
    LevelManager();
    ~LevelManager();

    // Cập nhật level dựa trên số coin đã ăn (ví dụ: mỗi 20 coin tăng 1 level, tối đa 10)
    void updateLevel(int coinCount);

    // Render thông tin level (in góc phải màn hình)
    void renderLevel();

    // Các hàm liên quan đến nhạc nền
    bool initMusic();
    void playMusic();
    void cleanupMusic();

    // Getter cho current level
    int getLevel() const { return currentLevel; }

private:
    int currentLevel;
    const int coinsPerLevel; // Số coin cần để tăng 1 level
    const int maxLevel;

    // Nhạc nền sử dụng SDL_mixer
    Mix_Music* bgMusic;
};

#endif // LEVELMANAGER_H
