#include "../ImageProcess/global_variable.h"
#include "../ImageProcess/filter_process.h"
#include "gtest/gtest.h"
#include "iostream"


TEST(OpenCVTest, filter_OLDFASHION) {
    Mat src, result;
    src = imread("../assets/img.png", IMREAD_ANYCOLOR);
    if (!src.empty()) {
        result = filter(src, OLDFASHION);
    } else {
        Mat img1(500, 500, CV_8UC3, Scalar(10, 100, 150));
        result = filter(img1, OLDFASHION);
    }
//    imwrite("../assets/OLDFASHION.png", result);
}

TEST(OpenCVTest, filter_COMICBOOK) {
    Mat src, result;
    src = imread("../assets/img.png", IMREAD_ANYCOLOR);
    if (!src.empty()) {
        result = filter(src, COMICBOOK);
    } else {
        Mat img1(500, 500, CV_8UC3, Scalar(10, 100, 150));
        result = filter(img1, COMICBOOK);
    }
//    imwrite("../assets/COMICBOOK.png", result);

}

TEST(OpenCVTest, filter_FANTASY) {
    Mat src, result;
    src = imread("../assets/img.png", IMREAD_ANYCOLOR);
    if (!src.empty()) {
        result = filter(src, FANTASY);
    } else {
        Mat img1(500, 500, CV_8UC3, Scalar(10, 100, 150));
        result = filter(img1, FANTASY);
    }
//    imwrite("../assets/FANTASY.png", result);

}

TEST(OpenCVTest, filter_FREEZE) {
    Mat src, result;
    src = imread("../assets/img.png", IMREAD_ANYCOLOR);
    if (!src.empty()) {
        result = filter(src, FREEZE);
    } else {
        Mat img1(500, 500, CV_8UC3, Scalar(10, 100, 150));
        result = filter(img1, FREEZE);
    }
//    imwrite("../assets/FREEZE.png", result);

}

TEST(OpenCVTest, filter_SKETCH) {
    Mat src, result;
    src = imread("../assets/img.png", IMREAD_ANYCOLOR);
    if (!src.empty()) {
        result = filter(src, SKETCH);
    }
    else {
        Mat img1(500, 500, CV_8UC3, Scalar(10, 100, 150));
        result = filter(img1, SKETCH);
    }
//    imwrite("../assets/FREEZE.png", result);

}

TEST(OpenCVTest, filter_WIND) {
    Mat src, result;
    src = imread("../assets/img.png", IMREAD_ANYCOLOR);
    if (!src.empty()) {
        result = filter(src, WIND);
    }
    else {
        Mat img1(500, 500, CV_8UC3, Scalar(10, 100, 150));
        result = filter(img1, WIND);
    }
//    imwrite("../assets/FREEZE.png", result);

}

//TEST(OpenCVTest, filter_DARKTONE) {
//    Mat src, result;
//    src = imread("../assets/img.png", IMREAD_ANYCOLOR);
//    if (!src.empty()) {
//        result = filter(src, DARKTONE);
//    }
//    imwrite("../assets/DARKTONE.png", result);
//
//}

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}