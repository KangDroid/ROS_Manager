#!/bin/bash
source /opt/ros/melodic/setup.bash
source ~/catkin_ws/devel/setup.bash
source ~/catkin_ws/install_isolated/setup.bash
#export ROS_MASTER_URI=http://192.168.0.17:11311
#export ROS_HOSTNAME=192.168.0.17
export ROS_MASTER_URI=http://localhost:11311
export ROS_HOSTNAME=localhost
export TURTLEBOT3_MODEL=burger


roscore
