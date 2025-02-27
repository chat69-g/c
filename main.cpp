#include <SDL2/SDL.h>
#include "igralec.h"
#include "portal.h"
#include "arena.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
Player player = {50, 50, 20, 1.2}; // ✅ Prava definicija, samo tukaj!
Portal portal;
Arena arena;
bool vAreni = false;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;
    window = SDL_CreateWindow("Resevanje Bika", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) return false;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) return false;
    return true;
}

void handleEvents(bool &running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) running = false;
        handleInput();
    }
}

void update(Uint32 currentTime) {
    updatePlayer();
    updatePortal(portal, currentTime);
    checkPortalCollision(&player, portal, currentTime);
}

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (vAreni) {
        drawArena(renderer, arena);
    }

    if (portal.aktiven) {
        drawPortal(renderer, portal, SDL_GetTicks());
    }

    drawPlayer(renderer);
    SDL_RenderPresent(renderer);
}

void cleanup() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    if (!init()) return -1;
    
    arena.width = 800;
    arena.height = 600;
    
    player = {100, 100, 20, 1.2};
    initPortal(portal, 300, 300);

    bool running = true;
    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        handleEvents(running);
        update(currentTime);
        render();
        SDL_Delay(16);
    }

    cleanup();
    return 0;
}
