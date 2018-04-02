#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <actionlib_tutorials/TaskAction.h>
#include<math.h>

class TaskAction
{
protected:

  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<actionlib_tutorials::TaskAction> as_;
  std::string action_name_;
  actionlib_tutorials::TaskFeedback feedback_;
  actionlib_tutorials::TaskResult result_;

public:

  TaskAction(std::string name) :
    as_(nh_, name, boost::bind(&TaskAction::executeCB, this, _1), false),
    action_name_(name)
  {
    as_.start();
  }

  ~TaskAction(void)
  {
  }

  void executeCB(const actionlib_tutorials::TaskGoalConstPtr &goal)
  {
    ros::Rate r(1);
    bool success = true;
    feedback_.sequence.clear();
    feedback_.sequence.push_back(goal->start);
    ROS_INFO("%s: Executing, creating task sequence of order %f with seeds %f, %f", action_name_.c_str(), goal->start, feedback_.sequence[0], feedback_.sequence[1]);
    for(int i=0; i<=10; i++)
    {
      if (as_.isPreemptRequested() || !ros::ok())
      {
        ROS_INFO("%s: Preempted", action_name_.c_str());
        // set the action state to preempted
        as_.setPreempted();
        success = false;
        break;
      }
      float k=feedback_.sequence[i] ;
// using nr method     	
      feedback_.sequence.push_back((2*k*k*k+3)/(3*k*k+5) );
      r.sleep();
    }

    if(success)
    {
      result_.sequence = feedback_.sequence;
      ROS_INFO("%s: Succeeded", action_name_.c_str());
      as_.setSucceeded(result_);
    }
  }


};


int main(int argc, char** argv)
{
  ros::init(argc, argv, "task");

  TaskAction task("task");
  ros::spin();

  return 0;
}

