#ifndef STRUCT1_H
#define STRUCT1_H
#include "Common.h"

extern g anh; // Chỉ khai báo, định nghĩa trong file Global.cpp

extern SDL_Texture* spriteSheet;
void renderAnimation(SDL_Texture* spriteSheet, int x, int y, int FRAME_COUNT, int FRAME_WIDTH, int FRAME_HEIGHT);

// Khai báo extern các biến dùng cho animation
extern int FRAME_COUNT;
extern int FRAME_WIDTH;
extern int FRAME_HEIGHT;
extern int ANIMATION_SPEED;  // Nếu dùng lại biến từ str1, bạn có thể bỏ qua nếu không cần
extern int frameIndex;
extern Uint32 lastFrameTime;

#endif // STRUCT1_H
