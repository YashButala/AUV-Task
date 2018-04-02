#include<ros/ros.h>
#include<std_msgs/Int16.h>
int main(int argc, char** argv)
{
	ros :: init (argc,argv,"count");
	ros :: NodeHandle nh;
	ros :: Publisher counter_pub =nh.advertise<std_msgs::Int16>("counter",100);
		std_msgs::Int16 n;
	n.data=atoi(argv[1]);
	if(n.data<2||n.data>14)
	{
		ROS_INFO("\nInvalid entry\n Rerun the program");
		return 0;	
	}
	ros::Rate poll_rate(100);
	while(counter_pub.getNumSubscribers() == 0)
    poll_rate.sleep();
	ROS_INFO("Sum of pips: %d", n.data);
	counter_pub.publish(n);
	ros::spinOnce();

	return 0;
}
