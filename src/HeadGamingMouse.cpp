#include "HeadGamingMouse.h"
#include "PicoGamepad.h"
#include "GY521.h"
#include "Arduino.h"

/**
 * CLASS: HeadGamingMouse
 * Author: BMED
 * 
 * Purpose:
 * 
 */




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
    
    this->gamepad = new PicoGamepad(true, 0x1235, 0x0050, 0x0001);
    this->imu = new GY521();
    this->val =16;

    Serial.begin(115200);

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

}