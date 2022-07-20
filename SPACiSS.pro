# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = SPACiSS

QT = core gui widgets

HEADERS = \
   $$PWD/2ndparty/spencer_tracking_rviz_plugin/src/visuals/covariance_visual.h \
   $$PWD/2ndparty/spencer_tracking_rviz_plugin/src/visuals/mesh_node.h \
   $$PWD/2ndparty/spencer_tracking_rviz_plugin/src/visuals/person_visual.h \
   $$PWD/2ndparty/spencer_tracking_rviz_plugin/src/visuals/text_node.h \
   $$PWD/2ndparty/spencer_tracking_rviz_plugin/src/additional_topic_subscriber.h \
   $$PWD/2ndparty/spencer_tracking_rviz_plugin/src/detected_persons_display.h \
   $$PWD/2ndparty/spencer_tracking_rviz_plugin/src/human_attributes_display.h \
   $$PWD/2ndparty/spencer_tracking_rviz_plugin/src/person_display_common.h \
   $$PWD/2ndparty/spencer_tracking_rviz_plugin/src/social_activities_display.h \
   $$PWD/2ndparty/spencer_tracking_rviz_plugin/src/social_relations_display.h \
   $$PWD/2ndparty/spencer_tracking_rviz_plugin/src/tracked_groups_display.h \
   $$PWD/2ndparty/spencer_tracking_rviz_plugin/src/tracked_persons_cache.h \
   $$PWD/2ndparty/spencer_tracking_rviz_plugin/src/tracked_persons_display.h \
   $$PWD/3rdparty/libpedsim/include/pedsim/ped_agent.h \
   $$PWD/3rdparty/libpedsim/include/pedsim/ped_angle.h \
   $$PWD/3rdparty/libpedsim/include/pedsim/ped_includes.h \
   $$PWD/3rdparty/libpedsim/include/pedsim/ped_obstacle.h \
   $$PWD/3rdparty/libpedsim/include/pedsim/ped_scene.h \
   $$PWD/3rdparty/libpedsim/include/pedsim/ped_tree.h \
   $$PWD/3rdparty/libpedsim/include/pedsim/ped_vector.h \
   $$PWD/3rdparty/libpedsim/include/pedsim/ped_waypoint.h \
   $$PWD/pedsim_sensors/include/pedsim_sensors/obstacle_point_cloud.h \
   $$PWD/pedsim_sensors/include/pedsim_sensors/pedsim_sensor.h \
   $$PWD/pedsim_sensors/include/pedsim_sensors/people_point_cloud.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/element/adolescent.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/element/agent.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/element/agentcluster.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/element/agentgroup.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/element/areawaypoint.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/element/attractionarea.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/element/child.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/element/elderly.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/element/obstacle.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/element/oldelderly.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/element/preadolescent.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/element/queueingwaypoint.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/element/scenarioelement.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/element/waitingqueue.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/element/waypoint.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/force/alongwallforce.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/force/force.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/force/groupcoherenceforce.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/force/groupgazeforce.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/force/grouprepulsionforce.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/force/randomforce.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/waypointplanner/groupwaypointplanner.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/waypointplanner/individualwaypointplanner.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/waypointplanner/queueingplanner.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/waypointplanner/shoppingplanner.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/waypointplanner/waypointplanner.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/agentstatemachine.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/config.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/orientationhandler.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/rng.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/scenarioreader.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/scene.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/simulator.h \
   $$PWD/pedsim_simulator/include/pedsim_simulator/utilities.h \
   $$PWD/pedsim_utils/include/pedsim_utils/geometry.h \
   $$PWD/pedsim_visualizer/include/pedsim_visualizer/sim_visualizer.h

SOURCES = \
   $$PWD/2ndparty/spencer_tracking_rviz_plugin/src/visuals/person_visual.cpp \
   $$PWD/2ndparty/spencer_tracking_rviz_plugin/src/detected_persons_display.cpp \
   $$PWD/2ndparty/spencer_tracking_rviz_plugin/src/human_attributes_display.cpp \
   $$PWD/2ndparty/spencer_tracking_rviz_plugin/src/person_display_common.cpp \
   $$PWD/2ndparty/spencer_tracking_rviz_plugin/src/social_activities_display.cpp \
   $$PWD/2ndparty/spencer_tracking_rviz_plugin/src/social_relations_display.cpp \
   $$PWD/2ndparty/spencer_tracking_rviz_plugin/src/tracked_groups_display.cpp \
   $$PWD/2ndparty/spencer_tracking_rviz_plugin/src/tracked_persons_cache.cpp \
   $$PWD/2ndparty/spencer_tracking_rviz_plugin/src/tracked_persons_display.cpp \
   $$PWD/3rdparty/libpedsim/src/ped_agent.cpp \
   $$PWD/3rdparty/libpedsim/src/ped_angle.cpp \
   $$PWD/3rdparty/libpedsim/src/ped_obstacle.cpp \
   $$PWD/3rdparty/libpedsim/src/ped_scene.cpp \
   $$PWD/3rdparty/libpedsim/src/ped_tree.cpp \
   $$PWD/3rdparty/libpedsim/src/ped_vector.cpp \
   $$PWD/3rdparty/libpedsim/src/ped_waypoint.cpp \
   $$PWD/experimental_package/src/timer_node.cpp \
   $$PWD/pedsim_gazebo_plugin/src/actor_poses_plugin.cpp \
   $$PWD/pedsim_sensors/src/pedsim_sensors/obstacle_point_cloud.cpp \
   $$PWD/pedsim_sensors/src/pedsim_sensors/people_point_cloud.cpp \
   $$PWD/pedsim_simulator/src/element/adolescent.cpp \
   $$PWD/pedsim_simulator/src/element/agent.cpp \
   $$PWD/pedsim_simulator/src/element/agentcluster.cpp \
   $$PWD/pedsim_simulator/src/element/agentgroup.cpp \
   $$PWD/pedsim_simulator/src/element/areawaypoint.cpp \
   $$PWD/pedsim_simulator/src/element/attractionarea.cpp \
   $$PWD/pedsim_simulator/src/element/child.cpp \
   $$PWD/pedsim_simulator/src/element/elderly.cpp \
   $$PWD/pedsim_simulator/src/element/obstacle.cpp \
   $$PWD/pedsim_simulator/src/element/oldelderly.cpp \
   $$PWD/pedsim_simulator/src/element/preadolescent.cpp \
   $$PWD/pedsim_simulator/src/element/queueingwaypoint.cpp \
   $$PWD/pedsim_simulator/src/element/scenarioelement.cpp \
   $$PWD/pedsim_simulator/src/element/waitingqueue.cpp \
   $$PWD/pedsim_simulator/src/element/waypoint.cpp \
   $$PWD/pedsim_simulator/src/force/alongwallforce.cpp \
   $$PWD/pedsim_simulator/src/force/force.cpp \
   $$PWD/pedsim_simulator/src/force/groupcoherenceforce.cpp \
   $$PWD/pedsim_simulator/src/force/groupgazeforce.cpp \
   $$PWD/pedsim_simulator/src/force/grouprepulsionforce.cpp \
   $$PWD/pedsim_simulator/src/force/randomforce.cpp \
   $$PWD/pedsim_simulator/src/waypointplanner/groupwaypointplanner.cpp \
   $$PWD/pedsim_simulator/src/waypointplanner/individualwaypointplanner.cpp \
   $$PWD/pedsim_simulator/src/waypointplanner/queueingplanner.cpp \
   $$PWD/pedsim_simulator/src/waypointplanner/shoppingplanner.cpp \
   $$PWD/pedsim_simulator/src/waypointplanner/waypointplanner.cpp \
   $$PWD/pedsim_simulator/src/agentstatemachine.cpp \
   $$PWD/pedsim_simulator/src/config.cpp \
   $$PWD/pedsim_simulator/src/orientationhandler.cpp \
   $$PWD/pedsim_simulator/src/rng.cpp \
   $$PWD/pedsim_simulator/src/scenarioreader.cpp \
   $$PWD/pedsim_simulator/src/scene.cpp \
   $$PWD/pedsim_simulator/src/simulate_diff_drive_robot.cpp \
   $$PWD/pedsim_simulator/src/simulator.cpp \
   $$PWD/pedsim_simulator/src/simulator_node.cpp \
   $$PWD/pedsim_utils/src/pedsim_utils/geometry.cpp \
   $$PWD/pedsim_utils/src/pedsim_utils/pedsim_utils.cpp \
   $$PWD/pedsim_visualizer/src/sim_visualizer.cpp \
   $$PWD/pedsim_visualizer/src/sim_visualizer_node.cpp

INCLUDEPATH = \
    $$PWD/2ndparty/spencer_tracking_rviz_plugin/src \
    $$PWD/2ndparty/spencer_tracking_rviz_plugin/src/visuals \
    $$PWD/3rdparty/libpedsim/include/pedsim \
    $$PWD/pedsim_sensors/include/pedsim_sensors \
    $$PWD/pedsim_simulator/include/pedsim_simulator \
    $$PWD/pedsim_simulator/include/pedsim_simulator/element \
    $$PWD/pedsim_simulator/include/pedsim_simulator/force \
    $$PWD/pedsim_simulator/include/pedsim_simulator/waypointplanner \
    $$PWD/pedsim_utils/include/pedsim_utils \
    $$PWD/pedsim_visualizer/include/pedsim_visualizer

#DEFINES = 

