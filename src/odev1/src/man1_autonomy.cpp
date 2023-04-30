#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"
#include <ros/console.h>
ros::Publisher cmd_vel_pub;
geometry_msgs::Twist cmd_vel;

void laserCallBack(const sensor_msgs::LaserScan::ConstPtr& laser){
	//ASAGIDA BULUNAN IF KOMUTU ORNEK OLARAK VERILMISTIR. SIZIN BURAYI DEGISTIRMENIZ BEKLENMEKTEDIR
	//BURDAN SONRASINI DEGISTIR
	if(laser->ranges[540] > 0.60 && laser->ranges[360] > 0.60 && laser->ranges[720] > 0.60 && laser->ranges[1000] > 0.45){
        ROS_DEBUG("düz git");
		cmd_vel.linear.x = 1;
		cmd_vel.angular.z = 0.0;
	}

    else if(laser->ranges[360] <= 0.60 ){
        ROS_DEBUG("sola dön");
		cmd_vel.linear.x = 0.1;
		cmd_vel.angular.z = 2.0;
    }

    else if(laser->ranges[720] <= 0.60){
        ROS_DEBUG("saga dön");
        cmd_vel.linear.x = 0.1;
        cmd_vel.angular.z = -2.0;
    }

    else if (laser->ranges[1000] <= 0.45){
        ROS_DEBUG("saga dön");
        cmd_vel.linear.x = 0.3;
        cmd_vel.angular.z = -2.0;
    }
    else if (laser->ranges[80] <= 0.45){
        ROS_DEBUG("sola dön");
        cmd_vel.linear.x = 0.3;
        cmd_vel.angular.z = 2.0;
    }
    else if(laser->ranges[360] < 0.60 && laser->ranges[720] < 0.60 && laser->ranges[540] < 0.60){
        ROS_DEBUG("hepsi küçük sola dön");
        cmd_vel.linear.x = 0.0;
        cmd_vel.angular.z = 0.90;
    }
    else {
        cmd_vel.linear.x = 0.0;
        cmd_vel.angular.z = 0.90;
    }

	cmd_vel_pub.publish(cmd_vel);
}

int main(int argc, char **argv){
	ros::init(argc, argv, "man1_autonomy");
	ros::NodeHandle nh;

	cmd_vel.linear.y = 0.0;
	cmd_vel.linear.z = 0.0;
	cmd_vel.angular.x = 0.0;
	cmd_vel.angular.y = 0.0;

	ros::Subscriber laser_sub = nh.subscribe("/rtg/hokuyo", 1000, laserCallBack);
	cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/rtg/cmd_vel", 1000);

	ros::spin();

	return 0;
}
