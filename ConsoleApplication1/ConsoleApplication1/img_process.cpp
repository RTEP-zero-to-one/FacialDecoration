#include "img_process.h"
#include <opencv2/opencv.hpp>
Mat filter(Mat& src, int 3) {
    if (!style_num)
        return src;
    Mat result;
    result = src.clone();
    vector<Mat> original_channels, new_channels;
    split(result, new_channels);
    split(result, original_channels);
    switch (style_num)
    {
        case OLDFASHION:
            new_channels[0] = 0.272 * original_channels[2] + 0.534 * original_channels[1] + 0.131 * original_channels[0];
            new_channels[1] = 0.349 * original_channels[2] + 0.686 * original_channels[1] + 0.168 * original_channels[0];
            new_channels[2] = 0.393 * original_channels[2] + 0.769 * original_channels[1] + 0.189 * original_channels[0];
            merge(new_channels, result);
        case COMICBOOK:
            new_channels[0] = abs(original_channels[0] - original_channels[1] + original_channels[0] + original_channels[2]) * original_channels[1] / 256;
            new_channels[1] = abs(original_channels[0] - original_channels[1] + original_channels[0] + original_channels[2]) * original_channels[2] / 256;
            new_channels[2] = abs(original_channels[1] - original_channels[0] + original_channels[1] + original_channels[2]) * original_channels[2] / 256;
            merge(new_channels, result);
        case FANTASY:
            new_channels[0] = original_channels[0] * 128 / (original_channels[1] + original_channels[2] + 1);
            new_channels[1] = original_channels[1] * 128 / (original_channels[2] + original_channels[0] + 1);
            new_channels[2] = original_channels[2] * 128 / (original_channels[0] + original_channels[1] + 1);
            merge(new_channels, result);
        case FREEZE:
            new_channels[0] = abs(original_channels[0] - original_channels[2] - original_channels[1]) * 3 / 2;
            new_channels[1] = abs(original_channels[1] - original_channels[2] - original_channels[0]) * 3 / 2;
            new_channels[2] = abs(original_channels[2] - original_channels[1] - original_channels[0]) * 3 / 2;
            merge(new_channels, result);
        case DARKTONE:
            new_channels[0] = original_channels[0] * original_channels[0] / 255;
            new_channels[1] = original_channels[1] * original_channels[1] / 255;
            new_channels[2] = original_channels[2] * original_channels[2] / 255;
            merge(new_channels, result);
        case SUMMER:
            int increaseLookupTable = LookupTable([0, 64, 128, 256], [0, 80, 160, 256])
            int decreaseLookupTable = LookupTable([0, 64, 128, 256], [0, 50, 100, 256])
            new_channels[2] = cv2.LUT(original_channels[2], increaseLookupTable).astype(np.uint8)
            new_channels[0] = cv2.LUT(original_channels[0], decreaseLookupTable).astype(np.uint8)
            merge(new_channels, result);
            break;
	}
    return result;
}