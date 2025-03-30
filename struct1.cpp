#include "struct1.h"

// Nếu cần các hằng số animation, định nghĩa chúng tại đây (ví dụ)
int FRAME_COUNT = 5;
int FRAME_WIDTH = 90;
int FRAME_HEIGHT = 80;

// Định nghĩa lại biến animation (nếu chưa dùng biến ANIMATION_SPEED từ str1.h)
int frameIndex = 0;
Uint32 lastFrameTime = 0;

// Nếu spriteSheet được dùng ở nhiều nơi, bạn cũng định nghĩa nó ở đây
SDL_Texture* spriteSheet = nullptr;
