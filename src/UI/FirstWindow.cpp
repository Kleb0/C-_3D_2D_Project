#include "FirstWindow.h"
#include "ui_FirstWindow.h"
#include "Engine/OpenGLWidget.hpp"

FirstWindow::FirstWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    OpenGLWidget *glWidget = new OpenGLWidget(ui->openGLWidget);
    glWidget->setGeometry(ui->openGLWidget->geometry());
}

FirstWindow::~FirstWindow()
{
    delete ui;
}