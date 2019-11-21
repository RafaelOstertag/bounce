#ifndef __RENDERABLE_HH
#define __RENDERABLE_HH

#include "renderer.hh"

class Renderable {
    public:
      virtual void render(const Renderer& renderer) = 0;
};

#endif
