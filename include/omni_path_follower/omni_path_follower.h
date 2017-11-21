/** include the libraries you need in your planner here */
/** for global path planner interface */
#include <ros/ros.h>
#include <costmap_2d/costmap_2d_ros.h>
#include <costmap_2d/costmap_2d.h>
#include <nav_core/base_local_planner.h>
#include <geometry_msgs/PoseStamped.h>
#include <angles/angles.h>
#include <base_local_planner/world_model.h>
#include <base_local_planner/costmap_model.h>
#include <Eigen/Dense>

using std::string;

#ifndef GLOBAL_PLANNER_CPP
#define GLOBAL_PLANNER_CPP

namespace omni_path_follower
{

class PathFollower : public nav_core::BaseLocalPlanner
{
public:

  PathFollower();

  /** overridden classes from interface nav_core::BaseGlobalPlanner **/
  void initialize(std::string name, tf::TransformListener *tf, costmap_2d::Costmap2DROS *costmap_ros);
  bool computeVelocityCommands(geometry_msgs::Twist &cmd_vel);
  bool isGoalReached();
  bool setPlan(const std::vector< geometry_msgs::PoseStamped > &plan);

private:
  double in_path_vel_;
  double to_path_k_;
  double angle_k_;
  double goal_threshold_;
  bool rotate_to_path_;
  bool rotate_at_start_;

  geometry_msgs::Pose last_waypoint_;
  geometry_msgs::Pose next_waypoint_;
  int path_length_;
  int path_index_;

  std::vector<geometry_msgs::PoseStamped> global_plan_;
  geometry_msgs::PoseStamped goal_;
  tf::TransformListener* tfl_;
  costmap_2d::Costmap2DROS* costmap_ros_;

  bool initialized_;
  bool goal_reached_;
};

} //namespace omni_path_follower

#endif
