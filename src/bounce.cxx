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

int main(int argc, char* args[]) {
    if (!init_sdl()) {
        return 1;
    }
    atexit(quit_sdl);

    Color white{0xFF, 0xFF, 0xFF, 0x0};
    auto window = new Window("Bounce", 640, 480, white);

    BoundingBox ballBoundingBox{0, 0, 640, 400};
    Ball ball{0, 0, 3, 5, ballBoundingBox};

    Color black{0x0, 0x0, 0x0, 0x0};
    OutlineRenderer boundingBoxRenderer{ballBoundingBox, black};

    Color textColor{0x70, 0x70, 0x70, 0x0};

    std::string textX{"X: "};
    Text labelX{fontfile, 18, 0, 405, textColor, textX};

    std::string textY{"Y: "};
    Text labelY{fontfile, 18, 100, 405, textColor, textY};

    std::string textVelocityX{"vX: "};
    Text labelVelocityX{fontfile, 18, 0, 435, textColor, textVelocityX};

    std::string textVelocityY{"vY: "};
    Text labelVelocityY{fontfile, 18, 100, 435, textColor, textVelocityY};

    Wall verticalWall{300, 100, 40, 200};
    ball.addWall(&verticalWall);

    Wall horizontalTopWall{220, 60, 200, 40};
    ball.addWall(&horizontalTopWall);

    Wall horizontalBottomWall{220, 330, 200, 40};
    ball.addWall(&horizontalBottomWall);

    Color wallColor{0x70, 0x70, 0x70, 0x0};
    SolidRenderer verticalWallRenderer{verticalWall, wallColor};
    SolidRenderer horizontalTopWallRenderer{horizontalTopWall, wallColor};
    SolidRenderer horizontalBottomWallRenderer{horizontalBottomWall, wallColor};

    std::vector<Renderable*> renderables;
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
        window->clear();

        ball.move();
        labelX.setText(textX + std::to_string(ball.x()));
        labelY.setText(textY + std::to_string(ball.y()));
        labelVelocityX.setText(textVelocityX +
                               std::to_string(ball.getVelocityX()));
        labelVelocityY.setText(textVelocityY +
                               std::to_string(ball.getVelocityY()));

        std::for_each(begin(renderables), end(renderables),
                      [window](auto r) { window->render(*r); });

        window->update();
        SDL_Delay(16);
    }
    delete window;
}
