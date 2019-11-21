#include "renderer.hh"

Renderer::Renderer(SDL_Renderer* renderer) : sdlRenderer{renderer} {}

Renderer::~Renderer() {
    if (sdlRenderer) {
        SDL_DestroyRenderer(sdlRenderer);
    }
}

Renderer::Renderer(Renderer&& o) : sdlRenderer{o.sdlRenderer} {
    o.sdlRenderer = nullptr;
}

Renderer& Renderer::operator=(Renderer&& o) {
    sdlRenderer = o.sdlRenderer;
    o.sdlRenderer = nullptr;

    return *this;
}

Renderer::operator SDL_Renderer*() const { return sdlRenderer; }
