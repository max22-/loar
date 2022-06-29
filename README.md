# Loar
Embed the [Lua](https://www.lua.org/) programming language in your Arduino sketch.
(Lua version 5.3.6)
Work in progress.

# Example

```
#include <Arduino.h>
#include <loar.h>

Loar L(&Serial);

void setup() {
  Serial.begin(115200);
}

void loop() {
  L.do_repl();
}
```

# Compatible boards
- ESP32 Dev Module
- Raspberry Pi Pi
- Others, but not tested yet.

# Why "Loar" ?
Loar means moon in [Breton language](https://en.wikipedia.org/wiki/Breton_language).