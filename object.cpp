#include "object.h"

bool checkCollision(int bulletX, int bulletY, int bulletW, int bulletH,
                    int alienX, int alienY, int alienW, int alienH)
{
    SDL_Rect bulletRect = { bulletX, bulletY, bulletW, bulletH };
    SDL_Rect alienRect = { alienX, alienY, alienW, alienH };
    return SDL_HasIntersection(&bulletRect, &alienRect);
}
