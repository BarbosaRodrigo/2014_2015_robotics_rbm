/**
 * @file    obstacle_avoidance.cpp
 * @brief   A template for webots projects.
 *
 * @author  Rodrigo Barbosa Moreno <100072651@alumnos.uc3m.es>
 * @date    2014-11
 */

#include <iostream>

#include <cmath>
#include <webots/DifferentialWheels.hpp>

using namespace std;
using namespace webots;

#define NUM_DISTANCE_SENSOR 4
#define DISTANCE_LIMIT      100
#define MAX_SPEED           25
#define DESIRED_ANGLE   45

class MyRobot : public DifferentialWheels {
    private:
        int _time_step;

        Compass * _my_compass;
       
        DistanceSensor * _distance_sensor[NUM_DISTANCE_SENSOR];
        double _left_speed, _right_speed;

        enum Mode {
            STOP,
            FORWARD,
            TURN_LEFT,
            TURN_RIGHT,
            BACKWARDS
        };

        Mode _mode;

    public:
        // You may need to define your private methods or variables, like
        //  Constructors, helper functions, etc.

        /**
         * @brief Empty constructor of the class.
         */
        MyRobot();
        
        
        /**
         * @brief Destructor of the class.
         */
        ~MyRobot();
 
       
        /**
         * @brief User defined function for initializing and running the template class.
         */
        void run();
         double convert_bearing_to_degrees(const double* in_vector);
};
