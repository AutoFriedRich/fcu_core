## 1. Prerequisites
### 1.1 **Ubuntu** and **ROS**
Ubuntu 64-bit 18.04.
ROS Melodic. [ROS Installation](http://wiki.ros.org/ROS/Installation)

### 1.2. **serial**
sudo apt-get install ros-melodic-serial

### 1.3. **eigen**
sudo apt-get install libeigen3-dev

## 2. Build
在工作空间：catkin_make

## 3. Source
source devel/setup.bash

## 4. 如果用到串口需要配置权限
sudo chmod 777 /dev/ttyACM0

## 5. 运行node
 roslaunch fcu_core fcu_core.launch

# 用于调试的singleuav-branch

- 切换分支
  
  `git checkout singleuav-branch`

- 在fcu_bridge_001中修改ip地址

- 连接飞机
  
  `roslaunch fcu_core fcu_one.launch`

- 查看当前定位信息
 
  `rosrun fcu_core mission_sub`


- Command
  
  重新map一下
  * 1:解锁 2:锁定 t:起飞 l:降落
  * q:Z轴上升 e:Z轴下降 w:Y轴上升 s:Y轴下降 a:X轴上升 d:X轴下降
  * z:yaw轴增加 c:yaw轴减少 
  * x:归位 将 x 和 y 都至于 0 位置
