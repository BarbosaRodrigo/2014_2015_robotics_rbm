/**
 * @file    obstacle_avoidance.cpp
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

    _mode = FORWARD;

    _my_compass = getCompass("compass");
    _my_compass->enable(_time_step);
    _distance_sensor[0] = getDistanceSensor("ds1");
    _distance_sensor[0]->enable(_time_step);
    _distance_sensor[1] = getDistanceSensor("ds14");
    _distance_sensor[1]->enable(_time_step);
    _distance_sensor[2] = getDistanceSensor("ds3");
    _distance_sensor[2]->enable(_time_step);
    _distance_sensor[3] = getDistanceSensor("ds12");
    _distance_sensor[3]->enable(_time_step);
}


//////////////////////////////////////////////

MyRobot::~MyRobot()
{
    for (int i=0; i<NUM_DISTANCE_SENSOR; i++) {
        _distance_sensor[i]->disable();
    }
    _my_compass->disable();
}

//////////////////////////////////////////////

void MyRobot::run()
{
    double ir1_val = 0.0, ir14_val = 0.0;
    double ir3_val = 0.0, ir12_val = 0.0;
    double compass_angle;
   
    while (step(_time_step) != -1) {
        // Read the sensors
        ir1_val = _distance_sensor[0]->getValue();
        ir14_val = _distance_sensor[1]->getValue();
        ir3_val = _distance_sensor[2]->getValue();
        ir12_val = _distance_sensor[3]->getValue();
        
         const double *compass_val = _my_compass->getValues();
        compass_angle = convert_bearing_to_degrees(compass_val);

        cout << "ds1: " << ir1_val << " ds14:" << ir14_val << endl;
        cout << "ds3: " << ir3_val << " ds12:" << ir12_val << endl;

        //Condition to choose between compass and sensor motion mode
     if ((ir1_val < DISTANCE_LIMIT) && (ir14_val < DISTANCE_LIMIT)&& (ir12_val < DISTANCE_LIMIT)&& (ir3_val < DISTANCE_LIMIT)){ 

         //Compass mode
       if ( compass_angle < (DESIRED_ANGLE - 2)) {
            
           _mode = TURN_RIGHT;
            } 
            else{if(compass_angle > (DESIRED_ANGLE + 2)) {
               
                _mode = TURN_LEFT;
                }
                 else {
               
                _mode = FORWARD;
                }
            }}else{
         
            //Sensor mode

            //Condition to stop and go backwards
               if (((ir1_val > 800) || (ir14_val > 800)||(ir3_val > 800) || (ir12_val > 800)) && ((ir1_val != 0) || (ir14_val != 0))){
                        
                         _mode = BACKWARDS;
                          cout << "Backwards." << endl;}
                          
               else{

                   //Condition to turn using sensors
                   if ((ir12_val > DISTANCE_LIMIT-50)|| (ir14_val > DISTANCE_LIMIT)) {
                    _mode = TURN_LEFT;
                    cout << "Turning left." << endl;
                  }                         
                  
                  
                  else {
                         if ((ir3_val > DISTANCE_LIMIT-50)||(ir1_val > DISTANCE_LIMIT)) {
                        _mode = TURN_RIGHT;
                        cout << "Turning right." << endl;
                        }
                        else {                                                     
                        _mode = FORWARD;
                        cout << "Moving forward." << endl;
                    }}}  
                }
            
       
     
     
     
     
     
     
     
     
     
         
     
        // Send actuators commands according to the mode
        switch (_mode){
            case STOP:
                _left_speed = 0;
                _right_speed = 0;
                break;
            case FORWARD:
                _left_speed = MAX_SPEED;
                _right_speed = MAX_SPEED;
                break;
            case TURN_LEFT:
                _left_speed = MAX_SPEED/3.0;
                _right_speed = MAX_SPEED;
                break;
            case TURN_RIGHT:
                _left_speed = MAX_SPEED;
                _right_speed = MAX_SPEED/3.0;
                break;
            case BACKWARDS:
                _left_speed = -MAX_SPEED;
                _right_speed = -MAX_SPEED;
                break;
                
            default:
                break;
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
