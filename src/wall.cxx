#include "wall.hh"

bool Wall::collisionTop(const Line& line) const {
    Line wallLine{Point{double(x()), double(y())},
                 Point{double(xRight()), double(y())}};
    return intersect(wallLine, line);
}

bool Wall::collisionLeft(const Line& line) const {
    Line wallLine{Point{double(x()), double(y())},
                 Point{double(x()), double(yBottom())}};
    return intersect(wallLine, line);
}

bool Wall::collisionBottom(const Line& line) const {
    Line wallLine{Point{double(x()), double(yBottom())},
                 Point{double(xRight()), double(yBottom())}};
    return intersect(wallLine, line);
}

bool Wall::collisionRight(const Line& line) const {
    Line wallLine{Point{double(xRight()), double(y())},
                 Point{double(xRight()), double(yBottom())}};
    return intersect(wallLine, line);
}

bool Wall::collision(const Rectangle& rectangle) const {
    return ((rectangle.x() >= x() && rectangle.x() <= xRight()) ||
            (rectangle.xRight() >= x() && rectangle.xRight() <= x())) &&
           ((rectangle.y() >= y() && rectangle.y() <= yBottom()) ||
            (rectangle.yBottom() >= y() && rectangle.yBottom() <= yBottom()));
}
