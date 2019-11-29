#ifndef __SOLIDRENDERER_HH
#define __SOLIDRENDERER_HH

#include "color.hh"
#include "rectangle.hh"
#include "renderable.hh"

#include <SDL.h>

class SolidRenderer : public Renderable {
  public:
    SolidRenderer(const Rectangle& rectangle, const Color& color)
        : rectangle{rectangle}, color{color} {}
    virtual ~SolidRenderer() {}

    virtual void render(const Renderer& renderer);

  private:
    const Rectangle& rectangle;
    const Color& color;
};

#endif
