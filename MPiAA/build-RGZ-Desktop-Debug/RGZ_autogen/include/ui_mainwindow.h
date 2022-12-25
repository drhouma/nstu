/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "paintwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    PaintWidget *PaintScene;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QRadioButton *init_goal_rb;
    QRadioButton *triangles_rb;
    QRadioButton *intermediate_points;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *remove_tr;
    QPushButton *remove_start_end;
    QPushButton *clear_path;
    QPushButton *clear_path_2;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QPushButton *add_vertex;
    QSpinBox *spinBox;
    QSlider *horizontalSlider;
    QPushButton *find_path;
    QLabel *distance_label;
    QLabel *label_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1036, 782);
        MainWindow->setMinimumSize(QSize(600, 650));
        MainWindow->setMaximumSize(QSize(1100, 782));
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgba(246, 225, 14, 195);\n"
"\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        PaintScene = new PaintWidget(centralwidget);
        PaintScene->setObjectName(QString::fromUtf8("PaintScene"));
        PaintScene->setGeometry(QRect(0, 0, 781, 781));
        PaintScene->setMinimumSize(QSize(781, 571));
        PaintScene->setMaximumSize(QSize(781, 781));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(790, 10, 240, 111));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        init_goal_rb = new QRadioButton(verticalLayoutWidget);
        init_goal_rb->setObjectName(QString::fromUtf8("init_goal_rb"));
        init_goal_rb->setStyleSheet(QString::fromUtf8("QRadioButton {\n"
"	background-color: rgb(230, 116, 25);\n"
"	color: rgb(255, 255, 255);\n"
"	font-size: 20px;\n"
"	border: 1px solid ;\n"
"	border-radius: 10px;\n"
"	\n"
"	border-color: rgb(239, 41, 41);\n"
"};"));
        init_goal_rb->setChecked(true);

        verticalLayout->addWidget(init_goal_rb);

        triangles_rb = new QRadioButton(verticalLayoutWidget);
        triangles_rb->setObjectName(QString::fromUtf8("triangles_rb"));
        triangles_rb->setStyleSheet(QString::fromUtf8("QRadioButton {\n"
"	background-color: rgb(230, 116, 25);\n"
"	color: rgb(255, 255, 255);\n"
"	font-size: 20px;\n"
"	border: 1px solid ;\n"
"	border-radius: 10px;\n"
"	\n"
"	border-color: rgb(239, 41, 41);\n"
"};"));

        verticalLayout->addWidget(triangles_rb);

        intermediate_points = new QRadioButton(verticalLayoutWidget);
        intermediate_points->setObjectName(QString::fromUtf8("intermediate_points"));
        intermediate_points->setStyleSheet(QString::fromUtf8("QRadioButton {\n"
"	background-color: rgb(230, 116, 25);\n"
"	color: rgb(255, 255, 255);\n"
"	font-size: 20px;\n"
"	border: 1px solid ;\n"
"	border-radius: 10px;\n"
"	\n"
"	border-color: rgb(239, 41, 41);\n"
"};"));

        verticalLayout->addWidget(intermediate_points);

        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(790, 130, 231, 143));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        remove_tr = new QPushButton(verticalLayoutWidget_2);
        remove_tr->setObjectName(QString::fromUtf8("remove_tr"));
        remove_tr->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(230, 116, 25);\n"
"	color: rgb(255, 255, 255);\n"
"	font-size: 20px;\n"
"	border: 1px solid ;\n"
"	border-radius: 10px;\n"
"	\n"
"	border-color: rgb(239, 41, 41);\n"
"};\n"
""));

        verticalLayout_2->addWidget(remove_tr);

        remove_start_end = new QPushButton(verticalLayoutWidget_2);
        remove_start_end->setObjectName(QString::fromUtf8("remove_start_end"));
        remove_start_end->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(230, 116, 25);\n"
"	color: rgb(255, 255, 255);\n"
"	font-size: 20px;\n"
"	border: 1px solid ;\n"
"	border-radius: 10px;\n"
"	\n"
"	border-color: rgb(239, 41, 41);\n"
"};\n"
""));

        verticalLayout_2->addWidget(remove_start_end);

        clear_path = new QPushButton(verticalLayoutWidget_2);
        clear_path->setObjectName(QString::fromUtf8("clear_path"));
        clear_path->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(230, 116, 25);\n"
"	color: rgb(255, 255, 255);\n"
"	font-size: 20px;\n"
"	border: 1px solid ;\n"
"	border-radius: 10px;\n"
"	\n"
"	border-color: rgb(239, 41, 41);\n"
"};\n"
""));

        verticalLayout_2->addWidget(clear_path);

        clear_path_2 = new QPushButton(verticalLayoutWidget_2);
        clear_path_2->setObjectName(QString::fromUtf8("clear_path_2"));
        clear_path_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(230, 116, 25);\n"
"	color: rgb(255, 255, 255);\n"
"	font-size: 20px;\n"
"	border: 1px solid ;\n"
"	border-radius: 10px;\n"
"	\n"
"	border-color: rgb(239, 41, 41);\n"
"};\n"
""));

        verticalLayout_2->addWidget(clear_path_2);

        verticalLayoutWidget_3 = new QWidget(centralwidget);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(790, 280, 231, 91));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        add_vertex = new QPushButton(verticalLayoutWidget_3);
        add_vertex->setObjectName(QString::fromUtf8("add_vertex"));
        add_vertex->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(230, 116, 25);\n"
"	color: rgb(255, 255, 255);\n"
"	font-size: 20px;\n"
"	border: 1px solid ;\n"
"	border-radius: 10px;\n"
"	\n"
"	border-color: rgb(239, 41, 41);\n"
"};\n"
""));

        verticalLayout_3->addWidget(add_vertex);

        spinBox = new QSpinBox(verticalLayoutWidget_3);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setStyleSheet(QString::fromUtf8("\n"
"	background-color: rgb(230, 116, 25);\n"
"	color: rgb(255, 255, 255);\n"
"	font-size: 20px;\n"
"	border: 1px solid ;\n"
"	border-radius: 10px;\n"
"	\n"
"	border-color: rgb(239, 41, 41);\n"
""));
        spinBox->setAlignment(Qt::AlignCenter);
        spinBox->setMaximum(1000);

        verticalLayout_3->addWidget(spinBox);

        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(790, 490, 171, 31));
        horizontalSlider->setStyleSheet(QString::fromUtf8("\n"
"	background-color: rgb(230, 116, 25);\n"
"	color: rgb(255, 255, 255);\n"
"	font-size: 20px;\n"
"	border: 2px solid ;\n"
"	border-radius: 10px;\n"
"	\n"
"	border-color: rgb(239, 41, 41);\n"
""));
        horizontalSlider->setSliderPosition(55);
        horizontalSlider->setOrientation(Qt::Horizontal);
        find_path = new QPushButton(centralwidget);
        find_path->setObjectName(QString::fromUtf8("find_path"));
        find_path->setGeometry(QRect(790, 430, 231, 25));
        find_path->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(230, 116, 25);\n"
"	color: rgb(255, 255, 255);\n"
"	font-size: 20px;\n"
"	border: 1px solid ;\n"
"	border-radius: 10px;\n"
"	\n"
"	border-color: rgb(239, 41, 41);\n"
"};\n"
""));
        distance_label = new QLabel(centralwidget);
        distance_label->setObjectName(QString::fromUtf8("distance_label"));
        distance_label->setGeometry(QRect(970, 490, 51, 31));
        distance_label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"background-color: rgb(230, 116, 25);\n"
"	color: rgb(255, 255, 255);\n"
"	font-size: 20px;\n"
"	border: 1px solid ;\n"
"	border-radius: 10px;\n"
"	\n"
"	border-color: rgb(239, 41, 41);\n"
"}"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(790, 460, 231, 21));
        label_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"background-color: rgb(230, 116, 25);\n"
"	color: rgb(255, 255, 255);\n"
"	font-size: 20px;\n"
"	border: 1px solid ;\n"
"	border-radius: 10px;\n"
"	\n"
"	border-color: rgb(239, 41, 41);\n"
"}"));
        label_2->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Maze", nullptr));
        init_goal_rb->setText(QApplication::translate("MainWindow", "Set init/Goal points", nullptr));
        triangles_rb->setText(QApplication::translate("MainWindow", "Set Triangles", nullptr));
        intermediate_points->setText(QApplication::translate("MainWindow", "Set Intermediate\n"
"points", nullptr));
        remove_tr->setText(QApplication::translate("MainWindow", "Remove Triangles", nullptr));
        remove_start_end->setText(QApplication::translate("MainWindow", "Remove start / end", nullptr));
        clear_path->setText(QApplication::translate("MainWindow", "Remove Tree", nullptr));
        clear_path_2->setText(QApplication::translate("MainWindow", "Remove Intermediate\n"
" Points", nullptr));
        add_vertex->setText(QApplication::translate("MainWindow", "Add Vertex", nullptr));
        find_path->setText(QApplication::translate("MainWindow", "Enable / disable Search", nullptr));
        distance_label->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "Vision distance", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
