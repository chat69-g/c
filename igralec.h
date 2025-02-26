#ifndef IGRALEC_H   // Preprečuje večkratno vključitev datoteke (include guard)
#define IGRALEC_H

#include <SDL2/SDL.h>  // Vključimo knjižnico SDL2, ki omogoča grafiko in vnos uporabnika

// Struktura, ki predstavlja igralca
struct Player {
    float x, y;    // Koordinate igralca na zaslonu
    int size;    // Velikost igralca
    float speed;   // Hitrost premikanja igralca
};

// Deklaracija globalne spremenljivke igralca (definicija bo v .cpp datoteki)
extern Player player;
extern bool vAreni;

// Funkcija za obdelavo vnosa uporabnika (premikanje igralca)
void handleInput();

// Funkcija za posodabljanje igralčevih podatkov (npr. premik)
void updatePlayer();

// Funkcija za risanje igralca na zaslon z uporabo SDL_Renderer-ja
void drawPlayer(SDL_Renderer* renderer);

#endif  // Konec zaščitnega makra
