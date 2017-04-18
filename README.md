# SDL2-Floodfill-cpp
Floodfill class implementation on SDL2 written in c++.

# What you need
You need to install SDL2, a C open source library.

# How to use
After including floodfill.cpp in your main file and project, you need to create a Floodfill object giving the surface by parameter.
Then simply call riempi(int x, int y, SDL_Color bordo, SDL_Color fillcolor), where:
- x and y stand for the starting coordinate
- bordo stands for the RGB color where the floodfill stops
- fillcolor stands for the RGB color which is filled in the area

You may want to change the surface by using cambiaSup(SDL_Surface *supe), where:
- supe stands for the new surface

The class will do anything needed.
# Example
There is included an example main.cpp file, which simply creates a window and fills a triangle.
To compile, at least on Linux, you can simply type:
```
make release
make run
```
Or to compile and immediatly run:
```
make all
```
