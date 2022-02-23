//
// Created by paul on 2022/2/23.
//

#include <QApplication>
#include <QFormLayout>
#include <QtGlobal>
#include <QObject>
#include <QSlider>
#include <QSpinBox>
#include <QWidget>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    auto window = new QWidget;
    auto spinBox = new QSpinBox;
    spinBox->setRange(0, 100);
    auto slider = new QSlider;
    slider->setRange(0, 100);
    QObject::connect(spinBox,
            // 对于重载函数需要给出确定的版本，QOverload需要编译器支持c++11
                     QOverload<int>::of(&QSpinBox::valueChanged),
                     slider,
                     &QSlider::setValue);
    QObject::connect(slider,
                     &QSlider::valueChanged,
                     spinBox,
                     &QSpinBox::setValue);
    auto layout = new QFormLayout;
    layout->addRow("spin box:", spinBox);
    layout->addRow("slider:", slider);
    window->setLayout(layout);
    window->show();
    return app.exec();
}