#include "Game.h"
#include "menu.h"

int main(int argc, char* argv[]) {
    initSDL();
    createRenderer();     // Chỉ gọi 1 lần
    menu menuScreen;
    menuScreen.initMenu();   // Chỉ gọi 1 lần
    menuScreen.renderMenu(); // Render menu ban đầu
    menuScreen.key_process(); // Chờ người dùng nhập phím

    // Nếu check_menu là true (Start Game được chọn), chuyển sang game
    if (menuScreen.getCheckMenu()) {
        menuScreen.cleanup1();
        Game game;
        if (!game.init()) {
            return -1;
        }
        game.run();
        game.cleanup();

    }
    return 0;
}
