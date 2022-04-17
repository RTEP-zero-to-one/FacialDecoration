#include "../ImageProcess/global_variable.h"
#include "../ImageProcess/filter_process.h"
#include "../ImageProcess/face_detect.cpp"
#include "../ImageProcess/cascade.cpp"
#include "gtest/gtest.h"
#include "iostream"

TEST(FilterTest, OLDFASHION) {
    Mat src, result;
    src = imread("assets/img.png", IMREAD_ANYCOLOR);
    if (!src.empty()) {
        result = filter(src, OLDFASHION);
    } else {
        Mat img1(500, 500, CV_8UC3, Scalar(10, 100, 150));
        result = filter(img1, OLDFASHION);
    }
}

TEST(FilterTest, COMICBOOK) {
    Mat src, result;
    src = imread("assets/img.png", IMREAD_ANYCOLOR);
    if (!src.empty()) {
        result = filter(src, COMICBOOK);
    } else {
        Mat img1(500, 500, CV_8UC3, Scalar(10, 100, 150));
        result = filter(img1, COMICBOOK);
    }
}

TEST(FilterTest, FANTASY) {
    Mat src, result;
    src = imread("assets/img.png", IMREAD_ANYCOLOR);
    if (!src.empty()) {
        result = filter(src, FANTASY);
    } else {
        Mat img1(500, 500, CV_8UC3, Scalar(10, 100, 150));
        result = filter(img1, FANTASY);
    }
}

TEST(FilterTest, EMBOSSING) {
    Mat src, result;
    src = imread("assets/img.png", IMREAD_ANYCOLOR);
    if (!src.empty()) {
        result = filter(src, EMBOSSING);
    } else {
        Mat img1(500, 500, CV_8UC3, Scalar(10, 100, 150));
        result = filter(img1, EMBOSSING);
    }
}

TEST(FilterTest, SKETCH) {
    Mat src, result;
    src = imread("assets/img.png", IMREAD_ANYCOLOR);
    if (!src.empty()) {
        result = filter(src, SKETCH);
    } else {
        Mat img1(500, 500, CV_8UC3, Scalar(10, 100, 150));
        result = filter(img1, SKETCH);
    }
}

TEST(FilterTest, WIND) {
    Mat src, result;
    src = imread("assets/img.png", IMREAD_ANYCOLOR);
    if (!src.empty()) {
        result = filter(src, WIND);
    } else {
        Mat img1(500, 500, CV_8UC3, Scalar(10, 100, 150));
        result = filter(img1, WIND);
    }
}

TEST(DetectTest, Face) {
    Mat src;
    bool result;
    Detect detection;
    cascade_face.load(FACE_XML);
    src = imread("assets/person.jpg", IMREAD_ANYCOLOR);
    result = detection.faceDetect(src, cascade_face);
    EXPECT_EQ(result, 1);
}

//Please run in $ProjectDir
GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}