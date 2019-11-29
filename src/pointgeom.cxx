#include "pointgeom.hh"

#include <cassert>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace {
double calculateSlope(const Line& line) {
    auto x = line.p1.x - line.p2.x;
    assert(x < 0.0 || x > 0.0);

    auto y = line.p1.y - line.p2.y;

    return y / x;
}

bool isLineHorizontal(const Line& line) {
    return std::abs(line.p1.y - line.p2.y) <=
           std::numeric_limits<double>::epsilon();
}
bool isLineVertical(const Line& line) {
    return std::abs(line.p1.x - line.p2.x) <=
           std::numeric_limits<double>::epsilon();
}

Point intersectHorizontal(const Line& hLine, const Line& line) {
    auto slopeLine = calculateSlope(line);

    auto x = (hLine.p1.y + slopeLine * line.p1.x - line.p1.y) / slopeLine;
    auto y = slopeLine * (x - line.p1.x) + line.p1.y;

    return Point{x, y};
}

Point intersectVertical(const Line& vLine, const Line& line) {
    auto slopeLine = calculateSlope(line);

    auto y = slopeLine * (vLine.p1.x - line.p1.x) + line.p1.y;
    return Point{vLine.p1.x, y};
}

Point intersectBothVertical(const Line& line1, const Line& line2) {
    if (std::abs(line1.p1.x - line2.p1.x) >
        std::numeric_limits<double>::epsilon()) {
        // we can return an arbitrary point, it can't be on both lines
        return line1.p1;
    }

    if ((line1.p1.y <= line2.p1.y && line2.p1.y <= line1.p2.y) ||
        (line1.p2.y <= line2.p1.y && line2.p1.y <= line1.p1.y)) {
        return line2.p1;
    }

    if ((line1.p1.y <= line2.p2.y && line2.p2.y <= line1.p2.y) ||
        (line1.p2.y <= line2.p2.y && line2.p2.y <= line1.p1.y)) {
        return line2.p2;
    }

    // we can return an arbitrary point, it can't be on both lines
    return line1.p1;
}

Point intersectBothHorizontal(const Line& line1, const Line& line2) {
    if (std::abs(line1.p1.y - line2.p1.y) >
        std::numeric_limits<double>::epsilon()) {
        // we can return an arbitrary point, it can't be on both lines
        return line1.p1;
    }

    if ((line1.p1.x <= line2.p1.x && line2.p1.x <= line1.p2.x) ||
        (line1.p2.x <= line2.p1.x && line2.p1.x <= line1.p1.x)) {
        return line2.p1;
    }

    if ((line1.p1.x <= line2.p2.x && line2.p2.x <= line1.p2.x) ||
        (line1.p2.x <= line2.p2.x && line2.p2.x <= line1.p1.x)) {
        return line2.p2;
    }

    // we can return an arbitrary point, it can't be on both lines
    return line1.p1;
}

bool isPointOnLine(const Point& point, const Line& line) {
    // The input line consists of integer coordinates, so we round the computed
    // coordinates of point
    auto pointX = std::round(point.x);
    auto pointY = std::round(point.y);
    return ((line.p1.x <= pointX && pointX <= line.p2.x) ||
            (line.p2.x <= pointX && pointX <= line.p1.x)) &&
           ((line.p1.y <= pointY && pointY <= line.p2.y) ||
            (line.p2.y <= pointY && pointY <= line.p1.y));
}

bool isPointOnBothLines(const Point& point, const Line& line1,
                        const Line& line2) {
    return isPointOnLine(point, line1) && isPointOnLine(point, line2);
}

} // namespace

bool intersect(const Line& line1, const Line& line2) {
    if (isLineVertical(line1) && isLineVertical(line2)) {
        auto point = intersectBothVertical(line1, line2);
        return isPointOnBothLines(point, line1, line2);
    }

    if (isLineHorizontal(line1) && isLineHorizontal(line2)) {
        auto point = intersectBothHorizontal(line1, line2);
        return isPointOnBothLines(point, line1, line2);
    }

    if (isLineHorizontal(line1)) {
        auto point = intersectHorizontal(line1, line2);
        return isPointOnBothLines(point, line1, line2);
    }

    if (isLineHorizontal(line2)) {
        auto point = intersectHorizontal(line2, line1);
        return isPointOnBothLines(point, line1, line2);
    }

    if (isLineVertical(line1)) {
        auto point = intersectVertical(line1, line2);
        return isPointOnBothLines(point, line1, line2);
    }

    if (isLineVertical(line2)) {
        auto point = intersectVertical(line2, line1);
        return isPointOnBothLines(point, line1, line2);
    }

    throw std::invalid_argument(
        "One line must be either horizontal or vertical");
}
