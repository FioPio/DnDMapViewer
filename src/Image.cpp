#include "Image.h"

#include <opencv2/opencv.hpp>


cv::Mat Image::scaleImage(cv::Mat image, float scale)
{
    std::cout << "Original Height and Width: " << image.rows << " x " << image.cols << std::endl;
    cv::Mat scaled_image;
    int new_width  =  scale * image.cols;
    int new_height =  scale * image.rows;
    std::cout << "Scaled Height and Width: " << new_height << " x " << new_width << std::endl;
    cv::resize(image, scaled_image, cv::Size(new_width, new_height), cv::INTER_LINEAR);
    return scaled_image;
}
