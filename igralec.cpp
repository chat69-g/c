#include "igralec.h"
#include <cmath>
#include "arena.h"

Player player = {50, 50, 20, 1.2};
const Uint8* keys = SDL_GetKeyboardState(NULL);

void initPlayer(Player* player, int startX, int startY) {
    player->x = startX;
    player->y = startY;
    player->size = 20;
    player->speed = 1.2;
}

void updatePlayer() {
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    float moveAmount = player.speed * 16; // 16 ms kot okvirno trajanje enega cikla

    if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP]) player.y -= moveAmount;
    if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN]) player.y += moveAmount;
    if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]) player.x -= moveAmount;
    if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) player.x += moveAmount;

    checkArenaCollision(player, arena);
}

void drawPlayer(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect = { static_cast<int>(round(player.x)), 
                      static_cast<int>(round(player.y)), 
                      player.size, player.size };
    SDL_RenderFillRect(renderer, &rect);
}

// Funkcija za izračun premika izstrelka glede na kot
void shootBullet(std::vector<Bullet>& bullets, const Player& player, float targetX, float targetY) {
    Bullet bullet;
    bullet.x = player.x + player.size / 2;
    bullet.y = player.y + player.size / 2;
    bullet.speed = 5.0f;

    float dx = targetX - bullet.x;
    float dy = targetY - bullet.y;
    float length = sqrt(dx * dx + dy * dy);
    
    bullet.dx = (dx / length) * bullet.speed;
    bullet.dy = (dy / length) * bullet.speed;

    bullets.push_back(bullet);
}

void updateBullet(Bullet& bullet, Uint32 deltaTime) {
    bullet.x += bullet.dx * (deltaTime / 16.0f);
    bullet.y += bullet.dy * (deltaTime / 16.0f);
}

void drawBullet(SDL_Renderer* renderer, const Bullet& bullet) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Rumeni izstrelek
    SDL_Rect rect = { static_cast<int>(bullet.x), static_cast<int>(bullet.y), 5, 5 };
    SDL_RenderFillRect(renderer, &rect);
}
