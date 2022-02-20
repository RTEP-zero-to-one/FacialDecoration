#include "../ConsoleApplication1/ConsoleApplication1/global_variable.h"
#include "../ConsoleApplication1/ConsoleApplication1/img_process.h"
#include "gtest/gtest.h"
#include "iostream"


TEST(OpenCVTest, imgprocess_OLDFASHION) {
    Mat src, result;
    src = imread("assets/cat.jpg", IMREAD_ANYCOLOR);
    result = filter(src, OLDFASHION);
    imwrite("assets/cat_after.jpg", result);
}

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}