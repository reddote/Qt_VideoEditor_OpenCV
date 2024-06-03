#include "..\Header\GifConverter.h"
#include <iostream>

GifConverter::GifConverter(const std::string& inputVideoPath, const std::string& outputGifPath, int bitDepth, bool dither)
    : inputVideoPath(inputVideoPath), outputGifPath(outputGifPath), bitDepth(bitDepth), dither(dither) {}

void GifConverter::MatToRGB(const cv::Mat& mat, uint8_t* rgb) {
    for (int y = 0; y < mat.rows; y++) {
        for (int x = 0; x < mat.cols; x++) {
            cv::Vec3b color = mat.at<cv::Vec3b>(cv::Point(x, y));
            rgb[(y * mat.cols + x) * 3 + 0] = color[2]; // R
            rgb[(y * mat.cols + x) * 3 + 1] = color[1]; // G
            rgb[(y * mat.cols + x) * 3 + 2] = color[0]; // B
        }
    }
}

bool GifConverter::convertToGif() {
    // Open the video file
    cv::VideoCapture cap(inputVideoPath);
    if (!cap.isOpened()) {
        std::cerr << "Error opening video file" << std::endl;
        return false;
    }

    // Get video properties
    int frame_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    int fps = cap.get(cv::CAP_PROP_FPS);

    // Create a GIF writer
    GifWriter gifWriter;
    if (!GifBegin(&gifWriter, outputGifPath.c_str(), frame_width, frame_height, 100 / fps, bitDepth, dither)) {
        std::cerr << "Error initializing GIF writer" << std::endl;
        return false;
    }

    // Capture frames and add to GIF
    cv::Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty())
            break;

        uint8_t* rgb = new uint8_t[frame_width * frame_height * 3];
        MatToRGB(frame, rgb);
        if (!GifWriteFrame(&gifWriter, rgb, frame_width, frame_height, 100 / fps, bitDepth, dither)) {
            std::cerr << "Error writing GIF frame" << std::endl;
            delete[] rgb;
            return false;
        }
        delete[] rgb;
    }

    // Finalize the GIF
    GifEnd(&gifWriter);

    // Release video capture
    cap.release();

    std::cout << "GIF created successfully" << std::endl;
    return true;
}
