#include "mainWindow.h"
#include "ui_mainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    loadCascade();
    ui->setupUi(this);
    setWindowTitle("Qt Application");
    ui->releaseDecoration->setVisible(false);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(readFrame()));
    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(openCamera()));
    connect(ui->pauseButton, SIGNAL(clicked()), this, SLOT(closeCamera()));
    connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(quit()));

    connect(ui->hatDecoration, SIGNAL(clicked()), this, SLOT(getDecorationImage()));
    connect(ui->otherDecoration, SIGNAL(clicked()), this, SLOT(getDecorationImage()));
    connect(ui->releaseDecoration, SIGNAL(clicked()), this, SLOT(releaseDecoration()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::readFrame() {
    // capture frame
    capture >> frame;

    detection.faceDetect(frame, cascade_face);
    detection.eyeDetect(frame, cascade_eye);
    detection.getAngle(frame);
    displayDetection(frame, detection);
    afterProcess = detection.decorate(frame, decoratedItem);

    // show realtime frame in the label
    QImage image = QImage((const uchar *) afterProcess.data, afterProcess.cols, afterProcess.rows,
                          QImage::Format_RGB888).rgbSwapped();
    ui->cameraShow->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::openCamera() {
    capture.open(0);
    ui->startButton->setEnabled(false);
    ui->pauseButton->setEnabled(true);
    timer->start(25);
}

void MainWindow::closeCamera() {
    timer->stop();
    ui->startButton->setEnabled(true);
    capture.release();
}

void MainWindow::quit() {
    close();
}

void MainWindow::getDecorationImage() {
    string btnObj = ((QPushButton *) sender())->text().toStdString();
    decoratedItem = imread("assets/" + btnObj + ".jpeg");
    if (!decoratedItem.empty()) {
        ui->releaseDecoration->setVisible(true);
    }
}

void MainWindow::releaseDecoration() {
    decoratedItem.release();
    ui->releaseDecoration->setVisible(false);
}