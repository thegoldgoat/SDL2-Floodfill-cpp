// Esempio di come usare la classe Floodfill

#include "floodfill.cpp"
#include <SDL2/SDL.h>

int main(int argc, char const *argv[]) {
  SDL_Window *finestra =
      SDL_CreateWindow("Flood-Fill", 10, 10, 300, 300, SDL_WINDOW_SHOWN);
  SDL_Surface *supFinestra = SDL_GetWindowSurface(finestra);
  SDL_Renderer *rend = SDL_CreateSoftwareRenderer(supFinestra);
  SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
  if (!finestra || !supFinestra || !rend) {
    return 1;
  }
  // Sfondo nero
  SDL_FillRect(supFinestra, NULL, 0);
  SDL_RenderDrawLine(rend, 10, 10, 200, 200);
  SDL_RenderDrawLine(rend, 10, 10, 200, 10);
  SDL_RenderDrawLine(rend, 200, 10, 200, 200);
  Uint32 prima = SDL_GetTicks();
  Floodfill principale(supFinestra);
  for (Uint8 i = 0; i < 255; i++) {
    principale.riempi(17, 16, {255, 255, 255}, {i, 0, 0});
    SDL_UpdateWindowSurface(finestra);
  }
  printf("Tempo in ms=%u\n", (SDL_GetTicks() - prima));

  SDL_UpdateWindowSurface(finestra);
  return 0;
}
