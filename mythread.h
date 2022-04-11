#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QWidget>
#include <QThread>
#include <opencv2/opencv.hpp>

class Mythread : public QThread
{
public:
    Mythread();


protected:
    void run();
};


#endif 
