/**
 * CLASS: HeadGamingMouse
 * Author: BMED
 *
 * Purpose:
 *
 */


#include "HeadGamingMouse.h"
//#include <PicoGamepad.h>
//#include <GY521.h>
#include <Serial.h>


 //using namespace arduino;

struct gyrodata {
    float *x;
    float *y;
    float *z;
};

struct acceldata {
    float *x;
    float *y;
    float *z;
};

struct magdata {
    float *x;
    float *y;
    float *z;
};

const uint HeadGamingMouse::sda_pin = 20;
const uint HeadGamingMouse::scl_pin = 21;

/**
 * Constructor
 *
 * @purpose: Initializes the HeadGamingMouse object
 *           Initialize child objects
 *
 * @param void
 * @return void
 */
HeadGamingMouse::HeadGamingMouse()
{
    Serial.begin( 115200 );

    this->wire = new arduino::MbedI2C( sda_pin, scl_pin );
    this->gamepad = new PicoGamepad( true, 0x1235, 0x0050, 0x0001 );
    this->imu = new GY521( 0x68, wire );

    gpio_set_function( sda_pin, GPIO_FUNC_I2C );
    gpio_set_function( scl_pin, GPIO_FUNC_I2C );
    gpio_pull_up( sda_pin );
    gpio_pull_up( scl_pin );

    this->val = 16;
    this->gyro_delay = 2000;
    this->last_gyro_time = 0;
    this->data_ready = false;
    this->gyroNoise = 1;
    this->accelNoise = 1;

    this->gyro = new gyrodata;
    this->accel = new acceldata;
    //this->mag = new magdata;

    this->gyro->x = new float();
    this->gyro->y = new float();
    this->gyro->z = new float();

    this->accel->x = new float();
    this->accel->y = new float();
    this->accel->z = new float();

    this->gyroPrev = new gyrodata;
    this->accelPrev = new acceldata;
    //this->mag = new magdata;

    this->gyroPrev->x = new float();
    this->gyroPrev->y = new float();
    this->gyroPrev->z = new float();

    this->accelPrev->x = new float();
    this->accelPrev->y = new float();
    this->accelPrev->z = new float();

    this->gyroDelta = new gyrodata;
    this->accelDelta = new acceldata;

    this->gyroDelta->x = new float();
    this->gyroDelta->y = new float();
    this->gyroDelta->z = new float();

    this->accelDelta->x = new float();
    this->accelDelta->y = new float();
    this->accelDelta->z = new float();

    this->gyroZero = new gyrodata;
    this->accelZero = new acceldata;

    this->gyroZero->x = new float();
    this->gyroZero->y = new float();
    this->gyroZero->z = new float();

    this->accelZero->x = new float();
    this->accelZero->y = new float();
    this->accelZero->z = new float();

    //this->mag->x = new float;
    //this->mag->y = new float;
    //this->mag->z = new float;

    //imu->setThrottle(true);
    //imu->setThrottleTime(this->gyro_delay);
    //imu->setAccelSensitivity(0);
    //imu->setGyroSensitivity(0);


}

HeadGamingMouse::~HeadGamingMouse()
{
    delete this->gamepad;
    delete this->imu;
    delete this->gyro;
    delete this->accel;
    delete this->gyroPrev;
    delete this->accelPrev;
    delete this->gyroDelta;
    delete this->accelDelta;
}

/**
 * process
 *
 * @purpose: program loop
 */
void HeadGamingMouse::process()
{

    cur_time = millis();

    // poll gyroscope within a certain time interval
    if ( cur_time - last_gyro_time > gyro_delay )
    {
        last_gyro_time = cur_time;

        readFromGyro();
    }

    //pass data to gamepad
    if ( data_ready && calcDelta() )
    {
        sendToGamepad();
    }

}

/**
 * @purpose: read from gyroscope
 */
void HeadGamingMouse::readFromGyro()
{
    if ( imu->isConnected() )
    {
        imu->read();

        *accel->x = imu->getAccelX();
        *accel->y = imu->getAccelY();
        *accel->z = imu->getAccelZ();

        *gyro->x = imu->getRoll();
        *gyro->y = imu->getPitch();
        *gyro->z = imu->getYaw();

        data_ready = true;
    }
    else
    {
        Serial.println( "Begin: IMU not connected" );
    }
}

/**
 * @purpose: send to gamepad
 */
void HeadGamingMouse::sendToGamepad()
{
    Serial.print( "Roll: " + String( *gyro->x ) );
    Serial.print( " Pitch: " + String( *gyro->y ) );
    Serial.print( " Yaw: " + String( *gyro->z ) );

    Serial.println();

    gamepad->SetRx( *gyro->x );
    gamepad->SetRy( *gyro->y );
    gamepad->SetRz( *gyro->z );

    gamepad->send_update();
    data_ready = false;
}

boolean HeadGamingMouse::calcDelta()
{
    boolean result = false;

    *gyroDelta->x = *gyro->x - *gyroPrev->x;
    if(abs(*gyroDelta->x) > gyroNoise)
    {
        result = true;
    }

    if(!result)
    {
        *gyroDelta->y = *gyro->y - *gyroPrev->y;
        if(abs(*gyroDelta->y) > gyroNoise)
        {
            result = true;
        }
    }

    if(!result)
    {
        *gyroDelta->z = *gyro->z - *gyroPrev->z;
        if(abs(*gyroDelta->z) > gyroNoise)
        {
            result = true;
        }
    }

    if(result)
    {
        *gyroPrev->x = *gyro->x;
        *gyroPrev->y = *gyro->y;
        *gyroPrev->z = *gyro->z;
    }

    *accelDelta->x = *accel->x - *accelPrev->x;
    if(abs(*accelDelta->x) > accelNoise)
    {
        result = true;
    }

    if(!result)
    {
        *accelDelta->y = *accel->y - *accelPrev->y;
        if(abs(*accelDelta->y) > accelNoise)
        {
            result = true;
        }
    }

    if(!result)
    {
        *accelDelta->z = *accel->z - *accelPrev->z;
        if(abs(*accelDelta->z) > accelNoise)
        {
            result = true;
        }
    }

    if(result)
    {
        *accelPrev->x = *accel->x;
        *accelPrev->y = *accel->y;
        *accelPrev->z = *accel->z;
    }

    return result;
   
}

void HeadGamingMouse::calibrate()
{
    Serial.println( "Begin: Calibrating" );

    readFromGyro();

    Serial.println( "End: Calibrating" );
}
