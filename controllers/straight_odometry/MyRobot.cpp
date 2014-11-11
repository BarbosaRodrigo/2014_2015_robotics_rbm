/**
 * @file    MyRobot.cpp
 * @brief   A template for webots projects.
 *
 * @author  Rodrigo Barbosa Moreno <100072651@alumnos.uc3m.es>
 * @date    2014-11
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
}


//////////////////////////////////////////////

MyRobot::~MyRobot()
{
    _my_compass->disable();
}

//////////////////////////////////////////////

void MyRobot::run()
{
    double compass_angle;
    double metros=0;
    double spin=0;
    double timer=0;

    while (step(_time_step) != -1){
        // Read the compass
        const double *compass_val = _my_compass->getValues();

        // Convert compass bearing vector to angle, in degrees
        compass_angle = convert_bearing_to_degrees(compass_val);

        // Print  values to console
        cout << "Compass angle (degrees): " << compass_angle << endl;
        cout << "metros (m): " << metros << endl;
        cout << "timerForw (s): " << timer << endl;
        cout << "timerSpin (s): " << spin << endl;

        //Condition to follow the desired angle
        if ((compass_angle < (DESIRED_ANGLE - 6))||(compass_angle > (DESIRED_ANGLE + 6))){
            spin++;
            if (compass_angle < (DESIRED_ANGLE - 2)) {
                // Turn right without moving forward
                _left_speed = SPIN_SPEED;
                _right_speed = -SPIN_SPEED;

            }
            else {
                if (compass_angle > (DESIRED_ANGLE + 2)) {
                    // Turn left without moving forward
                    _left_speed = -SPIN_SPEED;
                    _right_speed = SPIN_SPEED;
                }}}
        //Condition to move forward or stop
        else{ if(metros < 17){
                _left_speed = MAX_SPEED;
                _right_speed = MAX_SPEED;
                timer++;
                metros=(timer/18.94);
            }else{
                _left_speed = 0;

                _right_speed = 0;
            } }
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
