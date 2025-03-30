#ifndef OBJECT_H_
#define OBJECT_H_

#include <SDL.h>
#include "struct1.h"

bool checkCollision(int bulletX, int bulletY, int bulletW, int bulletH,
                    int alienX, int alienY, int alienW, int alienH);

#endif // OBJECT_H_
