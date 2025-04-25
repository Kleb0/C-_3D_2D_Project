/********************************************************************************
** Form generated from reading UI file 'GameView.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEVIEW_H
#define UI_GAMEVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "ThreeDWorldView.hpp"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QWidget *MainWidget;
    ThreeDWorldView *openGLWidget;
    QSlider *verticalSlider;
    QSlider *verticalSlider_2;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menu3DWorldView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1526, 910);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(20, 10, 1231, 821));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        MainWidget = new QWidget(gridLayoutWidget);
        MainWidget->setObjectName("MainWidget");
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        MainWidget->setPalette(palette);
        MainWidget->setAutoFillBackground(true);
        MainWidget->setStyleSheet(QString::fromUtf8("QSlider::groove:vertical {\n"
"    background: white;\n"
"    border: 1px solid #999999;\n"
"    width: 8px;\n"
"    margin: 0px 0;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QSlider::handle:vertical {\n"
"    background: #448aff;\n"
"    border: 1px solid #5c5c5c;\n"
"    height: 16px;\n"
"    margin: 2px -2px;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QSlider::sub-page:vertical {\n"
"    background: white;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QSlider::add-page:vertical {\n"
"    background: #448aff;\n"
"    border-radius: 4px;\n"
"}\n"
""));
        openGLWidget = new ThreeDWorldView(MainWidget);
        openGLWidget->setObjectName("openGLWidget");
        openGLWidget->setGeometry(QRect(10, 10, 851, 791));
        verticalSlider = new QSlider(MainWidget);
        verticalSlider->setObjectName("verticalSlider");
        verticalSlider->setGeometry(QRect(950, 340, 16, 160));
        QPalette palette1;
        QBrush brush1(QColor(222, 222, 222, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush1);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        verticalSlider->setPalette(palette1);
        verticalSlider->setAutoFillBackground(true);
        verticalSlider->setOrientation(Qt::Vertical);
        verticalSlider_2 = new QSlider(MainWidget);
        verticalSlider_2->setObjectName("verticalSlider_2");
        verticalSlider_2->setGeometry(QRect(980, 340, 16, 160));
        verticalSlider_2->setAutoFillBackground(true);
        verticalSlider_2->setStyleSheet(QString::fromUtf8("QSlider::groove:vertical {\n"
"    background: white;\n"
"    border: 1px solid #999999;\n"
"    width: 8px;\n"
"    margin: 0px 0;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QSlider::handle:vertical {\n"
"    background: #448aff;\n"
"    border: 1px solid #5c5c5c;\n"
"    height: 16px;\n"
"    margin: 2px -2px;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QSlider::sub-page:vertical {\n"
"    background: white;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QSlider::add-page:vertical {\n"
"    background: #448aff;\n"
"    border-radius: 4px;\n"
"}\n"
""));
        verticalSlider_2->setOrientation(Qt::Vertical);

        gridLayout->addWidget(MainWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1526, 21));
        menu3DWorldView = new QMenu(menubar);
        menu3DWorldView->setObjectName("menu3DWorldView");
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menu3DWorldView->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        menu3DWorldView->setTitle(QCoreApplication::translate("MainWindow", "3DWorldView", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEVIEW_H
