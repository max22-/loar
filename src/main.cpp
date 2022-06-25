#include <Arduino.h>
#include "loar.h"

Loar L(&Serial);

void setup() {
  Serial.begin(115200);
}

void loop() {
  L.do_repl();
}



