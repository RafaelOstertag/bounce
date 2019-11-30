#ifndef __TEXT_HH
#define __TEXT_HH

#include "color.hh"
#include "rectangle.hh"
#include "renderable.hh"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Text : public Renderable {
  public:
    Text(const std::string& ttfFilepath, int size, int x, int y,
         const Color& color, const std::string& text = std ::string{});
    Text(const Text&) = delete;
    Text& operator=(const Text&) = delete;

    Text(Text&& o);
    Text& operator=(Text&& o);

    virtual ~Text();

    void setText(const std::string& text);

    virtual void render(const Renderer& renderer);

  private:
    TTF_Font* font;
    SDL_Texture* texture;
    Color color;
    Rectangle textRectangle;
    std::string text;

    void freeTexture();
    void textToTexture(const Renderer& renderer);
};

#endif
