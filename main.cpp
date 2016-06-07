#include <time.h>
#include <QApplication>
#include <QDebug>

#include "MyWidget.h"


int main(int argc, char *argv[]) {
    qDebug() << "hello";

    QApplication app(argc, argv);
    MyWidget viewer;
    viewer.setWindowTitle("heart");

    viewer.show();

    return app.exec();
}
