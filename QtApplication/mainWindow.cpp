#include "mainWindow.h"
#include "ui_mainWindow.h"
#include "../ImageProcess/filter_process.h"
Mat decoratedItem;
MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    QFile stylesheet("assets/stylesheet.qss");
    stylesheet.open(QFile::ReadOnly);
    QString setSheet = QLatin1String(stylesheet.readAll());
    QWidget::setStyleSheet(setSheet);

    ui->setupUi(this);
    setWindowTitle("Facial Decoration");
    setWindowIcon(QIcon("assets/icon.ico"));

    // set button invisible as initial
    ui->aizenDecoration->setVisible(false);
    ui->batmanDecoration->setVisible(false);
    ui->jojoDecoration->setVisible(false);
    ui->narutoDecoration->setVisible(false);
    ui->rengokuDecoration->setVisible(false);
    ui->ramDecoration->setVisible(false);
    ui->customDecoration->setVisible(false);
    ui->releaseDecoration->setVisible(false);
    ui->filter_OLDFASHION->setVisible(false);
    ui->filter_COMICBOOK->setVisible(false);
    ui->filter_FANTASY->setVisible(false);
    ui->filter_FREEZE->setVisible(false);
    ui->filter_SKETCH->setVisible(false);
    ui->filter_WIND->setVisible(false);
    ui->filter_ORIGINAL->setVisible(false);
    ui->whitenLabel->setVisible(false);
    ui->whitenSlider->setVisible(false);
    ui->blurLabel->setVisible(false);
    ui->blurSlider-> setVisible(false);

    ui->imageLabel->setStyleSheet("background-image: url(assets/logo2.png);");

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(readFrame()));
    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(openCamera()));
    connect(ui->pauseButton, SIGNAL(clicked()), this, SLOT(closeCamera()));
    connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(quit()));

    connect(ui->aizenDecoration, SIGNAL(clicked()), this, SLOT(getDecorationImage()));
    connect(ui->batmanDecoration, SIGNAL(clicked()), this, SLOT(getDecorationImage()));
    connect(ui->jojoDecoration, SIGNAL(clicked()), this, SLOT(getDecorationImage()));
    connect(ui->narutoDecoration, SIGNAL(clicked()), this, SLOT(getDecorationImage()));
    connect(ui->rengokuDecoration, SIGNAL(clicked()), this, SLOT(getDecorationImage()));
    connect(ui->ramDecoration, SIGNAL(clicked()), this, SLOT(getDecorationImage()));
    connect(ui->customDecoration, SIGNAL(clicked()), this, SLOT(getDecorationImage()));
    connect(ui->releaseDecoration, SIGNAL(clicked()), this, SLOT(releaseDecoration()));

    connect(ui->whitenSlider, SIGNAL(valueChanged(int)), this, SLOT(whitenPositionChanged(int)));
    connect(ui->blurSlider, SIGNAL(valueChanged(int)), this, SLOT(blurPositionChanged(int)));

    connect(ui->filter_OLDFASHION, SIGNAL(clicked()), this, SLOT(filterProcess()));
    connect(ui->filter_COMICBOOK, SIGNAL(clicked()), this, SLOT(filterProcess()));
    connect(ui->filter_FANTASY, SIGNAL(clicked()), this, SLOT(filterProcess()));
    connect(ui->filter_FREEZE, SIGNAL(clicked()), this, SLOT(filterProcess()));
    connect(ui->filter_SKETCH, SIGNAL(clicked()), this, SLOT(filterProcess()));
    connect(ui->filter_WIND, SIGNAL(clicked()), this, SLOT(filterProcess()));
    connect(ui->filter_ORIGINAL, SIGNAL(clicked()), this, SLOT(filterProcess()));

    MyThread cascade;
    cascade.start();
    cascade.join();
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
    MainWindow::frame = faceBlur(MainWindow::frame,filterVal);
    MainWindow::frame = whiteFace(MainWindow::frame, whitenDegree);
    MainWindow::frame = filter(MainWindow::frame, filterStyleNum);

    // show realtime frame in the label
    cv::cvtColor(MainWindow::frame, MainWindow::frame, COLOR_BGR2RGB);
    QImage image = QImage((const uchar *) frame.data, frame.cols, frame.rows,
                          QImage::Format_RGB888);
    ui->cameraShow->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::openCamera() {
    capture.open(0);
    capture.set(CAP_PROP_FRAME_WIDTH, 640);
    capture.set(CAP_PROP_FRAME_HEIGHT, 480);
    ui->startButton->setEnabled(false);
    ui->pauseButton->setEnabled(true);
    timer->start(25);

    // show buttons
    ui->aizenDecoration->setVisible(true);
    ui->batmanDecoration->setVisible(true);
    ui->jojoDecoration->setVisible(true);
    ui->narutoDecoration->setVisible(true);
    ui->rengokuDecoration->setVisible(true);
    ui->ramDecoration->setVisible(true);
    ui->customDecoration->setVisible(true);
    ui->filter_OLDFASHION->setVisible(true);
    ui->filter_COMICBOOK->setVisible(true);
    ui->filter_FANTASY->setVisible(true);
    ui->filter_FREEZE->setVisible(true);
    ui->filter_SKETCH->setVisible(true);
    ui->filter_WIND->setVisible(true);
    ui->whitenLabel->setVisible(true);
    ui->whitenSlider->setVisible(true);
    ui->blurLabel->setVisible(true);
    ui->blurSlider-> setVisible(true);
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
    // get text of current button
    string btnString = ((QPushButton *) sender())->text().toStdString();
    // get object of current button
    auto btn = qobject_cast<QPushButton *>(sender());
    auto btnName = btn->objectName();
    auto currentButton = this->findChild<QPushButton *>(btnName);

    decoratedItem = imread("assets/" + btnString + ".jpeg");
    if (!decoratedItem.empty()) {
        ui->releaseDecoration->setVisible(true);
    }

}

void MainWindow::releaseDecoration() {
    decoratedItem.release();
    ui->releaseDecoration->setVisible(false);
}

void MainWindow::whitenPositionChanged(int arg) {
    whitenDegree = arg;
}

void MainWindow::blurPositionChanged(int arg) {
    filterVal = arg;
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
    } else if (btnObj == "SKETCH") {
        filterStyleNum = 7;
    } else if (btnObj == "WIND") {
        filterStyleNum = 8;
    } else if (btnObj == "ORIGINAL") {
        filterStyleNum = 0;
    }
    if(filterStyleNum ==0){
        ui->filter_ORIGINAL->setVisible(false);
    }else{
        ui->filter_ORIGINAL->setVisible(true);
    }
}