#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>

struct g {
    SDL_Renderer* renderer;
    SDL_Window* window;
};
extern g anh;
extern bool check_menu;


#include "def.h"

#endif // COMMON_H
