#include "neprijatelji.h"
#include <cmath>

void initEnemy(Enemy& enemy, float x, float y, float speed) {
    enemy.x = x;
    enemy.y = y;
    enemy.size = 20; // Size of the enemy
    enemy.speed = speed;
    enemy.active = true;
}

void updateEnemy(Enemy& enemy, const Player& player, Uint32 deltaTime) {
    if (!enemy.active) return;

    // Calculate direction toward the player
    float dx = player.x - enemy.x;
    float dy = player.y - enemy.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    // Normalize direction
    if (distance > 0) {
        dx /= distance;
        dy /= distance;
    }

    // Move enemy toward the player
    enemy.x += dx * enemy.speed * (deltaTime / 1000.0f);
    enemy.y += dy * enemy.speed * (deltaTime / 1000.0f);
}

void drawEnemy(SDL_Renderer* renderer, const Enemy& enemy) {
    if (!enemy.active) return;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color for enemies
    SDL_Rect rect = { static_cast<int>(enemy.x), static_cast<int>(enemy.y), enemy.size, enemy.size };
    SDL_RenderFillRect(renderer, &rect);
}

bool checkPlayerEnemyCollision(const Player& player, const Enemy& enemy) {
    return (player.x < enemy.x + enemy.size &&
            player.x + player.size > enemy.x &&
            player.y < enemy.y + enemy.size &&
            player.y + player.size > enemy.y);
}

void initBull(Bull& bull, float x, float y, float speed) {
    bull.x = x;
    bull.y = y;
    bull.size = 30; // Size of the bull
    bull.speed = speed;
    bull.active = true;
}

void updateBull(Bull& bull, Uint32 deltaTime) {
    if (!bull.active) return;

    // Naključno premikanje bika
    bull.x += (rand() % 3 - 1) * bull.speed * (deltaTime / 1000.0f); // Premik levo/desno
    bull.y += (rand() % 3 - 1) * bull.speed * (deltaTime / 1000.0f); // Premik gor/dol

    // Prepreči, da bi bik zapustil areno
    if (bull.x < 0) bull.x = 0;
    if (bull.y < 0) bull.y = 0;
    if (bull.x + bull.size > 800) bull.x = 800 - bull.size;
    if (bull.y + bull.size > 600) bull.y = 600 - bull.size;
}

void drawBull(SDL_Renderer* renderer, const Bull& bull) {
    if (!bull.active) return;
    SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255); // Brown color for the bull
    SDL_Rect rect = { static_cast<int>(bull.x), static_cast<int>(bull.y), bull.size, bull.size };
    SDL_RenderFillRect(renderer, &rect);
}