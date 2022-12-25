#include "collision.h"
#include <cmath>



inline int area (const QPoint &a, const QPoint &b, const QPoint &c) {
    return (b.x() - a.x()) * (c.y() - a.y()) - (b.y() - a.y()) * (c.x() - a.x());
}

inline bool intersect_1 (int a, int b, int c, int d) {
    if (a > b)  std::swap (a, b);
    if (c > d)  std::swap (c, d);
    return std::max(a,c) <= std::min(b,d);
}

// https://e-maxx.ru/algo/segments_intersection_checking
// return true if ab intresect cd
bool intersect (const QPoint &a, const QPoint &b, const QPoint &c, const QPoint &d) {
    return intersect_1 (a.x(), b.x(), c.x(), d.x())
        && intersect_1 (a.y(), b.y(), c.y(), d.y())
        && area(a,b,c) * area(a,b,d) <= 0
        && area(c,d,a) * area(c,d,b) <= 0;
}

auto CollisionFree(const QPoint &s, const QPoint &e, const std::vector<Triangle> &tr) -> bool {
    for (const auto &elem : tr) {
        if      (  intersect(s,e, elem.vertices[0], elem.vertices[1])
                || intersect(s,e, elem.vertices[1], elem.vertices[2])
                || intersect(s,e, elem.vertices[0], elem.vertices[2])) {
            return false;
        }
    }
    return true;
}

auto Steer(const QPoint& s, const QPoint &e, const std::vector<Triangle> &tr) -> QPoint {
    double step_x = static_cast<double>(e.x() - s.x()) / STICK_LEN;
    double step_y = static_cast<double>(e.y() - s.y()) / STICK_LEN;
    double cur_x = s.x(), cur_y = s.y();

    for (int i = 0; i < STICK_LEN; i++) {
        int x,y;
        if (CollisionFree(s, QPoint(std::round(cur_x + step_x), std::round(cur_y + step_y)), tr)) {
            cur_x += step_x;
            cur_y += step_y;
        } else {
            return QPoint(std::round(cur_x), std::round(cur_y));
        }
    }
    return e;
}
