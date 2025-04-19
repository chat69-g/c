#ifndef NEPRIJATELJI_H
#define NEPRIJATELJI_H

#include <SDL2/SDL.h>
#include "igralec.h"

struct Enemy {
    float x, y;
    int size;
    float speed;
    bool active;
};

struct Bull {
    float x, y;
    int size;
    float speed;
    bool active;
};

void initEnemy(Enemy& enemy, float x, float y, float speed);
void updateEnemy(Enemy& enemy, const Player& player, Uint32 deltaTime);
void drawEnemy(SDL_Renderer* renderer, const Enemy& enemy);

void initBull(Bull& bull, float x, float y, float speed);
void updateBull(Bull& bull, Uint32 deltaTime);
void drawBull(SDL_Renderer* renderer, const Bull& bull);

bool checkPlayerEnemyCollision(const Player& player, const Enemy& enemy);
#endif