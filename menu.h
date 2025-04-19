// Menu.h
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Menu {
    private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    std::string playerName;
    int selectedOption = 0; // 0=Start, 1=Top Scores, 2=Exit
    bool gameStarted = false;
    bool showScores = false;

    public:
    Menu(SDL_Renderer* renderer);
    ~Menu();
    void Render();
    void HandleEvent(const SDL_Event& event);
    bool IsGameStarted() const;
    bool ShowTopScores() const;
    std::string GetPlayerName() const;


};