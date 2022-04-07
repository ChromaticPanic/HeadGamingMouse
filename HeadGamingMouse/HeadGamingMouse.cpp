/**
 * CLASS: HeadGamingMouse
 * Author: BMED
 *
 * Purpose:
 *
 */


#include "HeadGamingMouse.h"
#include <Serial.h>


HeadGamingMouse::Data::Data()
{
    x = 0;
    y = 0;
    z = 0;
}

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

    this->gyro = new Data;
    this->accel = new Data;
    this->gyroPrev = new Data;
    this->accelPrev = new Data;
    this->gyroDelta = new Data;
    this->accelDelta = new Data;
    this->gyroZero = new Data;
    this->accelZero = new Data;

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
    delete this->gyroZero;
    delete this->accelZero;
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

        accel->x = imu->getAccelX();
        accel->y = imu->getAccelY();
        accel->z = imu->getAccelZ();

        gyro->x = imu->getRoll();
        gyro->y = imu->getPitch();
        gyro->z = imu->getYaw();

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
    Serial.print( "Roll: " + String( gyro->x ) );
    Serial.print( " Pitch: " + String( gyro->y ) );
    Serial.print( " Yaw: " + String( gyro->z ) );

    Serial.println();

    gamepad->SetRx( gyro->x );
    gamepad->SetRy( gyro->y );
    gamepad->SetRz( gyro->z );

    gamepad->send_update();
    data_ready = false;
}

boolean HeadGamingMouse::calcDelta()
{
    boolean result = false;

    gyroDelta->x = gyro->x - gyroPrev->x;
    if ( abs( gyroDelta->x ) > gyroNoise )
    {
        result = true;
    }

    if ( !result )
    {
        gyroDelta->y = gyro->y - gyroPrev->y;
        if ( abs( gyroDelta->y ) > gyroNoise )
        {
            result = true;
        }
    }

    if ( !result )
    {
        gyroDelta->z = gyro->z - gyroPrev->z;
        if ( abs( gyroDelta->z ) > gyroNoise )
        {
            result = true;
        }
    }

    if ( result )
    {
        gyroPrev->x = gyro->x;
        gyroPrev->y = gyro->y;
        gyroPrev->z = gyro->z;
    }

    accelDelta->x = accel->x - accelPrev->x;
    if ( abs( accelDelta->x ) > accelNoise )
    {
        result = true;
    }

    if ( !result )
    {
        accelDelta->y = accel->y - accelPrev->y;
        if ( abs( accelDelta->y ) > accelNoise )
        {
            result = true;
        }
    }

    if ( !result )
    {
        accelDelta->z = accel->z - accelPrev->z;
        if ( abs( accelDelta->z ) > accelNoise )
        {
            result = true;
        }
    }

    if ( result )
    {
        accelPrev->x = accel->x;
        accelPrev->y = accel->y;
        accelPrev->z = accel->z;
    }

    return result;

}

void HeadGamingMouse::calibrate()
{
    Serial.println( "Begin: Calibrating" );

    readFromGyro();

    Serial.println( "End: Calibrating" );
}