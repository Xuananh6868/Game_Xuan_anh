#include "LevelManager.h"
#include <cstdio>

LevelManager::LevelManager()
    : currentLevel(1), coinsPerLevel(20), maxLevel(10), bgMusic(nullptr)
{
    // Khởi tạo mặc định level 1
}

LevelManager::~LevelManager() {
    cleanupMusic();
}

void LevelManager::updateLevel(int coinCount) {
    int newLevel = coinCount / coinsPerLevel + 1;
    if(newLevel > maxLevel)
        newLevel = maxLevel;
    if(newLevel != currentLevel) {
        currentLevel = newLevel;
        std::cout << "Level up! Current level: " << currentLevel << std::endl;
    }
}

void LevelManager::renderLevel() {
    // In thông tin level ở góc phải màn hình
    std::string levelText = "LV: " + std::to_string(currentLevel);
    // Ví dụ: in ra ở góc phải trên với khoảng cách 10 pixel
    SDL_Color white = {255, 255, 255, 255};
    // Giả sử bạn muốn in ở tọa độ (SCREEN_WIDTH - 100, 10)
    renderText(levelText.c_str(), SCREEN_WIDTH - 100, 10, white);
}

bool LevelManager::initMusic() {
    // Khởi tạo SDL_mixer nếu chưa được khởi tạo (bạn có thể gọi Mix_OpenAudio trong main, nhưng đây là ví dụ độc lập)
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "SDL_mixer could not initialize! " << Mix_GetError() << std::endl;
        return false;
    }
    bgMusic = Mix_LoadMUS("nhac_game.mp3");
    if(!bgMusic) {
        std::cout << "Failed to load music: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

void LevelManager::playMusic() {
    if(bgMusic)
        Mix_PlayMusic(bgMusic, -1); // -1: lặp lại vô hạn
}

void LevelManager::cleanupMusic() {
    if(bgMusic) {
        Mix_FreeMusic(bgMusic);
        bgMusic = nullptr;
    }
    Mix_CloseAudio();
}
