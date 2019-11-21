#ifndef __BALL_HH
#define __BALL_HH

#include "boundingbox.hh"
#include "rectangle.hh"
#include "renderable.hh"

#include <SDL.h>
#include <string>

class Ball : public Renderable {
  public:
    Ball(int startX, int startY, int velocityX, int velocityY,
         const BoundingBox& confinement);
    Ball(const Ball&) = delete;
    Ball(Ball&& o);
    virtual ~Ball();

    virtual void render(const Renderer& renderer);
    void move();

    void increaseXVelocity();
    void decreaseXVelocity();
    void increaseYVelocity();
    void decreaseYVelocity();

    int getVelocityX() const { return velocityX; }
    int getVelocityY() const { return velocityY; }
    int getX() const { return ballBox.x(); }
    int getY() const { return ballBox.y(); }

  private:
    SDL_Surface* surface;
    SDL_Texture* texture;
    Rectangle ballBox;
    BoundingBox confinement;
    int velocityX;
    int velocityY;

    void loadSurface(const std::string& filename);
    void convertSurfaceToTexture(const Renderer& renderer);
};

#endif
