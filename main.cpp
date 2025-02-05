
#include <QApplication>
#include <QResource>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QResource::registerResource("static.qrc");

    MainWindow w;
    w.setWindowTitle("Mini Explorer");
    w.show();

    return app.exec();
}
