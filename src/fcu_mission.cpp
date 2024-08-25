#include <ros/ros.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <geometry_msgs/InertiaStamped.h>
#include <std_msgs/Int16.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_broadcaster.h>


static geometry_msgs::InertiaStamped mission_001;
static ros::Publisher mission_pub_001;
static float yaw=0.0f;
static float px=0.0f, py=0.0f, pz=0.0f;
static float vx=0.0f, vy=0.0f, vz=0.0f;
static float ax=0.0f, ay=0.0f, az=0.0f;


void cmdHandler(const std_msgs::Int16::ConstPtr& cmd){
  switch(cmd->data){
    case 5:
        pz+=0.25;
        break;
    case 6:
        pz-=0.25;
        break;
    case 7:
        py+=0.25;
        break;
    case 8:
        py-=0.25;
        break;
    case 9:
        px+=0.25;
        break;
    case 10:
        px-=0.25; 
        break;
    case 11:
        yaw+=0.2;
        break;
    case 12:
        yaw-=0.2;
        break;
    case 13:
        px=0.0f;
        py=0.0f;
        yaw=0.0f;
        break;
    default:
        break;
  }
}


void execute_mission_001(void){
  mission_001.header.frame_id = "mission_001";
  mission_001.header.stamp = ros::Time::now();
  mission_001.inertia.m=yaw;//rad
  mission_001.inertia.com.x=px;
  mission_001.inertia.com.y=py;
  mission_001.inertia.com.z=pz;
  mission_001.inertia.ixx=vx;
  mission_001.inertia.ixy=vy;
  mission_001.inertia.ixz=vz;
  mission_001.inertia.iyy=ax;
  mission_001.inertia.iyz=ay;
  mission_001.inertia.izz=az;
  mission_pub_001.publish(mission_001);
}

int main(int argc, char **argv) {

  ros::init(argc, argv, "fcu_mission");
  ros::NodeHandle nh;

  ros::Subscriber comm=nh.subscribe<std_msgs::Int16>("/fcu_bridge/command", 100, cmdHandler);
  mission_pub_001 = nh.advertise<geometry_msgs::InertiaStamped>("/fcu_bridge/mission_001",100);

  ros::Rate loop_rate(10);
  while (ros::ok()) {
    ros::spinOnce();
    static tf::TransformBroadcaster br;
    tf::Transform transform;
    tf::Quaternion q;
    transform.setOrigin(tf::Vector3(0, 0,0));
    q.setRPY(M_PI, 0, 0);
    transform.setRotation(q);
    br.sendTransform(tf::StampedTransform(transform,  ros::Time::now(), "map", "uwb"));
    
    execute_mission_001();

    loop_rate.sleep();
  }

  return 0;
}
