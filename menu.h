#ifndef MENU_H
#define MENU_H

#include "Common.h"
#include "def.h"

class menu {
public:
    menu();
    ~menu();
    // Hàm khởi tạo menu: chỉ load texture và tạo renderer 1 lần
    void initMenu();
    // Hàm render menu
    void renderMenu();
    // Hàm xử lý phím (vòng lặp chờ cho đến khi nhấn Enter)
    void key_process();
    void cleanup1();
    bool getCheckMenu() const { return check_menu; }
private:
    SDL_Texture* menu_game;
    SDL_Texture* menu_game1;
    SDL_Texture* Button_1;
    SDL_Texture* Button_2;
    SDL_Texture* Button_3;
    int selectedOption;    // 0: Start, 1: How To Play, 2: Exit
    static const int TOTAL_OPTIONS = 3;
    bool check_menu;       // Biến này xác định có chuyển sang game hay không

    void renderButton(SDL_Texture* buttonTexture, int x, int y, bool selected);
};

#endif // MENU_H
