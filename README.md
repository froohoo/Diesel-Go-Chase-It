# Diesel-Go-Chase-It

Sample Video of Performance


![2Wheel](/2Wheel.gif)



In addition to the 2 wheeled differential drive robot, a 4 wheeled robot based loosely off of the MSE6 from Star Wars is also included. The MSE6 uses acustom Ackermann Steering plugin that I developed since the skid steer plugin performance was poor in this application.


![MSE6](/MSE6.png)
![MSE6](/MSE6.gif)


The MSE6 mesh was created with [FreeCad](https://www.freecadweb.org/) and exported as a Collada (.dae) file. For those with parametric modeling experience, its an easy way to add visual flair to your robots. See [this tutorial](http://gazebosim.org/tutorials?tut=guided_i2) for details/walkthrough.

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
