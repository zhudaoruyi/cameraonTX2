# Light on Leopard camera of Jetson TX2
[TOC]
## Project tree
```sh
cameraonTX2
├── solver1
│   └── src
│       ├── gscam
│       ├── jetson_csi_cam
│       ├── image_view
│       └── vision_opencv
├── solver2
│   └── src
│       ├── JetsonOnbardCamera
│       ├── image_view
│       └── vision_opencv
└── README.txt
```
## Environment
- hardware
    * Jetson TX2
    * Leopard camera
- software
    * ubuntu 16.04
    * ROS kinetic
## Solver 1
- [jetson_csi_cam](https://github.com/peter-moran/jetson_csi_cam): main package
- [gscam](https://github.com/ros-drivers/gscam): relyon
- [image_view](https://github.com/ros-perception/image_pipeline/tree/indigo/image_view): image output with terminal window
- [vision_opencv](https://github.com/ros-perception/vision_opencv): relyon
## Solver 2
- [JetsonOnbardCamera](https://github.com/Dengjianping/JetsonOnboardCamera): main package
- [image_view](https://github.com/ros-perception/image_pipeline/tree/indigo/image_view): image output with terminal window
- [vision_opencv](https://github.com/ros-perception/vision_opencv): relyon

## Build
Build either solver1 or solver2 as below,
```sh
git clone https://github.com/zhudaoruyi/cameraonTX2.git
mkdir catkin_ws
cd catkin_ws
cp ../cameraonTX2/solver1/src .
catkin_make
source devel/setup.bash
```
