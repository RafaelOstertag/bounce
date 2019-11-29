#include "ball.hh"
#include "outlinerenderer.hh"
#include "sdl.hh"
#include "solidrenderer.hh"
#include "text.hh"
#include "wall.hh"
#include "window.hh"

#include <algorithm>
#include <string>
#include <vector>

constexpr char fontfile[] = "../data/DejaVuSansMono-Bold.ttf";

const Color white{0xFF, 0xFF, 0xFF, 0x0};
const Color black{0x0, 0x0, 0x0, 0x0};
const Color textColor{0x70, 0x70, 0x70, 0x0};
const Color wallColor{0x70, 0x70, 0x70, 0x0};

const std::string textX{"X: "};
const std::string textY{"Y: "};
const std::string textVelocityX{"vX: "};
const std::string textVelocityY{"vY: "};

const Wall verticalWall{300, 100, 40, 200};
const Wall horizontalTopWall{220, 30, 200, 40};
const Wall horizontalBottomWall{220, 330, 200, 40};

BoundingBox ballBoundingBox{0, 0, 640, 400};
Ball ball{0, 0, 3, 5, ballBoundingBox};

SolidRenderer verticalWallRenderer{verticalWall, wallColor};
SolidRenderer horizontalTopWallRenderer{horizontalTopWall, wallColor};
SolidRenderer horizontalBottomWallRenderer{horizontalBottomWall, wallColor};
OutlineRenderer boundingBoxRenderer{ballBoundingBox, black};

std::vector<Renderable*> renderables;

int main(int argc, char* args[]) {
    if (!init_sdl()) {
        return 1;
    }
    atexit(quit_sdl);

    Window window("Bounce", 640, 480, white);
    Text labelX{fontfile, 18, 0, 405, textColor, textX};
    Text labelY{fontfile, 18, 100, 405, textColor, textY};
    Text labelVelocityX{fontfile, 18, 0, 435, textColor, textVelocityX};
    Text labelVelocityY{fontfile, 18, 100, 435, textColor, textVelocityY};

    ball.addWall(&verticalWall);
    ball.addWall(&horizontalTopWall);
    ball.addWall(&horizontalBottomWall);

    renderables.push_back(&ball);
    renderables.push_back(&labelX);
    renderables.push_back(&labelY);
    renderables.push_back(&labelVelocityX);
    renderables.push_back(&labelVelocityY);
    renderables.push_back(&boundingBoxRenderer);
    renderables.push_back(&verticalWallRenderer);
    renderables.push_back(&horizontalTopWallRenderer);
    renderables.push_back(&horizontalBottomWallRenderer);

    SDL_Event event;
    bool run{true};
    while (run) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                run = false;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_q:
                    run = false;
                    break;

                case SDLK_UP:
                    ball.increaseYVelocity();
                    break;

                case SDLK_DOWN:
                    ball.decreaseYVelocity();
                    break;

                case SDLK_LEFT:
                    ball.decreaseXVelocity();
                    break;

                case SDLK_RIGHT:
                    ball.increaseXVelocity();
                    break;
                }
            }
        }

        window.clear();
        ball.move();

        labelX.setText(textX + std::to_string(ball.x()));
        labelY.setText(textY + std::to_string(ball.y()));
        labelVelocityX.setText(textVelocityX +
                               std::to_string(ball.getVelocityX()));
        labelVelocityY.setText(textVelocityY +
                               std::to_string(ball.getVelocityY()));

        std::for_each(begin(renderables), end(renderables),
                      [&window](auto r) { window.render(*r); });

        window.update();
        SDL_Delay(16);
    }
}
