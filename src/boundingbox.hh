#ifndef __BOUNDINGBOX_HH
#define __BOUNDINGBOX_HH

#include "rectangle.hh"

class BoundingBox : public Rectangle {
  public:
    BoundingBox(int x, int y, int width, int height)
        : Rectangle{x, y, width, height} {}

    bool collisionTop(const Rectangle& rectangle) {
        return rectangle.y() <= y();
    };

    bool collisionLeft(const Rectangle& rectangle) {
        return rectangle.x() <= x();
    }

    bool collisionBottom(const Rectangle& rectangle) {
        return (rectangle.y() + rectangle.height()) >= (y() + height());
    }

    bool collisionRight(const Rectangle& rectangle) {
        return (rectangle.x() + rectangle.width()) >= (x() + width());
    }
};

#endif
