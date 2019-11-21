#ifndef __RECTANGLE_HH
#define __RECTANGLE_HH

#include <SDL.h>

class Rectangle {
  public:
    Rectangle(int x = 0, int y = 0, int width = 0, int height = 0)
        : sdlRect{x, y, width, height} {}

    int x() const { return sdlRect.x; }
    int y() const { return sdlRect.y; }
    int width() const { return sdlRect.w; }
    int height() const { return sdlRect.h; }

    void x(int v) { sdlRect.x = v; }
    void y(int v) { sdlRect.y = v; }
    void width(int v) { sdlRect.w = v; }
    void height(int v) { sdlRect.h = v; }

    operator const SDL_Rect*() const { return &sdlRect; }

  private:
    SDL_Rect sdlRect;
};

#endif
