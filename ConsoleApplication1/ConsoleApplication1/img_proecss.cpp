#include "img_process.h"
Mat filter(Mat& src, int style_num) {
    if (!style_num)
        return src;
    Mat result;
    result = src.clone();
    vector<Mat> original_channels, new_channels;   // 
    split(result, new_channels);
    split(result, original_channels);
    switch (style_num)
    {
        case OLDFASHION:
            new_channels[0] = 0.272 * original_channels[2] + 0.534 * original_channels[1] + 0.131 * original_channels[0];
            new_channels[1] = 0.349 * original_channels[2] + 0.686 * original_channels[1] + 0.168 * original_channels[0];
            new_channels[2] = 0.393 * original_channels[2] + 0.769 * original_channels[1] + 0.189 * original_channels[0];
            merge(new_channels, result);
            break;

	}
    return result;
}