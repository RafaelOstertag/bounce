#ifndef __WINDOW_HH
#define __WINDOW_HH

#include "color.hh"
#include "renderable.hh"
#include "renderer.hh"

#include <SDL.h>
#include <string>

class Window {
  public:
    Window(const std::string& name, int height, int width,
           const Color& bgColor);
    ~Window();
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    Window(Window&& o);
    Window& operator=(Window&&) = delete;

    void clear();
    void render(Renderable& renderable) const;
    void update() const;

  private:
    SDL_Window* sdlWindow;
    Renderer renderer;
    const Color& bgColor;
};

#endif
