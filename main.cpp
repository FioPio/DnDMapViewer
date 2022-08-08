#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>

enum KeyCodes
{
    KEY_ESC = 27,
    KEY_Q   = 'q',
    KEY_P   = 'p',
    KEY_E   = 'e',
    KEY_C   = 'c',
    KEY_U   = 'u',
    KEY_H   = 'h',
    KEY_S   = 's'
};

enum ViwerState
{
    STATE_ADD_PLAYERS,
    STATE_ADD_ENEMIES,
    STATE_STANDBY, 
    STATE_HIDE, 
    STATE_SHOW
};


void CallBackFunc(int event, int x, int y, int flags, void* userdata);
cv::Mat scaleImage(cv::Mat image, float scale);

cv::Mat original_image;
cv::Mat players_view;
cv::Mat image_mask;
char state;
bool players_view_is_alive;
bool players_view_can_be_shown;

int main(int argc, char** argv )
{
    char key ='0';
    players_view_is_alive = false;
    players_view_can_be_shown = false;
    state = STATE_HIDE;
    if ( argc != 2 )
    {
        printf("Usage: %s <Image_Path>\n",argv[0]);
        return -1;
    }
    state = STATE_STANDBY;

    cv::Mat master_view;
    original_image = cv::imread( argv[1], 1 );

    if ( !original_image.data )
    {
        printf("No original_image data \n");
        return -2;
    }
    namedWindow("Display Image", cv::WINDOW_AUTOSIZE );

    //set the callback function for any mouse event
    cv::setMouseCallback("Display Image", CallBackFunc, NULL);

     original_image = scaleImage(original_image,0.1);
    
    image_mask=cv::Mat(original_image.rows, original_image.cols, CV_8UC3, cv::Scalar(0, 0, 0));
    players_view=cv::Mat(original_image.rows, original_image.cols, CV_8UC3, cv::Scalar(0, 0, 0));
    
    
    while(key!=KEY_ESC && key!=KEY_Q)
    {
        cv::imshow("Display Image", original_image);
        key=cv::waitKey(100);
        switch(key)
        {
            case KEY_C: // Clean
                image_mask=cv::Mat(original_image.rows, original_image.cols, CV_8UC3, cv::Scalar(0, 0, 0));
                players_view=cv::Mat(original_image.rows, original_image.cols, CV_8UC3, cv::Scalar(0, 0, 0));
                if ( players_view_is_alive )
                {
                    cv::imshow("Player's view", players_view);
                }
                
                
                break;
            
            case KEY_H: // Hide Player's View
                if ( players_view_is_alive )
                {
                    cv::destroyWindow("Player's view");
                    players_view_is_alive = false;
                }
                players_view_can_be_shown = false;
                break;
                
            case KEY_P: // Add players
                state = STATE_ADD_PLAYERS;
                break;
            
            case KEY_S:                                     // Show
                cv::imshow("Player's view", players_view);
                players_view_is_alive = true;
                players_view_can_be_shown = true;
                break;
                
        }
    }


    //original_image.copyTo(players_view);
    cv::destroyAllWindows();

    return 0;
}


// Callback that shows the mouse position in the image
void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
    if  ( event == cv::EVENT_LBUTTONDOWN )
    {
        std::cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
        //original_image.copyTo(players_view);
        if ( state == STATE_ADD_PLAYERS )
        {
            cv::Point center(x, y);//Declaring the center point
            int radius = 50; //Declaring the radius
            cv::Scalar circle_color(255, 255, 255);//Color of the circle
            int thickness = -radius;//2;//thickens of the line
        
            cv::circle(image_mask, center,radius, circle_color, thickness);//Using circle()function to draw the line//
        
            original_image.copyTo(players_view,image_mask);
            if ( players_view_can_be_shown)
            {
                cv::namedWindow("Player's view");//Declaring a window to show the circle
                cv::imshow("Player's view", players_view);//Showing the circle//
                //cv::waitKey(0);//Waiting for Keystroke//
                players_view_is_alive = true;
            }
        }

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
