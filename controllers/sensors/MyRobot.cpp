/**
 * @file    sensors.cpp
 * @brief   A template for webots projects.
 *
 * @author  Rodrigo Barbosa Moreno <100072651@alumnos.uc3m.es>
 * @date    2014-10
 */
#include "MyRobot.h"

//////////////////////////////////////////////

MyRobot::MyRobot() : DifferentialWheels()
{
    _time_step = 64;

    _left_speed = 0;
    _right_speed = 0;

    // Get and enable the compass device
    _my_compass = getCompass("compass");
    _my_compass->enable(_time_step);
    
    _distance_sensor[0] = getDistanceSensor("ds0");
    _distance_sensor[0]->enable(_time_step);
    _distance_sensor[1] = getDistanceSensor("ds15");
    _distance_sensor[1]->enable(_time_step);
}


//////////////////////////////////////////////

MyRobot::~MyRobot()
{
    _my_compass->disable();
    
    for (int i=0; i<NUM_DISTANCE_SENSOR; i++) {
        _distance_sensor[i]->disable();
    }
    
}

//////////////////////////////////////////////

void MyRobot::run()
{
    double compass_angle;
    double ir0_val = 0.0;
    double ir15_val = 0.0;
   
    while (step(_time_step) != -1){
        // Read the sensors
        const double *compass_val = _my_compass->getValues();
        
        // Convert compass bearing vector to angle, in degrees
        compass_angle = convert_bearing_to_degrees(compass_val);
        ir0_val = _distance_sensor[0]->getValue();
        ir15_val = _distance_sensor[1]->getValue();

        // Print sensor values to console
        cout << "Compass angle (degrees): " << compass_angle << endl;
cout << "ir0_val(mm): " << ir0_val << endl;
        // Simple bang-bang control
        
               if (ir0_val>0){       
                          _left_speed = 0;
                   _right_speed = 0;
                   }
         else {   

            if (compass_angle < (DESIRED_ANGLE - 2)) {
            // Turn right
              _left_speed = MAX_SPEED;
              _right_speed = MAX_SPEED - 15;
            }
            else {
                if (compass_angle > (DESIRED_ANGLE + 2)) {
                // Turn left
                _left_speed = MAX_SPEED - 15;
                _right_speed = MAX_SPEED;
                }
                 else {
                // Move straight forward
                _left_speed = MAX_SPEED;
                _right_speed = MAX_SPEED;
                }
            }
           }
             // Set the motor speeds
        setSpeed(_left_speed, _right_speed);
    }
}

//////////////////////////////////////////////

double MyRobot::convert_bearing_to_degrees(const double* in_vector)
{
    double rad = atan2(in_vector[0], in_vector[2]);
    double deg = rad * (180.0 / M_PI);

    return deg;
}

//////////////////////////////////////////////
