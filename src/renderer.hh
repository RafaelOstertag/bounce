#ifndef __RENDERER_HH
#define __RENDERER_HH

#include <SDL.h>

class Renderer {
  public:
    Renderer(SDL_Renderer* renderer = nullptr);
    ~Renderer();
    Renderer(const Renderer&) = delete;
    Renderer(Renderer&& o);
    Renderer& operator=(Renderer&& o);

    operator SDL_Renderer*() const;

  private:
    SDL_Renderer* sdlRenderer;
};

#endif
