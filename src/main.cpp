#include <QApplication>
#include "UI/FirstWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    FirstWindow window;
    window.show();

    return app.exec();
}
