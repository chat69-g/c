#include "portal.h"
#include <SDL2/SDL.h>
#include "arena.h"
extern Arena arena;

void initPortal(Portal &portal, int x, int y) {
    portal.x = x;
    portal.y = y;
    portal.size = 50;
    portal.active = true;
    portal.activationTime = 0;
    portal.lastSpawnTime = 0;
    portal.timer = 0;
}

void updatePortal(Portal &portal, Uint32 currentTime) {
    if (!portal.active && (currentTime - portal.lastSpawnTime > 5000)) {
        portal.active = true;
        portal.lastSpawnTime = currentTime;
        portal.timer = currentTime;
    }
}

void checkPortalCollision(Player* player, Portal &portal, Uint32 currentTime) {
    if (!portal.active) return;

    SDL_Rect playerRect = { static_cast<int>(player->x), static_cast<int>(player->y), player->size, player->size };
    SDL_Rect portalRect = { portal.x, portal.y, portal.size, portal.size };

    if (SDL_HasIntersection(&playerRect, &portalRect)) {
        vAreni = true;
        player->x = 400;  // Postavi igralca na sredino arene
        player->y = 300;
        
        // Nastavi areno s črnim ozadjem in belimi stenami
        arena.x = 100;
        arena.y = 100;
        arena.width = 600;
        arena.height = 400;
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

void drawPortal(SDL_Renderer* renderer, Portal &portal, Uint32 currentTime) {
    if (!portal.active) return;

    int alpha = ((currentTime - portal.timer) / 300 % 2) ? 255 : 100;

    SDL_SetRenderDrawColor(renderer, 150, 0, 255, 255);
    SDL_Rect rect = { portal.x, portal.y, portal.size, portal.size };
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, alpha);
    SDL_RenderDrawRect(renderer, &rect);
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
