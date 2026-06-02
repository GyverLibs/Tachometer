This is an automatic translation and may be incorrect in some places. See the source README and examples for authoritative information.

[![latest](https://img.shields.io/github/v/release/GyverLibs/Tachometer.svg?color=brightgreen)](https://github.com/GyverLibs/Tachometer/releases/latest/download/Tachometer.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/Tachometer.svg)](https://registry.platformio.org/libraries/gyverlibs/Tachometer)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD%24%E2%82%AC%20%D0%9F%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B6%D0%B0%D1%82%D1%8C-%D0%B0%D0%B2%D1%82%D0%BE%D1%80%D0%B0-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/Tachometer?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# Tachometer
Tachometer library for Arduino without binding to iron
- Call the Tick() in the interruption on the front
- Take the getRPM() frequency to rpm
- Take getHz() frequency to Hz
- Take getUs() period in mx
- Built-in timeout of no signal
- Built-in averaging by n revolutions

### Compatibility
Compatible with all Arduino platforms (Arduino features are used)

## Contents
- [Installation](#install)
- [Initialization](#init)
- [Use of use](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found by the name **Tachometer** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download the library](https://github.com/GyverLibs/Tachometer/archive/refs/heads/main.zip).zip archive for manual installation:
    - Unpack and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unpack and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/ *
    - (Arduino IDE) Automatic installation from .zip: *Sketch/Connect library/Add .ZIP library...* and specify downloaded archive
- Read more detailed instructions for installing libraries[here](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: new versions fix errors and bugs, as well as optimize and add new features.
- Through the library manager IDE: find the library as when installing and click "Update"
- Manually: **Delete the folder with the old version** and then put the new one in its place. “Replacement” can not be done: sometimes new versions delete files that will remain when replaced and can lead to errors!

<a id="init"></a>
## Initialization
```cpp
Tachometer tacho;
```

<a id="usage"></a>
## Use of use
```cpp
void tick();                    // ticker - call in interruption on the front
void setWindow(uint8_t window); // setting the number of revolutions for averaging (by default 10)
void setTimeout(uint16_t tout); // Interruption timeout (MS), after which rotation is considered to have stopped (silent 1000)

uint32_t getRPM();              // speed up
float getHz();                  // hertz
uint32_t getUs();               // period
```

### Computer fan
When connecting a computer fan tachometer, it is recommended to use an external lift of 4.7-10 kΩ to the VCC. Built-in PULLUP is not enough, sometimes interference arrives!
![](/docs/fan.png)

<a id="example"></a>
## Example
For more examples see **examples**!
```cpp
// We measure fan speeds from pc
#define TACH_PIN 2    // pin tachometer (external lift 4.7k to VCC is desirable)

#include <Tachometer.h>
Tachometer tacho;

void setup() {
  Serial.begin(9600);

  // Pin fan tachometer pull to VCC
  pinMode(TACH_PIN, INPUT_PULLUP);

  // set-up
  attachInterrupt(0, isr, FALLING);

  //tacho.setWindow(20); // setting the number of ticks for counting time (by default 10)
  //tacho.setTimeout(2000) // interrupt timeout (ms), after which rotation is considered to have stopped
}

// interrupter
void isr() {
  tacho.tick();   // Let the library know about it.
}

void loop() {
  // output 10 times per second
  static uint32_t tmr;
  if (millis() - tmr > 100) {
    tmr = millis();
    Serial.println(tacho.getRPM());     // RPM
    //Serial.println(tacho.getHz());    // Hz
    //Serial.println(tacho.Us());       // us
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
If you find bugs, create **Issue**, or better write to the mail immediately.[alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
The library is open for revision and your **Pull Requests*!

When reporting bugs or incorrect work of the library, it is necessary to specify:
- Library version
- What is used by the IC
- SDK version (for ESP)
- Arduino IDE version
- Are embedded examples that use features and designs that cause bugs in your code working correctly?
- What code was downloaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed. Not a canvas of a thousand lines, but a minimum code.
