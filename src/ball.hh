#ifndef __BALL_HH
#define __BALL_HH

#include "boundingbox.hh"
#include "rectangle.hh"
#include "renderable.hh"
#include "solidrenderer.hh"
#include "wall.hh"

#include <SDL.h>
#include <string>
#include <vector>

class Ball : public Rectangle, public Renderable {
  public:
    Ball(int startX, int startY, int velocityX, int velocityY,
         const BoundingBox& confinement);
    Ball(const Ball&) = delete;
    Ball(Ball&& o);
    virtual ~Ball() {}

    virtual void render(const Renderer& renderer);
    void addWall(const Wall* wall);
    void move();

    void increaseXVelocity();
    void decreaseXVelocity();
    void increaseYVelocity();
    void decreaseYVelocity();

    int getVelocityX() const { return velocityX; }
    int getVelocityY() const { return velocityY; }

  private:
    SolidRenderer solidRenderer;
    BoundingBox confinement;
    std::vector<const Wall*> walls;

    int velocityX;
    int velocityY;

    void detectAndHandleConfinementCollision();
    void detectAndHandleWallCollisions();
#ifndef NDEBUG
    void renderTail(const Renderer& renderer);
#endif
};

#endif
