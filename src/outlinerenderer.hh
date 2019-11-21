#ifndef __OUTLINERENDERER_HH
#define __OUTLINERENDERER_HH

#include "color.hh"
#include "rectangle.hh"
#include "renderable.hh"

#include <SDL.h>

class OutlineRenderer : public Renderable {
  public:
    OutlineRenderer(const Rectangle& rectangle, const Color& color)
        : rectangle{rectangle}, color{color} {}
    virtual ~OutlineRenderer() {}

    virtual void render(const Renderer& renderer);

  private:
    const Rectangle& rectangle;
    const Color& color;
};

#endif
