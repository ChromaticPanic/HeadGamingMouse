#pragma once

class GY521;
class PicoGamepad;



class HeadGamingMouse {

private:
    int val;
    PicoGamepad* gamepad;
    GY521* imu;

protected:


public:
    HeadGamingMouse();
    void process();
 
};