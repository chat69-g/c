#ifndef PORTAL_H
#define PORTAL_H

#include <SDL2/SDL.h>
#include "igralec.h"

struct Portal {
    int x, y;
    int size;
    bool active;
    Uint32 activationTime;
    Uint32 lastSpawnTime; 
    Uint32 timer;        
};

void initPortal(Portal &portal, int x, int y);
void updatePortal(Portal &portal, Uint32 currentTime);
void checkPortalCollision(Player* player, Portal &portal, Uint32 currentTime);
void drawPortal(SDL_Renderer* renderer, Portal &portal, Uint32 currentTime);
void teleportPlayer(Player &player);
#endif
