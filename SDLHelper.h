#ifndef SDLHELPER_H
#define SDLHELPER_H

#include "Common.h"
#include "def.h"
 void initSDL();
 void createRenderer();
void quitSDL();
SDL_Texture* loadTexture(const char* filename);
void renderTexture(SDL_Texture* texture, int x, int y);
void renderAnimation(SDL_Texture* spriteSheet, int x, int y, int FRAME_COUNT, int FRAME_WIDTH, int FRAME_HEIGHT);
void renderText(const char* text, int x, int y, SDL_Color color);
void waitUntilKeyPressed();
void renderwin();

#endif // SDLHELPER_H
