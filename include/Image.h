#include <opencv2/opencv.hpp>


namespace Image
{
    // Scales the image 
    cv::Mat scaleImage(cv::Mat image, float scale);
    
    // Creates a one color image 
    cv::Mat generateColoredImage(int image_rows, int image_columns, cv::Scalar image_color);
    
}
