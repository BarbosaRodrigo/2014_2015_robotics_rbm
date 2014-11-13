/**
 * @file    wall_detector.cpp
 * @brief   A template for webots projects.
 *
 * @author  Rodrigo Barbosa Moreno <100072651@alumnos.uc3m.es>
 * @date    2014-11
 */

#include "MyRobot.h"


/**
 * @brief Main program.
 */
int main(int argc, char **argv)
{
    MyRobot* my_robot = new MyRobot();

    my_robot->run();

    delete my_robot;

    return 0;
}
