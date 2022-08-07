#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>


void CallBackFunc(int event, int x, int y, int flags, void* userdata);
cv::Mat scaleImage(cv::Mat image, float scale);

cv::Mat master_view;
cv::Mat players_view;


int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("Usage: %s <Image_Path>\n",argv[0]);
        return -1;
    }

    master_view = cv::imread( argv[1], 1 );

    if ( !master_view.data )
    {
        printf("No master_view data \n");
        return -2;
    }
    namedWindow("Display Image", cv::WINDOW_AUTOSIZE );

    //set the callback function for any mouse event
    cv::setMouseCallback("Display Image", CallBackFunc, NULL);

    master_view = scaleImage(master_view,0.1);
    cv::imshow("Display Image", master_view);
    cv::waitKey(0);


    master_view.copyTo(players_view);

    return 0;
}


// Callback that shows the mouse position in the image
void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
     if  ( event == cv::EVENT_LBUTTONDOWN )
     {
          std::cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
          master_view.copyTo(players_view);

          cv::Point center(x, y);//Declaring the center point
          int radius = 50; //Declaring the radius
          cv::Scalar circle_color(255, 255, 255);//Color of the circle
          int thickness = -radius;//2;//thickens of the line
          cv::namedWindow("Player's view");//Declaring a window to show the circle
          cv::circle(players_view, center,radius, circle_color, thickness);//Using circle()function to draw the line//
          cv::imshow("Player's view", players_view);//Showing the circle//
          cv::waitKey(0);//Waiting for Keystroke//


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
