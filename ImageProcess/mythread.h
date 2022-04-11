#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QWidget>
#include "CppThread.h"
#include <opencv2/opencv.hpp>

class Mythread : public CppThread
{
public:
    Mythread();


protected:
    void run();
};


#endif 
