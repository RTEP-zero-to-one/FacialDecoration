//
// Created by paul on 2022/3/25.
//

#ifndef FACIALDECORATIONTRACING_MAINWINDOW_H
#define FACIALDECORATIONTRACING_MAINWINDOW_H

#include <QMainWindow>
#include "QTimer"
#include "QImage"
#include "opencv2/opencv.hpp"

using namespace cv;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private slots:

    void readFrame();

    void openCamera();

    void closeCamera();
    void quit();

private:
    Ui::MainWindow *ui;
    VideoCapture capture;
    QTimer *timer;
    Mat frame;

};


#endif //FACIALDECORATIONTRACING_MAINWINDOW_H
