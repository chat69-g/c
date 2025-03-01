#include <iostream>
#include <vector>
#include <algorithm>
#include "igralec.h"
#include "arena.h"
#include "portal.h" // Include portal.h to access vAreni
#include "vrata.h"
#include "neprijatelji.h"

// Globalne spremenljivke
bool running = true;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
Arena arena = {0, 0, 800, 600, false, false, false, 0, 0}; // Initialize arena
Portal portal;
std::vector<Bullet> bullets;
std::vector<Enemy> enemies; // Vector za shranjevanje nasprotnikov
Bull bull; // Bull objekt
bool enemiesInitialized = false; // Flag to track if enemies and bull are initialized

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

// Preveri, ali so vsi nasprotniki mrtvi
bool allEnemiesDead() {
    for (const auto& enemy : enemies) {
        if (enemy.active) {
            return false; // Če je vsaj en nasprotnik aktiven, vrni false
        }
    }
    return true; // Vsi nasprotniki so mrtvi
}

// Posodobitev igre
void update(Uint32 deltaTime) {
    updatePlayer(&player, deltaTime);
    checkPortalCollision(&player, portal, SDL_GetTicks());

    // Inicializacija nasprotnikov in bika, ko igralec vstopi v areno
    if (vAreni && !enemiesInitialized) {
        for (int i = 0; i < 5; ++i) { // Dodaj 5 nasprotnikov
            Enemy enemy;
            initEnemy(enemy, rand() % 800, rand() % 600, 50.0f); // Naključne pozicije, hitrost = 50
            enemies.push_back(enemy);
        }
        initBull(bull, rand() % 800, rand() % 600, 30.0f); // Inicializacija bika na naključni poziciji
        enemiesInitialized = true; // Označi, da so nasprotniki in bik inicializirani
    }

    // Posodobi izstrelke
    for (auto& bullet : bullets) {
        updateBullet(bullet, deltaTime);
    }

    // Odstrani izstrelke, ki so zapustili zaslon ali zadeli nasprotnika
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [&](Bullet& bullet) {
        for (auto& enemy : enemies) {
            if (enemy.active && // Preveri, ali je nasprotnik aktiven
                bullet.x < enemy.x + enemy.size &&
                bullet.x + 5 > enemy.x &&
                bullet.y < enemy.y + enemy.size &&
                bullet.y + 5 > enemy.y) {
                enemy.active = false; // Deaktiviraj nasprotnika, če je zadel izstrelek
                return true; // Odstrani izstrelek
            }
        }
        return bullet.outOfBounds(800, 600); // Odstrani izstrelek, če je zunaj zaslona
    }), bullets.end());

    // Posodobi nasprotnike (samo, če je igralec v areni)
    if (vAreni) {
        for (auto& enemy : enemies) {
            if (enemy.active) { // Posodobi samo aktivne nasprotnike
                updateEnemy(enemy, player, deltaTime);

                // Preveri trk med igralcem in sovražnikom
                if (checkPlayerEnemyCollision(player, enemy)) {
                    running = false; // Konec igre, če se sovražnik dotakne igralca
                    std::cout << "Izgubil si! Sovražnik te je dotaknil." << std::endl;
                }
            }
        }

        // Posodobi bika (samo, če je igralec v areni)
        if (bull.active) {
            updateBull(bull, deltaTime);

            // Preveri trk igralca z bikov (samo, če je igralec v areni)
            if (bull.active &&
                player.x < bull.x + bull.size &&
                player.x + player.size > bull.x &&
                player.y < bull.y + bull.size &&
                player.y + player.size > bull.y) {
                if (allEnemiesDead()) {
                    // Rešitev bika (konec igre ali naslednji nivo)
                    running = false; // Za zdaj samo končamo igro
                    std::cout << "Bik rešen! Konec igre." << std::endl;
                } else {
                    // Igralec še ni ubil vseh nasprotnikov
                    std::cout << "Najprej ubij vse nasprotnike!" << std::endl;
                }
            }
        }
    }
}

// Risanje vseh elementov igre
void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (vAreni) {
        drawArena(renderer, arena); // Nariši areno samo, če je igralec znotraj
    }

    drawPortal(renderer, portal, SDL_GetTicks()); // Nariši portal
    drawPlayer(renderer, &player); // Nariši igralca

    // Nariši izstrelke
    for (const auto& bullet : bullets) {
        drawBullet(renderer, bullet);
    }

    // Nariši nasprotnike (samo, če je igralec v areni)
    if (vAreni) {
        for (const auto& enemy : enemies) {
            if (enemy.active) { // Nariši samo aktivne nasprotnike
                drawEnemy(renderer, enemy);
            }
        }

        // Nariši bika (samo, če je igralec v areni)
        if (bull.active) {
            drawBull(renderer, bull);
        }
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

    initPortal(portal, 400, 300); // Inicializacija portala

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