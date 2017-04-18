#include <SDL2/SDL.h>
#include <stdio.h>
#include <vector>

Uint32 get_pixel32(SDL_Surface *surface, int x, int y) {
  Uint32 *pixels = (Uint32 *)surface->pixels;
  return pixels[(y * surface->w) + x];
}

void put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel) {
  Uint32 *pixels = (Uint32 *)surface->pixels;
  pixels[(y * surface->w) + x] = pixel;
}

class Floodfill {
private:
  SDL_Surface *sup;
  bool **usati;
  int altezzaMatrice;
  int larghezzaMatrice;
  Uint32 bordo;
  Uint32 fillcolor;
  void init(SDL_Surface *supe);
  void loop(int x, int y);
  void azzera();
  void cambiaMatrice();

public:
  Floodfill(SDL_Surface *supe);
  void cambiaSup(SDL_Surface *supe);
  void riempi(int x, int y, SDL_Color bordo, SDL_Color fillcolor);
  ~Floodfill();
};

Floodfill::Floodfill(SDL_Surface *supe) { this->init(supe); }
void Floodfill::cambiaSup(SDL_Surface *supe) { this->init(supe); }
Floodfill::~Floodfill() {}

void Floodfill::init(SDL_Surface *supe) {
  if (!supe) {
    return;
  }
  this->sup = supe;
  this->altezzaMatrice = this->sup->h;
  this->larghezzaMatrice = this->sup->w;
  this->cambiaMatrice();
}

void Floodfill::cambiaMatrice() {
  int rows = this->larghezzaMatrice;
  int cols = this->altezzaMatrice;
  if (this->usati == NULL) {
    for (int i = 0; i < rows; i++)
      free(this->usati[i]);
  }

  this->usati = (bool **)malloc(rows * sizeof(bool *));
  for (int i = 0; i < rows; i++)
    this->usati[i] = (bool *)malloc(cols * sizeof(bool));
  this->azzera();
}

void Floodfill::azzera() {
  for (int i = 0; i < this->larghezzaMatrice; i++) {
    for (int j = 0; j < this->altezzaMatrice; j++) {
      this->usati[i][j] = false;
    }
  }
}

void Floodfill::riempi(int x, int y, SDL_Color bordo, SDL_Color fillcolor) {
  // Converti il valore RGB in Uint32
  this->bordo = SDL_MapRGB(this->sup->format, bordo.r, bordo.g, bordo.b);
  this->fillcolor =
      SDL_MapRGB(this->sup->format, fillcolor.r, fillcolor.g, fillcolor.b);
  // crea e Azzera la matrice di backtrack
  this->azzera();
  this->loop(x, y);
}

void Floodfill::loop(int x, int y) {
  // Controlla se sei già passato su questo pixel
  if (this->usati[x][y]) {
    return;
  }
  // Attiva il flag su questo pixel
  this->usati[x][y] = true;
  // Disegna su questo pixel
  put_pixel32(this->sup, x, y, this->fillcolor);
  // Vai nei pixel attorno
  if (x > 0) {
    // Sinistra
    if (get_pixel32(this->sup, x - 1, y) != this->bordo) {

      this->loop(x - 1, y);
    }
  }
  if (x < this->larghezzaMatrice - 1) {
    // Destra
    if (get_pixel32(this->sup, x + 1, y) != this->bordo) {
      this->loop(x + 1, y);
    }
  }
  if (y > 0) {
    if (get_pixel32(this->sup, x, y - 1) != this->bordo) {
      this->loop(x, y - 1);
    }
  }
  if (y < this->altezzaMatrice - 1) {
    // Sotto
    if (get_pixel32(this->sup, x, y + 1) != this->bordo) {
      this->loop(x, y + 1);
    }
  }
}
