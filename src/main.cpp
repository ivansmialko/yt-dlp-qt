#include "MainWindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("yt-dlp-qt");
    app.setOrganizationName("smialko");

    MainWindow window;
    window.show();

    return app.exec();
}   