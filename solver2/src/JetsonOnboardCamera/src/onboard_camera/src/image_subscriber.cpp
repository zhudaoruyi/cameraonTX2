#include <iostream>
#include <string>

#include <boost/filesystem.hpp>

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

namespace fs = boost::filesystem;


void callback(const sensor_msgs::ImageConstPtr & msg)
{
    static int count = 0; // record how many image captured
    
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch(cv_bridge::Exception & e)
    {
        ROS_ERROR("cv_bridge exception is: %s", e.what());
        return;
    }
    fs::path p = fs::current_path();
    
    auto pic_name = std::to_string(count) + ".jpg";
    fs::path file_name = pic_name;
    fs::path full_path = p / file_name;
    
    if (count % 5 == 0) // when count = 0, 5, 10..., save the picture
    {
        cv::imwrite(full_path.string(), cv_ptr->image);
        std::string f = "image saved as here: " + full_path.string();
        ROS_INFO("%s", f.c_str());
    }
    
    count++;
}


int main(int argc, char **argv)
{
    std::string node_name = "onboard_camera_image_receiver_node";
    ros::init(argc, argv, node_name);
    
    ros::NodeHandle handle;
    image_transport::ImageTransport it(handle);
    auto image_sub = it.subscribe("/camera/onboard/image", 1, callback);
    // image_transport::Subscriber image_sub = it.subscribe("/camera/onboard/image", 1, callback);
    
    ros::spin();
    
    return 0;
}