#ifndef IGRALC_H
#define IGRALC_H

#include <SDL2/SDL.h>
#include <vector>

struct Player {
    float x, y;
    int size;
    float speed;
};

extern Player player;

void initPlayer(Player* player, int startX, int startY);
void updatePlayer();
void drawPlayer(SDL_Renderer* renderer);

struct Bullet {
    float x, y;
    float dx, dy;
    float speed;

    bool outOfBounds(int width, int height) const { // DODAN const
        return x < 0 || x > width || y < 0 || y > height;
    }
};

void shootBullet(std::vector<Bullet>& bullets, const Player& player, float targetX, float targetY);
void updateBullet(Bullet& bullet, Uint32 deltaTime);
void drawBullet(SDL_Renderer* renderer, const Bullet& bullet);

#endif
