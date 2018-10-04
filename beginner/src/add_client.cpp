#include <ros/ros.h>
#include <actionlib/client/service_client.h>
#include <actionlib/TwoIntsAction.h>

int main(int argc, char ** argv)
{
  ros::init(argc, argv, "add_two_ints_client");
  if (argc != 3) {
    ROS_INFO_NAMED("actionlib", "Usage: add_two_ints_client X Y");
    return 1;
  }

  ros::NodeHandle n;
  actionlib::ServiceClient client = actionlib::serviceClient<actionlib::TwoIntsAction>(n,
      "add_two_ints");
  client.waitForServer();
  actionlib::TwoIntsGoal req;
  actionlib::TwoIntsResult resp;

  req.a = atoi(argv[1]);
  req.b = atoi(argv[2]);

  if (client.call(req, resp)) {
    ROS_INFO_NAMED("actionlib", "Sum: %ld", (int64_t)resp.sum);
    return 1;
  }

  return 0;
}
