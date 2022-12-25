#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H


#include <QWidget>
#include <QPaintEvent>
#include <QPointF>
#include <QMouseEvent>
#include <QString>
#include <vector>
#include "graph.h"
#include "collision.h"

auto shortest_path(const Graph &graph,int start_vertex ,int vision_distance, const std::vector<QPoint> &vp, const QPoint& p) -> std::vector<int>;
double lineLen(const QPoint &p1, const QPoint &p2);


class PaintWidget : public QWidget {
            Q_OBJECT
//            Q_DISABLE_COPY_MOVE(PaintWidget)

        public:
            explicit PaintWidget(QWidget *parent = nullptr);
            ~PaintWidget() = default;


        private:
            auto paintEvent(QPaintEvent* event) -> void override;
            auto mousePressEvent(QMouseEvent* event) -> void override;

        public:
            auto SetMode(QString mode) -> void;
            auto RemoveTriangles() -> void;
            auto RemoveStartEnd() -> void;
            auto ClearPath() -> void;
            auto ClearIMPoints() -> void;
            auto SetVisionDistance(int value) -> void;

            auto BuildTree(int vertices) -> void;
            auto FindPath() -> void;

        private:
            auto NearestVertex(const QPoint &v, const std::vector<QPoint> &points) -> QPoint;

        private:
            int iter{1};
            QPoint last_point;
            int m_click_counter{0};
            int m_vision_distance;
            QPoint m_path[2];
            QString m_mode{"points"};
            bool m_path_setted{false};
            bool m_need_path{true};
            Graph graph;
            std::vector<QPoint> m_points;
            std::vector<int> m_im_points;
            static constexpr int lineWidth{2};
            static constexpr double windowSize{781};
            const QString purpleColor {"#CC0099"};

            std::vector<Triangle> m_triangle_buf;
            QPoint m_triangle_points_buf[3];
        };


#endif // PAINTWIDGET_H
