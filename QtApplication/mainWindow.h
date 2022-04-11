//
// Created by paul on 2022/3/25.
//

#ifndef FACIALDECORATIONTRACING_MAINWINDOW_H
#define FACIALDECORATIONTRACING_MAINWINDOW_H

#include <QMainWindow>
#include "QTimer"
#include "QImage"
#include "opencv2/opencv.hpp"
#include "../ImageProcess/cascade.h"
#include "../ImageProcess/face_detect.h"


using namespace cv;
using namespace std;

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
    void getDecorationImage();
    void releaseDecoration();
    void spinBoxValueChanged(int arg);
    void sliderPositionChanged1(int position);
    void filterProcess();


private:
    Ui::MainWindow *ui;
    VideoCapture capture;
    QTimer *timer;
    Mat frame, decoratedItem,afterProcess;
    Detect detection;
    int filterStyleNum=0;
};


#endif //FACIALDECORATIONTRACING_MAINWINDOW_H
