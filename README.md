# Diesel-Go-Chase-It
Beta test for RoboND content

Sample Video of Performance
https://youtu.be/nNQRK6SXKsg



In addition to the 2 wheeled differential drive robot, a 4 wheeled skid steer robot based loosely off of the MSE6 from Star Wars is also included. 
![MSE6](/MSE6.png)

Installation:
1. run  `mkdir catkin_ws/src -p`
2. copy /ball_chaser and /my_robot to catkin_ws/src/ 
3. run `catkin_make`
4. run `source catkin_make/devel/setup.bash`
5. run `roslaunch my_robot world.launch`
6. run `roslaunch ball_chaser ball_chaser.launch`

To launch the 2 wheeled robot run:`roslaunch my_robot world.launch`

To launch the MSE6 run: `roslaunch my_robot world.launch MSE6:=true` 
