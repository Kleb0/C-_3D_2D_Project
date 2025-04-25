#pragma once

class ThreeDSceneDrawer
{
public:
    ThreeDSceneDrawer();
    void render();
    void initialization();

private:
    void drawGrid();
    void drawBackgroundGradient();
};
