#pragma once

class GY521;
class PicoGamepad;

using namespace arduino;

class HeadGamingMouse {

private:
    int val;
    PicoGamepad* gamepad;
    GY521* imu;

    uint16_t gyro_delay;
    uint16_t last_gyro_time;
    uint16_t cur_time;
    struct gyrodata* gyro;
    struct acceldata* accel;
    struct magdata* mag;

    bool data_ready;

protected:


public:
    HeadGamingMouse();
    void process();
 
};