#include "../ImageProcess/global_variable.h"
#include "../ImageProcess/filter_process.h"
#include "gtest/gtest.h"
#include "iostream"


TEST(OpenCVTest, filter_OLDFASHION) {
    Mat src, result;
    src = imread("../assets/img.png", IMREAD_ANYCOLOR);
    result = filter(src, OLDFASHION);
//    imwrite("../assets/OLDFASHION.png", result);
}

TEST(OpenCVTest, filter_COMICBOOK) {
    Mat src, result;
    src = imread("../assets/img.png", IMREAD_ANYCOLOR);
    result = filter(src, COMICBOOK);
//    imwrite("../assets/COMICBOOK.png", result);

}

TEST(OpenCVTest, filter_FANTASY) {
    Mat src, result;
    src = imread("../assets/img.png", IMREAD_ANYCOLOR);
    result = filter(src, FANTASY);
//    imwrite("../assets/FANTASY.png", result);

}

TEST(OpenCVTest, filter_FREEZE) {
    Mat src, result;
    src = imread("../assets/img.png", IMREAD_ANYCOLOR);
    result = filter(src, FREEZE);
//    imwrite("../assets/FREEZE.png", result);

}

//TEST(OpenCVTest, filter_DARKTONE) {
//    Mat src, result;
//    src = imread("../assets/img.png", IMREAD_ANYCOLOR);
//    result = filter(src, DARKTONE);
//    imwrite("../assets/DARKTONE.png", result);
//
//}

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}