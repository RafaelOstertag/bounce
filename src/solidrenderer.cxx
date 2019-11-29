#include "solidrenderer.hh"

void SolidRenderer::render(const Renderer& renderer) {
    SDL_SetRenderDrawColor(renderer, color.red(), color.green(), color.blue(),
                           color.alpha());
    SDL_RenderFillRect(renderer, rectangle);
}
