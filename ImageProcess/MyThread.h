#ifndef FACIALDECORATIONTRACING_MYTHREAD_H
#define FACIALDECORATIONTRACING_MYTHREAD_H
#include "../cppThread/CppThread.h"
#include "face_detect.h"
#include "../QtApplication/mainWindow.h"

class MyThread :public CppThread{
public:
    MyThread(){
    }
protected:
    void run() override;

private:
    Detect *detection;
};


#endif //FACIALDECORATIONTRACING_MYTHREAD_H
