#pragma once
#include <Arduino.h>
#include <PicoGamepad.h>
#include <GY521.h>

//class GY521;
//class PicoGamepad;

//using namespace arduino;

class HeadGamingMouse {

private:
    int val;
    PicoGamepad* gamepad;
    GY521* imu;
    arduino::MbedI2C *wire;

    // Pins
    static const uint sda_pin;
    static const uint scl_pin;

    uint16_t gyro_delay;
    uint16_t last_gyro_time;
    uint16_t cur_time;
    uint16_t gyroNoise;
    uint16_t accelNoise;

    struct gyrodata* gyro;
    struct acceldata* accel;
    //struct magdata* mag;
    struct gyrodata* gyroPrev;
    struct acceldata* accelPrev;
    struct gyrodata* gyroDelta;
    struct acceldata* accelDelta;
    struct gyrodata* gyroZero;
    struct acceldata* accelZero;

    bool data_ready;

    void readFromGyro();
    void sendToGamepad();
    boolean calcDelta();
    void calibrate();

protected:


public:
    HeadGamingMouse();
    ~HeadGamingMouse();
    void process();
 
};
