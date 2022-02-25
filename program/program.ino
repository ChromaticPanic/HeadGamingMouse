
#include "HeadGamingMouse.h"

HeadGamingMouse* mouse;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  mouse = new HeadGamingMouse();

}

void loop() {
  // put your main code here, to run repeatedly:
  mouse->process();
}
