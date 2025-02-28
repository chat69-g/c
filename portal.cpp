#include "portal.h"
#include <SDL2/SDL.h>
#include "arena.h"
extern Arena arena;
bool vAreni = false; 
void initPortal(Portal &portal, int x, int y) {
    portal.x = x;
    portal.y = y;
    portal.size = 30;
    portal.aktiven = true; // Portal je na začetku vklopljen
}

void updatePortal(Portal &portal, Uint32 currentTime) {
    // Lahko dodamo utripanje portala ali animacijo tukaj
}

// Preveri, ali igralec vstopi v portal
void checkPortalCollision(Player* player, Portal &portal, Uint32 currentTime) {
    if (!portal.aktiven) return;

    if (player->x < portal.x + portal.size &&
        player->x + player->size > portal.x &&
        player->y < portal.y + portal.size &&
        player->y + player->size > portal.y) {
        
        vAreni = true;
        portal.aktiven = false; // Portal izgine po uporabi
    }
}

void drawArena(SDL_Renderer* renderer) {
    // Črna podlaga arene
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect arenaRect = { arena.x, arena.y, arena.width, arena.height };
    SDL_RenderFillRect(renderer, &arenaRect);

    // Bele stene arene
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect topWall = { arena.x, arena.y, arena.width, 10 };
    SDL_Rect bottomWall = { arena.x, arena.y + arena.height - 10, arena.width, 10 };
    SDL_Rect leftWall = { arena.x, arena.y, 10, arena.height };
    SDL_Rect rightWall = { arena.x + arena.width - 10, arena.y, 10, arena.height };
    
    SDL_RenderFillRect(renderer, &topWall);
    SDL_RenderFillRect(renderer, &bottomWall);
    SDL_RenderFillRect(renderer, &leftWall);
    SDL_RenderFillRect(renderer, &rightWall);
}

// Nariše portal, samo če je aktiven
void drawPortal(SDL_Renderer* renderer, const Portal& portal, Uint32 currentTime) {
    if (!portal.aktiven) return; // Če ni aktiven, ga ne rišemo

    int centerX = static_cast<int>(portal.x);
    int centerY = static_cast<int>(portal.y);
    int radius = portal.size / 2;

    // **Utripajoča vijolična notranjost**
    int pulse = (SDL_GetTicks() / 100) % 256; // Spreminja vrednost od 0 do 255
    SDL_SetRenderDrawColor(renderer, 128, 0, 128, pulse); // Vijolična z utripanjem
    for (int w = 0; w < radius - 2; w++) { // Narišemo manjši krog z vijolično
        for (int h = 0; h < radius - 2; h++) {
            if (w * w + h * h <= (radius - 2) * (radius - 2)) {
                SDL_RenderDrawPoint(renderer, centerX + w, centerY + h);
                SDL_RenderDrawPoint(renderer, centerX - w, centerY + h);
                SDL_RenderDrawPoint(renderer, centerX + w, centerY - h);
                SDL_RenderDrawPoint(renderer, centerX - w, centerY - h);
            }
        }
    }

    // **Bela obroba**
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int w = 0; w < radius; w++) {
        for (int h = 0; h < radius; h++) {
            if (w * w + h * h >= (radius - 2) * (radius - 2) && w * w + h * h <= radius * radius) {
                SDL_RenderDrawPoint(renderer, centerX + w, centerY + h);
                SDL_RenderDrawPoint(renderer, centerX - w, centerY + h);
                SDL_RenderDrawPoint(renderer, centerX + w, centerY - h);
                SDL_RenderDrawPoint(renderer, centerX - w, centerY - h);
            }
        }
    }
}


void teleportPlayer(Player &player) {
    player.x = 400;
    player.y = 300;
}

void renderGame(SDL_Renderer* renderer, Player* player, Portal &portal, Uint32 currentTime) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);
    
    if (vAreni) {
        drawArena(renderer);
    }
    
    drawPortal(renderer, portal, currentTime);
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_Rect playerRect = { static_cast<int>(player->x), static_cast<int>(player->y), player->size, player->size };
    SDL_RenderFillRect(renderer, &playerRect);
    
    SDL_RenderPresent(renderer);
}