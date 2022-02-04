//
// Created by paul on 2022/2/2.
//

#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv) {
    // open stream
    VideoCapture capture;
    capture.open(0);
    if (!capture.isOpened()) {
        printf("could not read file...\n");
        return -1;
    }

    Mat frame;
    namedWindow("video_stream_demo", WINDOW_AUTOSIZE);
    while (capture.read(frame)) {
        imshow("video_stream_demo", frame);
        int c = waitKey(50);
        if ((char) c == 27) {   // press Esc to quit
            break;
        }
    }
    capture.release();
    return 0;
}
