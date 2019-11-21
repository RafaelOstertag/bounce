#include "outlinerenderer.hh"

void OutlineRenderer::render(const Renderer& renderer) {
    SDL_SetRenderDrawColor(renderer, color.red(), color.green(), color.blue(),
                           color.alpha());
    SDL_RenderDrawRect(renderer, rectangle);
}
