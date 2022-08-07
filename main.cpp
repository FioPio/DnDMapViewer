#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>

void CallBackFunc(int event, int x, int y, int flags, void* userdata);
cv::Mat scaleImage(cv::Mat image, float scale);

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    cv::Mat master_view;
    master_view = cv::imread( argv[1], 1 );
    if ( !master_view.data )
    {
        printf("No master_view data \n");
        return -2;
    }
    namedWindow("Display Image", cv::WINDOW_AUTOSIZE );

       //set the callback function for any mouse event
     cv::setMouseCallback("Display Image", CallBackFunc, NULL);

    imshow("Display Image", scaleImage(master_view,0.25));
    cv::waitKey(0);

    cv::Mat players_view;

    master_view.copyTo(players_view);

    return 0;
}


// Callback that shows the mouse position in the image
void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
     if  ( event == cv::EVENT_LBUTTONDOWN )
     {
          std::cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
     }
     else if  ( event == cv::EVENT_RBUTTONDOWN )
     {
          std::cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
     }
     else if  ( event == cv::EVENT_MBUTTONDOWN )
     {
          std::cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
     }
     else if ( event == cv::EVENT_MOUSEMOVE )
     {
          std::cout << "Mouse move over the window - position (" << x << ", " << y << ")" << std::endl;

     }
}

cv::Mat scaleImage(cv::Mat image, float scale)
{
    std::cout << "Original Height and Width: " << image.rows << " x " << image.cols << std::endl;
    cv::Mat scaled_image;
    int new_width  =  scale * image.cols;
    int new_height =  scale * image.rows;
    std::cout << "Scaled Height and Width: " << new_height << " x " << new_width << std::endl;
    cv::resize(image, scaled_image, cv::Size(new_width, new_height), cv::INTER_LINEAR);
    return scaled_image;
}
