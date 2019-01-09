cmake_minimum_required(VERSION 2.8.3)
project(onboard_camera CXX)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  message_generation
  roscpp
  std_msgs
)

## Find opencv package
find_package(OpenCV 3.4 REQUIRED)

catkin_package(
   CATKIN_DEPENDS roscpp std_msgs
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

## inlcude opencv libs directory
link_directories( 
    ${OpenCV_LIBRARY_DIRS} 
)

add_executable(image_publisher src/image_publisher.cpp)
target_link_libraries(image_publisher
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)

# add_executable(image_subscriber src/image_subscriber.cpp)
# target_link_libraries(image_subscriber
  # ${catkin_LIBRARIES}
  # ${OpenCV_LIBRARIES}
# )