#include <iostream>
#include <string>

// #include <boost/filesystem.hpp>

#include <ros/ros.h>
#include <std_msgs/String.h>

#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
// #include <camera_info_manager/camera_info_manager.h>
// #include <sensor_msgs/Image.h>
// #include <sensor_msgs/CameraInfo.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


std::string get_camera_config(const int & width, const int & height, const int & fps) 
{
    std::string pipe =  "nvcamerasrc ! video/x-raw(memory:NVMM), width=(int)" + std::to_string(width) + \
                        ", height=(int)" + std::to_string(height) + ", format=(string)I420, framerate=(fraction)" + \
                        std::to_string(fps) +"/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! \
                        videoconvert ! video/x-raw, format=(string)BGR ! appsink";
    return pipe;
}


int main(int argc, char **argv)
{
    // init rosnode
    std::string node_name = "onboard_camera_image_sender_node";
    ros::init(argc, argv, node_name);
    
    ros::NodeHandle node;
    image_transport::ImageTransport it(node);
    
    int width, height, fps;
    width = std::stoi(argv[1]), height = std::stoi(argv[2]), fps = std::stoi(argv[3]);
    
    // image_transport::Publisher image_pub = it.advertise("/camera/onboard/image", 1);
    auto image_pub = it.advertise("/camera/onboard/image", 1); // c++ 11 style
    ros::Rate loop_rate(fps);
    
    // camera operation
    cv::VideoCapture cap(get_camera_config(width, height, fps));
    if (!cap.isOpened())
    {
        ROS_ERROR("Cannot open onboard camera!");
        return -1;
    }
    
    cv::Mat frame;
    auto bridge = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame); // a bridge ros style image
    sensor_msgs::ImagePtr ros_image; // ros style image msgs
    
    while(ros::ok())
    {
        cap.read(frame); // read frame from camera
        
        bridge.image = frame; 
        ros_image = bridge.toImageMsg(); // convert to ros image
        
        image_pub.publish(ros_image); // send image
        ros::spinOnce();
        loop_rate.sleep();
    }
    
}
