//
// Created by paul on 2022/3/25.
//

#include "mainWindow.h"
#include "ui_mainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}