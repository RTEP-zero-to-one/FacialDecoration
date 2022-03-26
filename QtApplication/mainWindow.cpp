#include "mainWindow.h"
#include "ui_mainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
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
    //    todo: show decoration

    // show realtime frame in the label
    QImage image = QImage((const uchar*)frame.data,frame.cols,frame.rows,QImage::Format_RGB888).rgbSwapped();
    ui->cameraShow->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::openCamera()
{
    capture.open(0);
    timer->start(25);
}

void MainWindow::closeCamera()
{
    timer->stop();
    capture.release();
}

void MainWindow::quit()
{
    close();
}