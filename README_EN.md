# Tachometer
Tachometer library for Arduino without binding to hardware
- Call tick() in a rising interrupt
- Get getRPM() frequency in rpm
- Get getHz() frequency in Hz
- Take getUs() period in µs
- Built-in no signal timeout
- Built-in averaging over n revolutions

### Compatibility
Compatible with all Arduino platforms (using Arduino functions)

## Content
- [Install](#install)
- [Initialization](#init)
- [Usage](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found by the name **Tachometer** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download library](https://github.com/GyverLibs/Tachometer/archive/refs/heads/main.zip) .zip archive for manual installation:
    - Unzip and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unzip and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/*
    - (Arduino IDE) automatic installation from .zip: *Sketch/Include library/Add .ZIP library…* and specify the downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE% D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Initialization
```cpp
Tachometer tacho;
```

<a id="usage"></a>
## Usage
```cpp
void tick(); // ticker - call in edge interrupt
void setWindow(uint8_twindow); // set the number of revolutions for averaging (default 10)
void setTimeout(uint16_t tout); // interrupt timeout (ms), after which it is considered that the rotation has stopped (default 1000)

uint32_t getRPM(); // get rpm
float getHz(); // get hertz
uint32_t getUs(); // get period in µs
```

### Computer fan
When connecting a computer fan tachometer, it is recommended to use an external 4.7-10 kΩ pull-up to VCC. The built-in PULLUP is not enough, sometimes interference arrives!
![](/docs/fan.png)

<a id="example"></a>
## Example
See **examples** for other examples!
```cpp
// measure the fan speed from the PC
#define TACH_PIN 2 // tachometer pin (external 4.7k pullup to VCC is desirable)

#include <Tachometer.h>
Tachometer tacho;

void setup() {
  Serial.begin(9600);

  // pull the fan tachometer pin to VCC
  pinMode(TACH_PIN, INPUT_PULLUP);

  // set up an interrupt
  attachInterrupt(0, isr, FALLING);

  //tacho.setWindow(20); // setting the number of ticks for the time count (default 10)
  //tacho.setTimeout(2000); // interrupt timeout (ms), after which it is considered that the rotation has stopped
}

// interrupt handler
void isr() {
  tacho.tick(); // tell the library about it
}

void loop() {
  // output 10 times per second
  static uint32_t tmr;
  if (millis() - tmr > 100) {
    tmr = millis();
    Serial.println(tacho.getRPM()); // rpm
    //Serial.println(tacho.getHz()); // Hz
    //Serial.println(tacho.Us()); // us
  }
}
```

<a id="versions"></a>
## Versions
- v1.1
- v1.2
- v1.3 - improved stability, reduced code weight

<a id="feedback"></a>
## Bugs and feedback
When finding bugs, create **Issue**, andis better to immediately write to the mail [alex@alexgyver.ru](mailto:alex@alexgyver.ru)
The library is open for revision and your **Pull Request**'s!