#ifndef GIFCONVERTER_H
#define GIFCONVERTER_H

#include <opencv.hpp>
#include "gif.h"

class GifConverter {
public:
    GifConverter(const std::string& inputVideoPath, const std::string& outputGifPath, int bitDepth = 8, bool dither = false);
    bool convertToGif();

private:
    std::string inputVideoPath;
    std::string outputGifPath;
    int bitDepth;
    bool dither;

    void MatToRGB(const cv::Mat& mat, uint8_t* rgb);
};

#endif // GIFCONVERTER_H
