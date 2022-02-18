#include "../ConsoleApplication1/ConsoleApplication1/global_variable.h"
#include "../ConsoleApplication1/ConsoleApplication1/img_process.h"
#include "gtest/gtest.h"
//#include "opencv2/highgui.hpp"

int add(int a, int b) {
    return a + b;
}


TEST(test1, c1) {
//    Mat src,result;
//    src = imread("../assets/img.png");
//    result = filter(src,OLDFASHION);
    EXPECT_EQ(3, add(1, 2));
}

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}