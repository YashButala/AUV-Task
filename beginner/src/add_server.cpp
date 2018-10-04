#include <ros/ros.h>
#include <actionlib/server/service_server.h>
#include <actionlib/TwoIntsAction.h>

bool add(const actionlib::TwoIntsGoal & req, actionlib::TwoIntsResult & res)
{
  res.sum = req.a + req.b;
  ROS_INFO_NAMED("actionlib", "request: x=%ld, y=%ld", (int64_t)req.a, (int64_t)req.b);
  ROS_INFO_NAMED("actionlib", "   sending back response: [%ld]", (int64_t)res.sum);
  return true;
}

int main(int argc, char ** argv)
{
  ros::init(argc, argv, "add_two_ints_server");
  ros::NodeHandle n;

  actionlib::ServiceServer service = actionlib::advertiseService<actionlib::TwoIntsAction>(n,
      "add_two_ints",
      boost::bind(add, _1, _2));

  ros::spin();

  return 0;
}
