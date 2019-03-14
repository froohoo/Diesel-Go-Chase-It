# Diesel-Go-Chase-It
Beta test for RoboND content

Sample Video of Performance
https://youtu.be/nNQRK6SXKsg



In addition to the 2 wheeled differential drive robot, a 4 wheeled skid steer robot based loosely off of the MSE6 from Star Wars is also included. 
![MSE6](/MSE6.png)

The MSE6 mesh was created with [FreeCad](https://www.freecadweb.org/) and exported as a Collada (.dae) file. For those with parametric modeling experience, its an easy way to add visual flair to your robots. 

Installation:
1. run  `mkdir catkin_ws/src -p`
2. copy /ball_chaser and /my_robot to catkin_ws/src/
3. cd catkin_ws
4. run `catkin_make`
5. run `source catkin_make/devel/setup.bash`
6. run `roslaunch my_robot world.launch`
7. 
       * To launch the 2 wheeled robot run:`roslaunch my_robot world.launch`
       * To launch the MSE6 run: `roslaunch my_robot world.launch MSE6:=true` 
