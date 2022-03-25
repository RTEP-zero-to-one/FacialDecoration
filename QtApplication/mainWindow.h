//
// Created by paul on 2022/3/25.
//

#ifndef FACIALDECORATIONTRACING_MAINWINDOW_H
#define FACIALDECORATIONTRACING_MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
};


#endif //FACIALDECORATIONTRACING_MAINWINDOW_H
