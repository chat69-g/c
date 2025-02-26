#include "igralec.h"  // Vključimo naš header file, ki vsebuje deklaracije igralca in funkcij
#include <SDL2/SDL.h>  // Vključimo SDL knjižnico za grafiko in dogodke
#include "portal.h"  // Vključimo naš header file, ki vsebuje deklaracije portala in funkcij
#include "vrata.h"   // Vključimo header file za vrata
#include "arena.h"

Vrata vrata;


int main(int argc, char* argv[]) {
    // Inicializiramo SDL za uporabo grafike (video)
    SDL_Init(SDL_INIT_VIDEO);

    // Ustvarimo okno s širino 800 in višino 600, ki bo prikazano na sredini zaslona
    SDL_Window* window = SDL_CreateWindow(
        "2D Movement",                    
        SDL_WINDOWPOS_CENTERED,           
        SDL_WINDOWPOS_CENTERED,           
        800,                              
        600,                              
        SDL_WINDOW_SHOWN                  
    );

    // Ustvarimo SDL renderer za risanje v okno
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, 
        -1,                   
        SDL_RENDERER_ACCELERATED 
    );

    bool running = true;  
    SDL_Event event;      

    Portal portal;
    initPortal(portal, 200, 200); // Postavimo portal na neko začetno lokacijo
    initArena(arena, 100, 100, 300, 200);
    initVrata(vrata, 400, 300);

    while (running) {  
        Uint32 currentTime = SDL_GetTicks(); 
    
        // 1️⃣ DOGODKI (zapiranje okna)
        while (SDL_PollEvent(&event)) {  
            if (event.type == SDL_QUIT) running = false;  
        }
    
        // 2️⃣ POSODOBIMO IGRO
        handleInput();  
        updatePlayer();  
        updatePortal(portal, currentTime);  
        checkPortalCollision(&player, portal, currentTime); 
        updateVrata(vrata, currentTime, arena);
    
        // 3️⃣ POČISTIMO ZASLON
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  
        SDL_RenderClear(renderer);  
    
        // 4️⃣ NARIŠEMO ELEMENTE
        drawPlayer(renderer);  
        drawPortal(renderer, portal, currentTime);  
        drawVrata(renderer, vrata, currentTime);
        if (vAreni) {
            drawArena(renderer, arena);  // Arena se nariše samo, če je igralec notri
        }
        // 5️⃣ PRIKAŽEMO OKVIR (SAMO ENKRAT!)
        SDL_RenderPresent(renderer);  
    
        // 6️⃣ ČASOVNA ZAKASNITEV
        SDL_Delay(16); // 60 FPS
    }
    
    // Po koncu programa sprostimo pomnilnik in zapremo SDL
    SDL_DestroyRenderer(renderer); 
    SDL_DestroyWindow(window);     
    SDL_Quit();                    

    return 0;  
}
