#include <iostream>
#include <vector>
#include <algorithm>
#include "igralec.h"
#include "arena.h"
#include "portal.h" // Include portal.h to access vAreni
#include "vrata.h"

// Globalne spremenljivke
bool running = true;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
Arena arena = {0, 0, 800, 600, false, false, false, 0, 0}; // Initialize arena
Portal portal;
std::vector<Bullet> bullets;

// Funkcija za obdelavo dogodkov (tipkovnica + miška)
void handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        } else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                running = false;
            }
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                float targetX = event.button.x;
                float targetY = event.button.y;
                shootBullet(bullets, player, targetX, targetY);
            }
        }
    }
}

// Posodobitev igre
void update(Uint32 deltaTime) {
    updatePlayer(&player, deltaTime);
    checkPortalCollision(&player, portal, SDL_GetTicks());

    // Posodobi izstrelke
    for (auto& bullet : bullets) {
        updateBullet(bullet, deltaTime);
    }

    // Odstrani izstrelke, ki so zapustili zaslon
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [](const Bullet& b) { return b.outOfBounds(800, 600); }), bullets.end());
}

// Risanje vseh elementov igre
void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (vAreni) {
        drawArena(renderer, arena); // Draw arena only if player is inside
    }

    drawPortal(renderer, portal, SDL_GetTicks()); // Always draw the portal
    drawPlayer(renderer, &player); // Always draw the player

    for (const auto& bullet : bullets) {
        drawBullet(renderer, bullet);
    }

    SDL_RenderPresent(renderer);
}

// Glavna zanka igre
int SDL_main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;

    window = SDL_CreateWindow("Igra", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) return 1;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) return 1;

    initPortal(portal, 400, 300); // Initialize portal inside the arena

    Uint32 lastTime = SDL_GetTicks();
    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        Uint32 deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        handleEvents();
        update(deltaTime);
        render();

        SDL_Delay(16); // Omejitev FPS na približno 60
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}