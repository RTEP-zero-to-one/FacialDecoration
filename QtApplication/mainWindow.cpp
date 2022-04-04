#include "mainWindow.h"
#include "ui_mainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    loadCascade();
    ui->setupUi(this);
    setWindowTitle("Qt Application");
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(readFrame()));
    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(openCamera()));
    connect(ui->pauseButton, SIGNAL(clicked()), this, SLOT(closeCamera()));
    connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(quit()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readFrame()
{
    // capture frame
    capture>>frame;

    hat = imread("assets/hat.jpeg");
    detection.faceDetect(frame, cascade_face);
    detection.eyeDetect(frame, cascade_eye);
    detection.getAngle(frame);
    displayDetection(frame, detection);
    Mat afterProcess=detection.decorate(frame, hat);

    // show realtime frame in the label
    QImage image = QImage((const uchar*)afterProcess.data,afterProcess.cols,afterProcess.rows,QImage::Format_RGB888).rgbSwapped();
    ui->cameraShow->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::openCamera()
{
    capture.open(0);
    ui->startButton->setEnabled(false);
    ui->pauseButton->setEnabled(true);
    timer->start(25);
}

void MainWindow::closeCamera()
{
    timer->stop();
    ui->startButton->setEnabled(true);
    capture.release();
}

void MainWindow::quit()
{
    close();
}