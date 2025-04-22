#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class SDL2Widget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit SDL2Widget(QWidget *parent = nullptr);
    ~SDL2Widget();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    SDL_Surface *imageSurface = nullptr;
    GLuint textureId = 0;
};
