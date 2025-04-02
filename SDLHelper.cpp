#include "SDLHelper.h"
#include "struct1.h"
#include <cstdio>

extern g anh; // biến global từ Common.h

// Biến font dùng cho SDL_ttf
TTF_Font* font = nullptr;

// Hàm ghi lỗi và thoát (giữ nguyên cách dùng)
void logErrorAndExit(const char* msg, const char* error) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

void initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());

    anh.window = SDL_CreateWindow("Chicken Invaders Clone",
                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                          SCREEN_WIDTH, SCREEN_HEIGHT,
                          SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (anh.window == nullptr)
        logErrorAndExit("CreateWindow", SDL_GetError());

    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
        logErrorAndExit("SDL_image error:", IMG_GetError());

    if (TTF_Init() == -1) {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        exit(1);
    }
    font = TTF_OpenFont("gamecuben.ttf", 14);
    if (!font)
        logErrorAndExit("TTF_OpenFont", TTF_GetError());
}

void createRenderer() {
    anh.renderer = SDL_CreateRenderer(anh.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (anh.renderer == nullptr)
        logErrorAndExit("CreateRenderer", SDL_GetError());
    SDL_RenderSetLogicalSize(anh.renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL() {
    IMG_Quit();
    SDL_DestroyRenderer(anh.renderer);
    SDL_DestroyWindow(anh.window);
    SDL_Quit();
}

SDL_Texture* loadTexture(const char* filename) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
    SDL_Texture* texture = IMG_LoadTexture(anh.renderer, filename);
    if (texture == NULL)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());
    return texture;
}

void renderTexture(SDL_Texture* texture, int x, int y) {
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(anh.renderer, texture, NULL, &dest);
}

void renderAnimation(SDL_Texture* spriteSheet, int x, int y, int FRAME_COUNT, int FRAME_WIDTH, int FRAME_HEIGHT) {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime > lastFrameTime + ANIMATION_SPEED) {
        frameIndex = (frameIndex + 1) % FRAME_COUNT;
        lastFrameTime = currentTime;
    }
    SDL_Rect srcRect = { frameIndex * FRAME_WIDTH, 0, FRAME_WIDTH, FRAME_HEIGHT };
    SDL_Rect destRect = { x, y, FRAME_WIDTH, FRAME_HEIGHT };
    SDL_RenderCopy(anh.renderer, spriteSheet, &srcRect, &destRect);
}

void renderText(const char* text, int x, int y, SDL_Color color) {
    if (!font) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Font not loaded!");
        return;
    }
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Failed to create surface: %s", TTF_GetError());
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(anh.renderer, surface);
    if (!texture) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Failed to create texture: %s", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }
    SDL_Rect dstRect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(anh.renderer, texture, NULL, &dstRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void waitUntilKeyPressed() {
    SDL_Event e;
    while (true) {
        if (SDL_PollEvent(&e) != 0 &&
            (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return;
        SDL_Delay(20);
    }
}


