#include "igralec.h"  // Vključimo naš header file, ki vsebuje deklaracije za igralca
#include <SDL2/SDL.h>  // Vključimo SDL knjižnico za grafiko in vhodne dogodke
#include <cmath>  // Potrebno za funkcijo round()
#include "arena.h" 

extern Player player;
// Definiramo igralca s začetnimi vrednostmi:
// x = 50, y = 50 (začetna pozicija)
// size = 20 (velikost kvadrata)
// speed = 2 (hitrost premikanja)



// Spremenljivka za shranjevanje stanja tipkovnice
const Uint8* keys = SDL_GetKeyboardState(NULL);

// Funkcija za obdelavo vhodnih dogodkov (npr. tipkovnice)
void handleInput() {
    SDL_PumpEvents();  // Osveži stanje vhodnih naprav (npr. tipkovnice in miške)
}

// Funkcija za posodobitev položaja igralca glede na pritiskane tipke
void updatePlayer() {
    static Uint32 lastTime = SDL_GetTicks();
    Uint32 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;

    const Uint8* keys = SDL_GetKeyboardState(NULL);
    float moveAmount = player.speed * deltaTime * 100;

    if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP]) player.y -= moveAmount;
    if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN]) player.y += moveAmount;
    if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]) player.x -= moveAmount;
    if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) player.x += moveAmount;

    checkArenaCollision(player, arena);  // Preveri, če je igralec zadel steno
}


// Funkcija za risanje igralca na zaslon
void drawPlayer(SDL_Renderer* renderer) {
    // Nastavimo barvo risanja (rdeča: 255, 0, 0, popolnoma neprosojna: 255)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    
    // Ustvarimo pravokotnik na podlagi igralčevih koordinat in velikosti
    SDL_Rect rect = { static_cast<int>(round(player.x)), 
        static_cast<int>(round(player.y)), 
        player.size, 
        player.size };
    
    // Narišemo napolnjen pravokotnik (kvadrat) na zaslon
    SDL_RenderFillRect(renderer, &rect);
}
