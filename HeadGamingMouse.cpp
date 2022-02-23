#include "HeadGamingMouse.h"
#include "lib/PicoGamepad.h"
#include "lib/GY521.h"
#include <Arduino.h>

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
    
    this->gamepad = new PicoGamepad();
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