#include <ros/ros.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <geometry_msgs/InertiaStamped.h>
#include <std_msgs/Int16.h>




void missionHandler(const geometry_msgs::InertiaStamped::ConstPtr& mission){
    float yaw=0.0f, yaw_rate=0.0f;
    float px=0.0f, py=0.0f, pz=0.0f;
    float vx=0.0f, vy=0.0f, vz=0.0f;
    float ax=0.0f, ay=0.0f, az=0.0f;
    yaw=mission->inertia.m;
    px=mission->inertia.com.x;
    py=mission->inertia.com.y;
    pz=mission->inertia.com.z;
    vx=mission->inertia.ixx;
    vy=mission->inertia.ixy;
    vz=mission->inertia.ixz;
    ax=mission->inertia.iyy;
    ay=mission->inertia.iyz;
    az=mission->inertia.izz;

    std::cout<<"-----------mission----------"<<std::endl;
    std::cout<<"x:"<<px<<" y:"<<py<<" z:"<<pz<<std::endl;
    std::cout<<"yaw:"<<yaw<<std::endl;

}
int main(int argc, char** argv)
{
  ros::init(argc, argv, "mission_sub");
  ros::NodeHandle nh;

  ros::Subscriber mission=nh.subscribe<geometry_msgs::InertiaStamped>("/fcu_bridge/mission_001", 100, missionHandler);

  ros::spin();

  return 0;
}