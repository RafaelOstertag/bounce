#include "ball.hh"

#include <stdexcept>
#include <string>
#ifndef NDEBUG
#include <iostream>
#endif

#ifndef NDEBUG
#define DEBUG_OUT(x) std::cout << x << std::endl
#else
#define DEBUG_OUT(x) ((void)0)
#endif

Ball::Ball(int startX, int startY, int velocityX, int velocityY,
           const BoundingBox& confinement)
    : Rectangle{startX, startY, 20, 20}, color{}, solidRenderer{*this, color},
      confinement{confinement}, walls{}, velocityX{velocityX}, velocityY{
                                                                   velocityY} {}

Ball::Ball(Ball&& o)
    : Rectangle{std::move(o)}, color{o.color}, solidRenderer{std::move(
                                                   o.solidRenderer)},
      confinement{std::move(o.confinement)}, walls{std::move(o.walls)} {}

void Ball::addWall(const Wall* wall) { walls.push_back(wall); }

void Ball::render(const Renderer& renderer) {
    solidRenderer.render(renderer);
#ifndef NDEBUG
    renderTail(renderer);
#endif
}

void Ball::move() {
    x(x() + velocityX);
    y(y() + velocityY);

    detectAndHandleConfinementCollision();
    detectAndHandleWallCollisions();
}

void Ball::increaseXVelocity() {
    if (velocityX > 0) {
        velocityX++;
    } else {
        velocityX--;
    }
}

void Ball::decreaseXVelocity() {
    if (velocityX == -1 || velocityX == 1)
        return;

    if (velocityX > 0) {
        velocityX--;
    } else {
        velocityX++;
    }
}

void Ball::increaseYVelocity() {
    if (velocityY > 0) {
        velocityY++;
    } else {
        velocityY--;
    }
}

void Ball::decreaseYVelocity() {
    if (velocityY == -1 || velocityX == 1)
        return;
    if (velocityY > 0) {
        velocityY--;
    } else {
        velocityY++;
    }
}

void Ball::detectAndHandleConfinementCollision() {
    if (confinement.collisionTop(*this)) {
        y(confinement.y());
        velocityY *= -1;
    }

    if (confinement.collisionLeft(*this)) {
        x(confinement.x());
        velocityX *= -1;
    }

    if (confinement.collisionBottom(*this)) {
        y(confinement.y() + confinement.height() - height());
        velocityY *= -1;
    }

    if (confinement.collisionRight(*this)) {
        x(confinement.x() + confinement.width() - width());
        velocityX *= -1;
    }
}

void Ball::detectAndHandleWallCollisions() {
    auto newX = x();
    auto newVelocityX = velocityX;

    auto newY = y();
    auto newVelocityY = velocityY;

    for (auto wall : walls) {
        Line collisionLine1{
            Point{double(x()), double(yBottom())},
            Point{double(x() - velocityX), double(yBottom() - velocityY)}};
        Line collisionLine2 = Line{
            Point{double(xRight()), double(yBottom())},
            Point{double(xRight() - velocityX), double(yBottom() - velocityY)}};
        if ((wall->collisionTop(collisionLine1) ||
             wall->collisionTop(collisionLine2)) &&
            velocityY > 0) {
            DEBUG_OUT("Wall collision top");
            newY = wall->y() - height();
            newVelocityY *= -1;
        }

        collisionLine1 =
            Line{Point{double(xRight()), double(y())},
                 Point{double(xRight() - velocityX), double(y() - velocityY)}};
        collisionLine2 = Line{
            Point{double(xRight()), double(yBottom())},
            Point{double(xRight() - velocityX), double(yBottom() - velocityY)}};
        if ((wall->collisionLeft(collisionLine1) ||
             wall->collisionLeft(collisionLine2)) &&
            velocityX > 0) {
            DEBUG_OUT("Wall collision left");
            newX = wall->x() - width();
            newVelocityX *= -1;
        }

        collisionLine1 =
            Line{Point{double(x()), double(y())},
                 Point{double(x() - velocityX), double(y() - velocityY)}};
        collisionLine2 =
            Line{Point{double(xRight()), double(y())},
                 Point{double(xRight() - velocityX), double(y() - velocityY)}};
        if ((wall->collisionBottom(collisionLine1) ||
             wall->collisionBottom(collisionLine2)) &&
            velocityY < 0) {
            DEBUG_OUT("Wall collision bottom");
            newY = wall->yBottom();
            newVelocityY *= -1;
        }

        collisionLine1 =
            Line{Point{double(x()), double(y())},
                 Point{double(x() - velocityX), double(y() - velocityY)}};
        collisionLine2 =
            Line{Point{double(x()), double(yBottom())},
                 Point{double(x() - velocityX), double(yBottom() - velocityY)}};
        if ((wall->collisionRight(collisionLine1) ||
             wall->collisionRight(collisionLine2)) &&
            velocityX < 0) {
            DEBUG_OUT("Wall collision right");
            newX = wall->xRight();
            newVelocityX *= -1;
        }
    }
    x(newX);
    y(newY);
    velocityX = newVelocityX;
    velocityY = newVelocityY;
}

#ifndef NDEBUG
void Ball::renderTail(const Renderer& renderer) {
    SDL_RenderDrawLine(renderer, x(), y(), x() - velocityX, y() - velocityY);
    SDL_RenderDrawLine(renderer, xRight(), y(), xRight() - velocityX,
                       y() - velocityY);
    SDL_RenderDrawLine(renderer, x(), yBottom(), x() - velocityX,
                       yBottom() - velocityY);
    SDL_RenderDrawLine(renderer, xRight(), yBottom(), xRight() - velocityX,
                       yBottom() - velocityY);
}
#endif
