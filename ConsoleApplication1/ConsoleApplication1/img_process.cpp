#include "img_process.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc/types_c.h>

using namespace cv;
using namespace std;

Mat filter(Mat &src, int style_num) {
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
            break;
        }
        case FANTASY:
            new_channels[0] = original_channels[0] * 128 / (original_channels[1] + original_channels[2] + 1);
            new_channels[1] = original_channels[1] * 128 / (original_channels[2] + original_channels[0] + 1);
            new_channels[2] = original_channels[2] * 128 / (original_channels[0] + original_channels[1] + 1);
            merge(new_channels, result);
            break;
        case FREEZE:
            new_channels[0] = abs(original_channels[0] - original_channels[2] - original_channels[1]) * 3 / 2;
            new_channels[1] = abs(original_channels[1] - original_channels[2] - original_channels[0]) * 3 / 2;
            new_channels[2] = abs(original_channels[2] - original_channels[1] - original_channels[0]) * 3 / 2;
            merge(new_channels, result);
            break;
        case DARKTONE:
            new_channels[0] = original_channels[0] * original_channels[0] / 255;
            new_channels[1] = original_channels[1] * original_channels[1] / 255;
            new_channels[2] = original_channels[2] * original_channels[2] / 255;
            merge(new_channels, result);
            break;
    }
    return result;
}