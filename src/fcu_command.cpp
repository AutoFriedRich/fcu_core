#include <ros/ros.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <std_msgs/Int16.h>

static char buf[16] = {0};
static std_msgs::Int16 cmd;

int main(int argc, char **argv) {

  ros::init(argc, argv, "fcu_command");
  ros::NodeHandle nh;
  ros::Publisher command = nh.advertise<std_msgs::Int16>("/fcu_bridge/command",100);

  while (ros::ok()) {
    // 获取从键盘输入的数据
    printf("请输入指令：\n");
    ssize_t size = read(STDIN_FILENO, buf, sizeof(buf));
    if(size>0){
      if(size!=2){
        printf("指令错误！\n");
        continue;
      }
    }else{
      printf("禁用指令\n");
      ros::shutdown();
      return 0;
    }
    switch(buf[0]){
      case '1':
        printf("解锁\n");
        cmd.data=1;
        command.publish(cmd);
        break;
      case '2':
        printf("锁定\n");
        cmd.data=2;
        command.publish(cmd);
        break;
      case 't':
        printf("起飞\n");
        cmd.data=3;
        command.publish(cmd);
        break;
      case 'l':
        printf("降落\n");
        cmd.data=4;
        command.publish(cmd);
        break;

      case 'q':
        printf("Z轴上升\n");
        cmd.data=5;
        command.publish(cmd);
        break;
      case 'e':
        printf("Z轴下降\n");
        cmd.data=6;
        command.publish(cmd);
        break;
      case 'w':
        printf("Y轴上升\n");
        cmd.data=7;
        command.publish(cmd);
        break;
      case 's':
        printf("Y轴下降\n");
        cmd.data=8;
        command.publish(cmd);
        break;
      case 'a':
        printf("X轴上升\n");
        cmd.data=9;
        command.publish(cmd);
        break;
      case 'd':
        printf("X轴下降\n");
        cmd.data=10;
        command.publish(cmd);
        break;
      case 'z':
        printf("yaw轴增加\n");
        cmd.data=11;
        command.publish(cmd);
        break;
      case 'c':
        printf("yaw轴减少\n");
        cmd.data=12;
        command.publish(cmd);
        break;
      case 'x':
        printf("归位\n");
        cmd.data=13;
        command.publish(cmd);
        break;
      default:
        printf("非法指令！\n");
        break;
    }
  }

  return 0;
}

/**
*重新map一下
* 1:解锁 2:锁定 t:起飞 l:降落
* q:Z轴上升 e:Z轴下降 w:Y轴上升 s:Y轴下降 a:X轴上升 d:X轴下降
* z:yaw轴增加 c:yaw轴减少 
* x:归位 将 x 和 y 都至于 0 位置
*/