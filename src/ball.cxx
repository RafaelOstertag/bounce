#include "ball.hh"

#include <stdexcept>
#include <string>

Ball::Ball(int startX, int startY, int velocityX, int velocityY,
           const BoundingBox& confinement)
    : surface{nullptr}, texture{nullptr}, ballBox{},
      confinement{confinement}, velocityX{velocityX}, velocityY{velocityY} {
    loadSurface("../data/ball.bmp");

    auto height = surface->clip_rect.h;
    auto width = surface->clip_rect.w;

    ballBox = Rectangle{startX, startY, width, height};
}

Ball::Ball(Ball&& o)
    : surface{o.surface}, texture{o.texture}, ballBox{o.ballBox},
      confinement{o.confinement}, velocityX{o.velocityX}, velocityY{
                                                              o.velocityY} {
    o.surface = nullptr;
    o.texture = nullptr;
}

Ball::~Ball() {
    if (surface) {
        SDL_FreeSurface(surface);
    }
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void Ball::render(const Renderer& renderer) {
    if (texture == nullptr) {
        convertSurfaceToTexture(renderer);
    }

    SDL_RenderCopy(renderer, texture, nullptr, ballBox);
}

void Ball::move() {
    ballBox.x(ballBox.x() + velocityX);
    ballBox.y(ballBox.y() + velocityY);

    if (confinement.collisionTop(ballBox)) {
        ballBox.y(confinement.y());
        velocityY *= -1;
    }

    if (confinement.collisionLeft(ballBox)) {
        ballBox.x(confinement.x());
        velocityX *= -1;
    }

    if (confinement.collisionBottom(ballBox)) {
        ballBox.y(confinement.y() + confinement.height() - ballBox.height());
        velocityY *= -1;
    }

    if (confinement.collisionRight(ballBox)) {
        ballBox.x(confinement.x() + confinement.width() - ballBox.width());
        velocityX *= -1;
    }
}

void Ball::increaseXVelocity() {
    if (velocityX > 0) {
        velocityX++;
    } else {
        velocityX--;
    }
}

void Ball::decreaseXVelocity() {
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
    if (velocityY > 0) {
        velocityY--;
    } else {
        velocityY++;
    }
}

void Ball::loadSurface(const std::string& filename) {
    surface = SDL_LoadBMP(filename.c_str());
    if (surface == nullptr) {
        throw std::invalid_argument("Cannot load file " + filename + ": " +
                                    SDL_GetError());
    }
}

void Ball::convertSurfaceToTexture(const Renderer& renderer) {
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        std::string errorMsg{"Unable to create texture: "};
        throw std::runtime_error(errorMsg + SDL_GetError());
    }

    SDL_FreeSurface(surface);
    surface = nullptr;
}
