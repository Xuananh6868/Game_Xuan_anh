#include "menu.h"
#include "SDLHelper.h"
#include <SDL.h>
#include <iostream>

menu::menu() : selectedOption(0), check_menu(false) {
    // Không gọi initSDL và createRenderer ở đây nữa
}

menu::~menu() {
    // Giải phóng texture nếu cần
    SDL_DestroyTexture(Button_1);
    SDL_DestroyTexture(Button_2);
    SDL_DestroyTexture(Button_3);
    SDL_DestroyTexture(menu_game);
}

void menu::initMenu() {
    // Gọi các hàm khởi tạo 1 lần khi vào menu

    menu_game = loadTexture("photo/Menu_Game.jpg");
    menu_game1 = loadTexture("photo/Guess.jpg");
    Button_1 = loadTexture("photo/Button_start.png");
    Button_2 = loadTexture("photo/Button_guess.png");
    Button_3 = loadTexture("photo/Button_Exit.png");
}

void menu::renderMenu() {
    // Xóa renderer, vẽ lại menu và các nút
    SDL_RenderClear(anh.renderer);
    SDL_Rect destRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(anh.renderer, menu_game, NULL, &destRect);
    renderButton(Button_1, 315, 200, selectedOption == 0);
    renderButton(Button_2, 330, 280, selectedOption == 1);
    renderButton(Button_3, 340, 350, selectedOption == 2);
    SDL_RenderPresent(anh.renderer);
}

void menu::renderButton(SDL_Texture* buttonTexture, int x, int y, bool selected) {
    renderTexture(buttonTexture, x, y);
    if (selected) {
        int w, h;
        SDL_QueryTexture(buttonTexture, NULL, NULL, &w, &h);
        SDL_Rect borderRect = { x, y, w, h };
        SDL_SetRenderDrawColor(anh.renderer, 255, 0, 0, 255); // Màu đỏ cho đường viền
        SDL_RenderDrawRect(anh.renderer, &borderRect);
    }
}

void menu::key_process() {
    SDL_Event e;
    bool done = false;
    bool showHowToPlay = false; // Cờ kiểm tra nếu đang hiển thị hướng dẫn

    while (!done) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                exit(0);
            }
            if (e.type == SDL_KEYDOWN) {
                if (showHowToPlay) {
                    // Nếu đang trong màn hình hướng dẫn, thoát về menu khi nhấn bất kỳ phím nào
                    showHowToPlay = false;
                } else {
                    switch(e.key.keysym.sym) {
                        case SDLK_UP:
                            selectedOption = (selectedOption - 1 + TOTAL_OPTIONS) % TOTAL_OPTIONS;
                            break;
                        case SDLK_DOWN:
                            selectedOption = (selectedOption + 1) % TOTAL_OPTIONS;
                            break;
                        case SDLK_RETURN:
                            if (selectedOption == 0) {
                                std::cout << "Start Game selected" << std::endl;
                                check_menu = true;
                                done = true; // Thoát menu để vào game
                            } else if (selectedOption == 1) {
                                std::cout << "How To Play selected" << std::endl;
                                showHowToPlay = true; // Hiển thị màn hình hướng dẫn
                            } else if (selectedOption == 2) {
                                std::cout << "Exit selected" << std::endl;
                                check_menu = false;
                                exit(0);
                            }
                            break;
                    }
                }
            }
        }

        // Hiển thị nội dung phù hợp
        SDL_RenderClear(anh.renderer);
        if (showHowToPlay) {
            SDL_Rect destRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
            SDL_RenderCopy(anh.renderer, menu_game1, NULL, &destRect);
        } else {
            renderMenu();
        }
        SDL_RenderPresent(anh.renderer);
        SDL_Delay(16);
    }
}

void menu::cleanup1(){
    if(menu_game) SDL_DestroyTexture(menu_game);
    if(Button_1)  SDL_DestroyTexture(Button_1);
    if(Button_2)  SDL_DestroyTexture(Button_2);
    if(Button_3)  SDL_DestroyTexture(Button_3);
}
