#ifndef IGRALC_H
#define IGRALC_H

#include <SDL2/SDL.h>
#include <vector>

struct Player {
    float x, y;
    int size;
    float speed;
};

extern Player player; // Globalna spremenljivka za igralca

void initPlayer(Player* player, int x, int y);
void updatePlayer(Player* player, Uint32 deltaTime);
void drawPlayer(SDL_Renderer* renderer, Player* player);

struct Bullet {
    float x, y;
    float dx, dy;
    float speed;

    bool outOfBounds(int width, int height) const { // Preveri, ali je izstrelek zunaj zaslona
        return x < 0 || x > width || y < 0 || y > height;
    }
};

void shootBullet(std::vector<Bullet>& bullets, const Player& player, float targetX, float targetY);
void updateBullet(Bullet& bullet, Uint32 deltaTime);
void drawBullet(SDL_Renderer* renderer, const Bullet& bullet);

#endif