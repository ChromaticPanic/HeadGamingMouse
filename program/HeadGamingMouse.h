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
    PicoGamepad *gamepad;
    GY521 *imu;
    arduino::MbedI2C *wire;

    // Pins
    static const uint sda_pin;
    static const uint scl_pin;

    uint16_t gyro_delay;
    uint16_t last_gyro_time;
    uint16_t cur_time;
    uint16_t gyroNoise;
    uint16_t accelNoise;

    class Data;
    Data *gyro;
    Data *accel;
    Data *gyroPrev;
    Data *accelPrev;
    Data *gyroDelta;
    Data *accelDelta;
    Data *gyroZero;
    Data *accelZero;

    bool data_ready;

    void readFromGyro();
    void sendToGamepad();
    boolean calcDelta();
    void calibrate();

    class Data {
    public:
        float x;
        float y;
        float z;
        Data();
        //~Data();
    };

protected:


public:
    HeadGamingMouse();
    ~HeadGamingMouse();
    void process();

};