#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "paintwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_clear_path_2_clicked();

private slots:
    void on_intermediate_points_toggled(bool checked);

private slots:
    void on_add_vertex_clicked();

private slots:
    void on_horizontalSlider_sliderReleased();

private slots:
    void on_clear_path_clicked();

private slots:
    void on_find_path_clicked();

private slots:
    void on_remove_start_end_clicked();

private slots:
    void on_remove_tr_clicked();

private slots:
    void on_triangles_rb_toggled(bool checked);

private slots:
    void on_init_goal_rb_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    PaintWidget *m_pw;
};
#endif // MAINWINDOW_H
