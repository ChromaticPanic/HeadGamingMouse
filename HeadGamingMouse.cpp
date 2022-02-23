/**
 * CLASS: HeadGamingMouse
 * Author: BMED
 * 
 * Purpose:
 * 
 */


#include "HeadGamingMouse.h"
#include "lib/PicoGamepad.h"
#include "lib/GY521.h"
#include <Arduino.h>


using namespace arduino;

struct gyrodata {
    float* x;
    float* y;
    float* z;   
};

struct acceldata {
    float* x;
    float* y;
    float* z;   
};

struct magdata {
    float* x;
    float* y;
    float* z;   
};

/**
 * Constructor
 * 
 * @PURPOSE: Initializes the HeadGamingMouse object
 *           Initialize child objects
 * 
 * @param void
 * @return void
 */
HeadGamingMouse::HeadGamingMouse(){
    
    this->gamepad = new PicoGamepad();
    this->imu = new GY521();
    this->val =16;
    this->gyro_delay = 1000;
    this->last_gyro_time = 0;

    imu->setThrottle(true);
    imu->setThrottleTime(this->gyro_delay);

    this->gyro = new gyrodata();
    this->accel = new acceldata();
    this->mag = new magdata();

    this->gyro->x = new float();
    this->gyro->y = new float();
    this->gyro->z = new float();

    this->accel->x = new float();
    this->accel->y = new float();
    this->accel->z = new float();

    this->mag->x = new float();
    this->mag->y = new float();
    this->mag->z = new float();

    imu->setAccelSensitivity(0);
    imu->setGyroSensitivity(0);

    this->data_ready = false;

    Serial.begin(115200);

}

HeadGamingMouse::~HeadGamingMouse(){
    delete this->gamepad;
    delete this->imu;
    delete this->gyro;
    delete this->accel;
    delete this->mag;
}

/**
 * process
 * 
 * @PURPOSE: program loop
 * 
 * @param void
 * @return void
 */
void HeadGamingMouse::process(){

    cur_time = millis();

    if (cur_time - last_gyro_time > gyro_delay) {
        last_gyro_time = cur_time;

        imu->read();

        *accel->x = imu->getAccelX();
        *accel->y = imu->getAccelY();
        *accel->z = imu->getAccelZ();

        *gyro->x = imu->getRoll();
        *gyro->y = imu->getPitch();
        *gyro->z = imu->getYaw();

        data_ready = true;

    }


    if (data_ready) {
        gamepad->SetRx(*gyro->x);
        gamepad->SetRy(*gyro->y);
        gamepad->SetRz(*gyro->z);
        data_ready = false;
    }


}