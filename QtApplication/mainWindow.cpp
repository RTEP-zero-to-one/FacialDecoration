#include "mainWindow.h"
#include "ui_mainWindow.h"
#include "../ImageProcess/filter_process.h"


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

    //todo: remove hat button and decoration function
    connect(ui->hatDecoration, SIGNAL(clicked()), this, SLOT(getDecorationImage()));
    connect(ui->aizenDecoration, SIGNAL(clicked()), this, SLOT(getDecorationImage()));
    connect(ui->batmanDecoration, SIGNAL(clicked()), this, SLOT(getDecorationImage()));
    connect(ui->jojoDecoration, SIGNAL(clicked()), this, SLOT(getDecorationImage()));
    connect(ui->narutoDecoration, SIGNAL(clicked()), this, SLOT(getDecorationImage()));
    connect(ui->rengokuDecoration, SIGNAL(clicked()), this, SLOT(getDecorationImage()));
    connect(ui->tanjiroDecoration, SIGNAL(clicked()), this, SLOT(getDecorationImage()));
    connect(ui->releaseDecoration, SIGNAL(clicked()), this, SLOT(releaseDecoration()));

    connect(ui->spinBox_1, SIGNAL(valueChanged(int)), this, SLOT(spinBoxValueChanged(int)));
    connect(ui->beautySlider_1, SIGNAL(valueChanged(int)), this, SLOT(sliderPositionChanged1(int)));

    connect(ui->filter_OLDFASHION, SIGNAL(clicked()), this, SLOT(filterProcess()));
    connect(ui->filter_COMICBOOK, SIGNAL(clicked()), this, SLOT(filterProcess()));
    connect(ui->filter_FANTASY, SIGNAL(clicked()), this, SLOT(filterProcess()));
    connect(ui->filter_FREEZE, SIGNAL(clicked()), this, SLOT(filterProcess()));
    connect(ui->filter_SKETCH, SIGNAL(clicked()), this, SLOT(filterProcess()));
    connect(ui->filter_WIND, SIGNAL(clicked()), this, SLOT(filterProcess()));
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
    frame = detection.decorate(frame, decoratedItem);
    MainWindow::frame = filter(MainWindow::frame, filterStyleNum);

    // show realtime frame in the label
    QImage image = QImage((const uchar *) frame.data, frame.cols, frame.rows,
                          QImage::Format_RGB888).rgbSwapped();
    ui->cameraShow->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::openCamera() {
    capture.open(0);
    capture.set(CAP_PROP_FRAME_WIDTH,640);
    capture.set(CAP_PROP_FRAME_HEIGHT,480);
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

void MainWindow::spinBoxValueChanged(int arg) {
//    cout<<arg<<endl;
}

void MainWindow::sliderPositionChanged1(int arg) {
//    cout << arg << endl;
}

void MainWindow::filterProcess() {
    string btnObj = ((QPushButton *) sender())->text().toStdString();
    if (btnObj == "OLDFASHION") {
        filterStyleNum = 1;
    } else if (btnObj == "COMICBOOK") {
        filterStyleNum = 2;
    } else if (btnObj == "FANTASY") {
        filterStyleNum = 3;
    } else if (btnObj == "FREEZE") {
        filterStyleNum = 4;
    }else if(btnObj == "SKETCH"){
        filterStyleNum = 7;
    }else if(btnObj == "WIND"){
        filterStyleNum = 8;
    }
}