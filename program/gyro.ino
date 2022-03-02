/*
  PicoGamepad

  Turn a Raspberry Pico 2040 into an HID gamepad

  Supports:
  128 Buttons
  8 Analog axes
  4 Hat switches
  
  created 28 June 2021
  by Jake Wilkinson (RealRobots)

  This example code is in the public domain.

  https://www.gitlab.com/realrobots/PicoGamepad
*/

#include <PicoGamepad.h>
#include <GY521.h>

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

// Pins
const uint sda_pin = 26;
const uint scl_pin = 27;

MbedI2C wire(sda_pin, scl_pin);

//PicoGamepad gamepad;
GY521 imu(0x69, &wire);


// 16 bit integer for holding input values
int val;

uint16_t gyro_delay;
uint16_t last_gyro_time;
uint16_t cur_time;
boolean data_ready = false;

struct gyrodata gyro;
struct acceldata accel;
struct magdata mag;

void setup() {  
  Serial.begin(115200);

  gyro.x = new float();
  gyro.y = new float();
  gyro.z = new float();

  accel.x = new float();
  accel.y = new float();
  accel.z = new float();

  // Initialize I2C pins
  gpio_set_function(sda_pin, GPIO_FUNC_I2C);
  gpio_set_function(scl_pin, GPIO_FUNC_I2C);
  gpio_pull_up(sda_pin);
  gpio_pull_up(scl_pin);

  imu.begin();
  
}

void loop() {

 
  cur_time = millis();

  //if (cur_time - last_gyro_time > gyro_delay) {
    //    last_gyro_time = cur_time;

        //imu->read();

    //    *accel.x = (float) random(0, 100);
    //    *accel.y = (float) random(0, 100);
    //    *accel.z = (float) random(0, 100);

    //    *gyro.x = (float) random(0, 100);
    //    *gyro.y = (float) random(0, 100);
    //    *gyro.z = (float) random(0, 100);

    //    data_ready = true;

    //}
    // poll gyroscope within a certain time interval
     if (cur_time - last_gyro_time > gyro_delay) {
         last_gyro_time = cur_time;

         imu.read();

         *accel.x = imu.getAccelX();
         *accel.y = imu.getAccelY();
         *accel.z = imu.getAccelZ();

         *gyro.x = imu.getRoll();
         *gyro.y = imu.getPitch();
         *gyro.z = imu.getYaw();

         data_ready = true;

     }
  
    //pass data to gamepad
    // if (data_ready) {
    //     gamepad.SetRx(*gyro.x);
    //     gamepad.SetRy(*gyro.y);
    //     gamepad.SetRz(*gyro.z);

    //     gamepad.send_update();
    //     data_ready = false;
    // }

    if (data_ready) {
        Serial.print(*gyro.x + " ");
        Serial.print(*gyro.y + " ");
        Serial.print(*gyro.z);
        Serial.println();

        //gamepad.send_update();
        data_ready = false;
    }

}