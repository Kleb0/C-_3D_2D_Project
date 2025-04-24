#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include "Engine/ThreeDSceneDrawer.hpp"

class ThreeDWorldView : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit ThreeDWorldView(QWidget *parent = nullptr);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    ThreeDSceneDrawer scene;
};
