//
// Created by paul on 2022/3/25.
//

#ifndef FACIALDECORATIONTRACING_MAINWINDOW_H
#define FACIALDECORATIONTRACING_MAINWINDOW_H

#include <QMainWindow>
#include "QTimer"
#include "QImage"
#include "QFile"
#include "QDebug"
#include <QFileDialog>
#include "opencv2/opencv.hpp"
#include "../ImageProcess/cascade.h"
#include "../ImageProcess/face_detect.h"
#include "../ImageProcess/MyThread.h"



using namespace cv;
using namespace std;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
//    Detect detection;
//    static Mat &decoratedItem;
    ~MainWindow() override;

private slots:
    void readFrame();
    void openCamera();
    void closeCamera();
    void quit();
    void getDecorationImage();
    void releaseDecoration();
    void whitenPositionChanged(int position);
    void blurPositionChanged(int position);
    void filterProcess();


private:
    Ui::MainWindow *ui;
    VideoCapture capture;
    QTimer *timer;
    Mat frame;
//    Mat decoratedItem;
    Detect detection;
    int filterStyleNum=0;
    int whitenDegree=0;
    int filterVal=0;
};


#endif //FACIALDECORATIONTRACING_MAINWINDOW_H
