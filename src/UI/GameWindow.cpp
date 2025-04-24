#include "UI/GameWindow.hpp"
#include "ui_GameView.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

GameWindow::~GameWindow()
{
    delete ui;
}
