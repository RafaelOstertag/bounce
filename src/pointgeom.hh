#ifndef __POINTGEOM_HH
#define __POINTGEOM_HH

#include <limits>

struct Point {
    double x;
    double y;
};

struct Line {
    Point p1;
    Point p2;
};

bool intersect(const Line& line1, const Line& line2);

#endif
