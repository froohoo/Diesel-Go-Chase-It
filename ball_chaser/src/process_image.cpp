#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>
#include <string>
#include <cmath>

//Define a global client that can request services
ros::ServiceClient client;

//Define a couple of Globals. 
//MAXSPEED and MAXTURN are read from teh parameter server
//directionGuess persists between calls in case ball goes out of frame
float MAXSPEED, MAXTURN;
float directionGuess = -1;
// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    ball_chaser::DriveToTarget drive_cmd;
    drive_cmd.request.linear_x = lin_x;
    drive_cmd.request.angular_z = ang_z;
    
    if (!client.call(drive_cmd)){
        ROS_ERROR("Failed to execute drive command");
    }
}

//This callback/ function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img )
{
    const int white_pixel_val = 3 * 255;
    int white_moment = 0;
    int white_pixels = 0;
    int total_pixels = 0;
    int sumChannels = 0;
    int pixelStart = 0;
    const int totalPixels = img.height * img.width;
    const float goalFill = .40; //fraction of the screen filled white ball @ goal
    const char *encoding = img.encoding.c_str();
    float awm = 0;
    float x, z;
    // process one row at at time (i)
    for(int i=0; i<img.height; ++i){
        // process one pixel in the row at a time. Image encoding is rgb8
        // so each pixel is 3 bytes; one byte each for red green blue channel.
        // white pixels should be the only ones where the channels add up to 
        // be 3 * 255.

        // Process each column/pixel (3 bytes so step = 3)
        for (int j=0; j<img.step; j+=3){
            sumChannels = 0;
            pixelStart = i * img.step + j;
            // Add up all the channels for that pixel
            for (int channel=0;channel < 3;channel++){
                sumChannels += img.data[pixelStart + channel];
            }
            // Moment is a bit of an abstraction here, but I like the 
            // to think of this problem as the inertia of the white 
            // pixels about the center of the image 
            if (sumChannels == white_pixel_val){
                ++white_pixels;
                white_moment = white_moment + j - img.step/2;
                awm = white_moment/white_pixels;
            }
        }
    }
    // Print the metadata from the image message:
    ROS_INFO("%d white pixels found. awm is %1.2f\n", (int)white_pixels,awm);
    ROS_INFO("\nImage metadata:\n Height %d, Width %d,\n Encoding %s,\
           \n Step: %d, Big Endian?: %d\n", (int)img.height, (int)img.width,
          encoding, img.step, img.is_bigendian); 

    if (white_pixels == 0) { // no pixels found turn until you find some.
        x = 0.0;
        z = directionGuess * MAXTURN;
    }  
    else {
        x = MAXSPEED * std::pow(1 - white_pixels/(totalPixels*goalFill), 6.0);
        z = MAXTURN * std::pow(std::abs(2.0 * awm / img.step),.9);
        if (awm < 0){   //awm negative, ball is left, positive turn
            directionGuess = 1.0; //set guess in case we lose sight of ball 
        }
        else if (awm > 0) { //awm positive, ball is right, negative turn
            directionGuess = -1.0;
            z *= -1;
        }
    }
    
    
    
    drive_robot(x,z);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;
    
    if (n.getParam("/MAXSPEED", MAXSPEED) && n.getParam("/MAXTURN", MAXTURN)){
        ROS_INFO("Parameter Server Returned %f / %f for MAXSPEED, MAXTURN",(float)MAXSPEED, (float)MAXTURN);
    }
    else {
        MAXSPEED = .1;
        MAXTURN = 1.0;
        ROS_INFO("MAXSPEED, MAXTURN not set. Using Defaults %f / %f", (float)MAXSPEED, (float)MAXTURN);
    }
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    ros::spin();
    


    return 0;
}

