#pragma once

class ThreeDSceneDrawer
{
public:
    ThreeDSceneDrawer();
    void render();

private:
    void drawGrid();
    void drawBackgroundGradient();
};
