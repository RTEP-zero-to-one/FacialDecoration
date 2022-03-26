//
// Created by paul on 2022/2/23.
//

#include <QApplication>
#include "mainWindow.h"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return QApplication::exec();
}