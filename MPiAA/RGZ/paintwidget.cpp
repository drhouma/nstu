#include "paintwidget.h"
#include <QPen>
#include <QPainter>
#include <random>
#include <cmath>

PaintWidget::PaintWidget(QWidget *parent) : QWidget{parent}
{
    graph = Graph();
}

auto inVector(int p, const std::vector<int> &v) -> bool {
    for (const auto& elem : v) {
        if (p == elem) return true;
    }
    return false;
}

auto concatVectors(std::vector<int> &dest, std::vector<int> v2) -> void {
    for (const auto &elem : v2) {
        dest.emplace_back(elem);
    }
}


auto PaintWidget::mousePressEvent(QMouseEvent *event) -> void {
  if (event->button() == Qt::LeftButton) {
      if (m_mode == "points") {
          if (m_click_counter > 1)
              return;
         if (m_click_counter == 0)
              m_path[0] = event->pos();
          else
              m_path[1] = event->pos();

        ++m_click_counter;
        if (m_click_counter == 2) {
            m_path_setted = true;
        } else {
            m_path_setted = false;
        }
      } else if (m_mode == "triangle") {
          m_triangle_points_buf[m_click_counter] = event->pos();
          m_click_counter++;
          if (m_click_counter == 3) {
              Triangle tmp(m_triangle_points_buf[0],m_triangle_points_buf[1],m_triangle_points_buf[2]);
              m_triangle_buf.push_back(tmp);
              m_click_counter = 0;
          }
      } else if (m_mode == "intermediate") {
          QPoint tmp = event->pos();
          QPoint tmp2 = NearestVertex(tmp, m_points);
          if (lineLen(tmp, tmp2) < 30) {
              int index{0};
              for (const auto& elem : m_points) {
                  if (elem == tmp2) break;
                  index++;
              }
              if (!inVector(index, m_im_points)) m_im_points.emplace_back(index);
          }
      }
  } else if (event->button() == Qt::RightButton) {
    m_click_counter = 0;
    m_path_setted = false;
    ClearPath();
    RemoveTriangles();
    ClearIMPoints();
  }
  repaint();
}

void PaintWidget::SetMode(QString mode)
{
    m_click_counter = 0;
    m_mode = mode;
    repaint();
}

void PaintWidget::RemoveTriangles()
{
    m_triangle_buf.clear();
    repaint();
}

void PaintWidget::RemoveStartEnd()
{
    m_path_setted = false;
    if (m_mode == "points") {
        m_click_counter = 0;
    }
    repaint();
}

void PaintWidget::ClearPath() {
    m_need_path = false;
    graph = Graph();
    m_points.clear();
    m_im_points.clear();
    iter = 1;
    repaint();
}

void PaintWidget::ClearIMPoints() {
    m_im_points.clear();
    repaint();
}

void PaintWidget::SetVisionDistance(int value) {
    m_vision_distance = value;
    repaint();
}

double lineLen(const QPoint &p1, const QPoint &p2) {
    int x = p1.x() - p2.x();
    int y = p1.y() - p2.y();
    return sqrt(x * x + y * y);
}

void PaintWidget::BuildTree(int vertices) {
    if (!m_path_setted) {
        return;
    }

    int start_v{0}, end_v{std::numeric_limits<int>::max()};
    bool finded {false};


    std::random_device rd;
    std::default_random_engine engine{rd()};
    std::uniform_int_distribution<int> i_dist(1, windowSize - 1);



    if (m_points.empty()) {
        m_points.emplace_back(m_path[0]);
        graph.add_vertex(start_v);
        graph.add_vertex(end_v);
    }
    int iter1 = 0;
    while (iter1 < vertices && !finded) {
        QPoint rdp{i_dist(engine), i_dist(engine)};
        QPoint nearest = NearestVertex(rdp, m_points);

        int index{0};
        for (const auto &elem : m_points) {
            if (elem == nearest) break;
            index++;
        }
        double angle = -M_PI_2  + atan2(rdp.x() - nearest.x(), rdp.y() - nearest.y());
        int step_x = STICK_LEN * cos(angle);
        int step_y = STICK_LEN * sin(angle);
        QPoint next(nearest.x() + step_x, nearest.y() - step_y);
        if (!CollisionFree(nearest, next, m_triangle_buf)) {
            next = Steer(nearest, next, m_triangle_buf);
        }
        last_point = rdp;
        graph.add_vertex(iter);
        graph.add_edge(index, iter, STICK_LEN);
        m_points.emplace_back(next);
        iter++;
        iter1++;
    }

    repaint();
}

void PaintWidget::FindPath()
{
    m_need_path = !m_need_path;
    repaint();
}

QPoint PaintWidget::NearestVertex(const QPoint &v, const std::vector<QPoint> &points) {
    double minLen = std::numeric_limits<double>::max();
    QPoint res;

    for (const auto &elem : points) {
        double tmpLen = lineLen(elem, v);
        if (tmpLen < minLen) {
            minLen = tmpLen;
            res = elem;
        }
    }
    return res;
}

auto PaintWidget::paintEvent(QPaintEvent *event) -> void {
  QPainter painter{this};
  QPen pen{Qt::black};
  pen.setStyle(Qt::SolidLine);
  pen.setWidth(lineWidth);
  painter.setPen(pen);
  painter.drawLine(1, 1, 1, windowSize - 1);
  painter.drawLine(1, 1, windowSize, 1);
  painter.drawLine(windowSize - 1, 1, windowSize - 1, windowSize - 1);
  painter.drawLine(1, windowSize - 1, windowSize - 1, windowSize - 1);

  if (m_mode == "triangle") {
      pen.setColor(Qt::black);
      painter.setPen(pen);
      for (int i = 0; i < m_click_counter; i++) {
          painter.drawEllipse(m_triangle_points_buf[i], 3, 3);
      }
  }
  for (auto &elem : m_triangle_buf) {
      QPainterPath path;
      path.lineTo(elem.vertices[0]);
      path.lineTo(elem.vertices[1]);
      path.lineTo(elem.vertices[2]);
      path.lineTo(elem.vertices[0]);
      painter.fillPath(path, QBrush(QColor ("black")));
  }

  if (m_path_setted) {
      pen.setColor(Qt::blue);
      painter.setPen(pen);
      for (int i = 0; i < 2; i++) {
          painter.drawEllipse(m_path[i], 5, 5);
          pen.setColor(Qt::red);
          painter.setPen(pen);
      }
  } else {
      if (m_mode == "points") {
          pen.setColor(Qt::blue);
          painter.setPen(pen);
          for (int i = 0; i < m_click_counter; i++) {
              painter.drawEllipse(m_path[i], 5, 5);
              pen.setColor(Qt::red);
              painter.setPen(pen);
          }
      }
  }
  const auto &vertices = graph.get_vertices();
  pen.setColor(Qt::magenta);
  painter.setPen(pen);
  painter.drawEllipse(last_point, 3, 3);
  pen.setColor(Qt::red);
  painter.setPen(pen);
  for (const auto &v : vertices) {
      const auto &edges = graph.get_adjacent_edges(v);
      for (const auto &e : edges) {
          painter.drawEllipse(m_points[v], 2, 2);
          painter.drawLine(m_points[v], m_points[e.first]);
      }
  }

  if (m_need_path && m_path_setted) {

      pen.setColor(Qt::magenta);
      pen.setWidth(4);
      painter.setPen(pen);
      painter.drawEllipse(m_path[1], m_vision_distance, m_vision_distance);

      std::vector<int> im_points{0};
      concatVectors(im_points, m_im_points);
      std::vector<int> im_path;
      for (int i = 1; i < im_points.size(); i++) {
        concatVectors(im_path, shortest_path(graph, im_points[i - 1], im_points[i]));
      }

      if (!(im_path.size() == 0 && m_im_points.size() != 0)) {
          int start_vertex = im_path.size() == 0 ? 0 : im_path.back();
          auto path = shortest_path(graph, start_vertex, m_vision_distance,m_points, m_path[1]);

          concatVectors(im_path, path);
          if ( path.size() == 0 && m_points.size()!= 0 && im_path.size()!= 0 && lineLen(m_points[im_path.back()], m_path[1]) > m_vision_distance )im_path.clear();
          for (int i = 1; i < im_path.size(); i++) {
              painter.drawEllipse(m_points[im_path[i]], 2, 2);
              painter.drawLine(m_points[im_path[i-1]], m_points[im_path[i]]);
          }
      }
  }
  pen.setColor(Qt::red);
  pen.setWidth(2);
  painter.setBrush(Qt::green);
  painter.setPen(Qt::green);
  for (const auto& elem : m_im_points) {
      painter.drawEllipse(m_points[elem], 5, 5);
  }
}
