// Menu.cpp
#include "Menu.h"
#include <iostream>

Menu::Menu(SDL_Renderer* renderer) : renderer(renderer) {
    font = TTF_OpenFont("assets/font.ttf", 24);
    if (!font) std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
}

Menu::~Menu() {
    TTF_CloseFont(font);
}

void Menu::Render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render title
    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface* titleSurface = TTF_RenderText_Solid(font, "My Game", white);
    SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
    SDL_Rect titleRect = {100, 50, 200, 50};
    SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
    SDL_FreeSurface(titleSurface);
    SDL_DestroyTexture(titleTexture);

    // Render options
    const char* options[] = {"Start Game", "Top Scores", "Exit"};
    for (int i = 0; i < 3; i++) {
        SDL_Color color = (i == selectedOption) ? (SDL_Color){255, 0, 0, 255} : white;
        SDL_Surface* optionSurface = TTF_RenderText_Solid(font, options[i], color);
        SDL_Texture* optionTexture = SDL_CreateTextureFromSurface(renderer, optionSurface);
        SDL_Rect optionRect = {100, 150 + i * 50, 200, 30};
        SDL_RenderCopy(renderer, optionTexture, NULL, &optionRect);
        SDL_FreeSurface(optionSurface);
        SDL_DestroyTexture(optionTexture);
    }

    SDL_RenderPresent(renderer);
}

void Menu::HandleEvent(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP: selectedOption = (selectedOption - 1 + 3) % 3; break;
            case SDLK_DOWN: selectedOption = (selectedOption + 1) % 3; break;
            case SDLK_RETURN:
                if (selectedOption == 0) gameStarted = true;
                else if (selectedOption == 1) showScores = true;
                break;
        }
    }
}

bool Menu::IsGameStarted() const { return gameStarted; }
bool Menu::ShowTopScores() const { return showScores; }
std::string Menu::GetPlayerName() const { return playerName; }