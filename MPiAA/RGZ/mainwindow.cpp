#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    m_pw = ui->PaintScene;
    m_pw->SetVisionDistance(ui->horizontalSlider->value());
    ui->distance_label->setText(QString::number(ui->horizontalSlider->value()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_init_goal_rb_toggled(bool checked)
{
    if (checked) {
        m_pw->SetMode("points");
        m_pw->ClearIMPoints();
        m_pw->ClearPath();
        m_pw->RemoveStartEnd();
    }
}


void MainWindow::on_triangles_rb_toggled(bool checked)
{
    if (checked) {
        m_pw->SetMode("triangle");
    }
}


void MainWindow::on_remove_tr_clicked()
{
    m_pw->RemoveTriangles();
}


void MainWindow::on_remove_start_end_clicked()
{
    m_pw->RemoveStartEnd();
}


void MainWindow::on_find_path_clicked()
{
    m_pw->FindPath();
}


void MainWindow::on_clear_path_clicked()
{
    m_pw->ClearPath();
}


void MainWindow::on_horizontalSlider_sliderReleased()
{
    m_pw->SetVisionDistance(ui->horizontalSlider->value());
    ui->distance_label->setText(QString::number(ui->horizontalSlider->value()));
}


void MainWindow::on_add_vertex_clicked()
{
    m_pw->BuildTree(ui->spinBox->value());
}


void MainWindow::on_intermediate_points_toggled(bool checked)
{
    if (checked) {
        m_pw->SetMode("intermediate");
    }
}


void MainWindow::on_clear_path_2_clicked()
{
    m_pw->ClearIMPoints();
}

