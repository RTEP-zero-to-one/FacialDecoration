#include "filter_process.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc/types_c.h>

using namespace cv;
using namespace std;

Mat filter(Mat &src, int style_num) {
    //todo: filter design and using in realtime process
    if (!style_num)
        return src;
    Mat result;
    result = src.clone();
    vector<Mat> original_channels, new_channels;
    int width = src.cols;
    int height = src.rows;
    split(result, new_channels);
    split(result, original_channels);

    switch (style_num) {
        case OLDFASHION:
            new_channels[0] =
                    0.272 * original_channels[2] + 0.534 * original_channels[1] + 0.131 * original_channels[0];
            new_channels[1] =
                    0.349 * original_channels[2] + 0.686 * original_channels[1] + 0.168 * original_channels[0];
            new_channels[2] =
                    0.393 * original_channels[2] + 0.769 * original_channels[1] + 0.189 * original_channels[0];
            merge(new_channels, result);
            break;
        case COMICBOOK: {
            for (int y = 0; y < height; y++) {
                auto *P0 = src.ptr<uchar>(y);
                auto *P1 = result.ptr<uchar>(y);
                for (int x = 0; x < width; x++) {
                    float B = P0[3 * x];
                    float G = P0[3 * x + 1];
                    float R = P0[3 * x + 2];
                    float newB = abs(B - G + B + R) * G / 256;
                    float newG = abs(B - G + B + R) * R / 256;
                    float newR = abs(G - B + G + R) * R / 256;
                    if (newB < 0)newB = 0;
                    if (newB > 255)newB = 255;
                    if (newG < 0)newG = 0;
                    if (newG > 255)newG = 255;
                    if (newR < 0)newR = 0;
                    if (newR > 255)newR = 255;
                    P1[3 * x] = (uchar) newB;
                    P1[3 * x + 1] = (uchar) newG;
                    P1[3 * x + 2] = (uchar) newR;
                }
            }
            Mat gray;
            cvtColor(result, gray, COLOR_BGR2GRAY);
            normalize(gray, gray, 255, 0, NORM_MINMAX);
            result = gray;
        }
            break;
        case FANTASY: {
            for (int y = 0; y < height; y++) {
                auto *P0 = src.ptr<uchar>(y);
                auto *P1 = result.ptr<uchar>(y);
                for (int x = 0; x < width; x++) {
                    float b0 = P0[3 * x];
                    float g0 = P0[3 * x + 1];
                    float r0 = P0[3 * x + 2];

                    float b = b0 * 255 / (g0 + r0 + 1);
                    float g = g0 * 255 / (b0 + r0 + 1);
                    float r = r0 * 255 / (g0 + b0 + 1);

                    r = (r > 255 ? 255 : (r < 0 ? 0 : r));
                    g = (g > 255 ? 255 : (g < 0 ? 0 : g));
                    b = (b > 255 ? 255 : (b < 0 ? 0 : b));

                    P1[3 * x] = (uchar) b;
                    P1[3 * x + 1] = (uchar) g;
                    P1[3 * x + 2] = (uchar) r;
                }
            }
        }
            break;
        case FREEZE: {
            for (int y = 0; y < height; y++) {
                auto *P0 = src.ptr<uchar>(y);
                auto *P1 = result.ptr<uchar>(y);
                for (int x = 0; x < width; x++) {
                    float b0 = P0[3 * x];
                    float g0 = P0[3 * x + 1];
                    float r0 = P0[3 * x + 2];

                    float b = (b0 - g0 - r0) * 3 / 2;
                    float g = (g0 - b0 - r0) * 3 / 2;
                    float r = (r0 - g0 - b0) * 3 / 2;

                    r = (r > 255 ? 255 : (r < 0 ? -r : r));
                    g = (g > 255 ? 255 : (g < 0 ? -g : g));
                    b = (b > 255 ? 255 : (b < 0 ? -b : b));

                    P1[3 * x] = (uchar) b;
                    P1[3 * x + 1] = (uchar) g;
                    P1[3 * x + 2] = (uchar) r;
                }
            }
        }
            break;
        case SKETCH: {
            Mat gray0, gray1;
            cvtColor(src, gray0, COLOR_BGR2GRAY);
            addWeighted(gray0, -1, NULL, 0, 255, gray1);
            GaussianBlur(gray1, gray1, Size(11, 11), 0);

            Mat result1(gray1.size(), CV_8UC1);
            result = result1;
            for (int y = 0; y < height; y++) {

                auto *P0 = gray0.ptr<uchar>(y);
                auto *P1 = gray1.ptr<uchar>(y);
                auto *P = result.ptr<uchar>(y);
                for (int x = 0; x < width; x++) {
                    int tmp0 = P0[x];
                    int tmp1 = P1[x];
                    P[x] = (uchar) min((tmp0 + (tmp0 * tmp1) / (256 - tmp1)), 255);
                }
            }
        }
            break;
        case WIND: {
            int num = 20;//	num：Wind line density
            int num1 = 40;//num1：Wind line length
            Mat src1u[3];
            split(src, src1u);

            src.copyTo(result);
            Point center(width / 2, height / 2);
            RNG rng;

            for (int y = 0; y < height; y++) {
                auto *P = result.ptr<uchar>(y);
                {
                    for (int i = 0; i < num; i++)
                    {
                        int newX = rng.uniform(i * width / num, (i + 1) * width / num);
                        int newY = y;

                        if (newX < 0)newX = 0;
                        if (newX > width - 1)newX = width - 1;

                        auto tmp0 = src1u[0].at<uchar>(newY, newX);
                        auto tmp1 = src1u[1].at<uchar>(newY, newX);
                        auto tmp2 = src1u[2].at<uchar>(newY, newX);

                        for (int j = 0; j < num1; j++)
                        {
                            int tmpX = newX - j;//-：Wind to the left；+：Wind to the right

                            if (tmpX < 0)tmpX = 0;
                            if (tmpX > width - 1)tmpX = width - 1;

                            P[tmpX * 3] = tmp0;
                            P[tmpX * 3 + 1] = tmp1;
                            P[tmpX * 3 + 2] = tmp2;
                        }
                    }
                }
            }
        }
            break;
//        case DARKTONE:
//            new_channels[0] = original_channels[0] * original_channels[0] / 255;
//            new_channels[1] = original_channels[1] * original_channels[1] / 255;
//            new_channels[2] = original_channels[2] * original_channels[2] / 255;
//            merge(new_channels, result);
//            break;
        default:
            break;

    }
    return result;
}