#ifndef COLLISION_H
#define COLLISION_H
#include <QPoint>
#include <vector>

const int STICK_LEN = 20;

struct Triangle {
    Triangle() = delete;
    Triangle(const QPoint &p1,const QPoint &p2, const QPoint &p3) {
        vertices[0] = p1;
        vertices[1] = p2;
        vertices[2] = p3;
    }
    auto IsPoint() -> bool {
        return vertices[0].x() == 0 && vertices[1].x() == 0 && vertices[2].x() == 0 && vertices[0].y() == 0 && vertices[1].y() == 0&& vertices[2].y() == 0;
    }
    QPoint vertices[3];
};

auto CollisionFree(const QPoint &s, const QPoint &e, const std::vector<Triangle> &tr) -> bool;

auto Steer(const QPoint &s, const QPoint &e, const std::vector<Triangle> &tr)
    -> QPoint;

#endif // COLLISION_H
