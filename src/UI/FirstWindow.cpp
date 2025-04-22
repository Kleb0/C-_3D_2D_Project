#include "FirstWindow.h"
#include "ui_FirstWindow.h"
#include "Engine/OpenGLWidget.hpp"

FirstWindow::FirstWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

FirstWindow::~FirstWindow()
{
    delete ui;
}