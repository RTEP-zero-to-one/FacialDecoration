#include "../ImageProcess/global_variable.h"
#include "../ImageProcess/img_process.h"
#include "gtest/gtest.h"
#include "iostream"


TEST(OpenCVTest, imgprocess_OLDFASHION) {
    Mat src, result;
    src = imread("../assets/img.png", IMREAD_ANYCOLOR);
    filter(src, FANTASY);
}

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}