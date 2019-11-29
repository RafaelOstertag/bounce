#ifndef __WALL_H
#define __WALL_H

#include "pointgeom.hh"
#include "rectangle.hh"

class Wall : public Rectangle {
  public:
    Wall(int x, int y, int width, int height)
        : Rectangle{x, y, width, height} {}
    ~Wall() {}

    bool collisionTop(const Line& line) const;

    bool collisionLeft(const Line& line) const;

    bool collisionBottom(const Line& line) const;

    bool collisionRight(const Line& line) const;

    bool collision(const Rectangle& rectangle) const;
};

#endif
