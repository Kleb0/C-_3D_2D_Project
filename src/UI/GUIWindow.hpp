#pragma once

class GUIWindow
{
public:
    GUIWindow() = default;
    virtual ~GUIWindow();

    virtual void render() = 0; // Fonction pure : chaque fenêtre doit définir son affichage
};
