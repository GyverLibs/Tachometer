This is an automatic translation, may be incorrect in some places. See sources and examples!

# Tachometer
Tachometer library for arduino without reference to the iron
- Call Tick () in interruption on the front
- Take Getrpm () Frequency in rpm
- Take Gethz () frequency in Hz
- Take Getus () The period in the ISS
- Built -in timout of the absence of a signal
- Built -in averaging n revolutions

## compatibility
Compatible with all arduino platforms (used arduino functions)

## Content
- [installation] (# Install)
- [initialization] (#init)
- [use] (#usage)
- [Example] (# Example)
- [versions] (#varsions)
- [bugs and feedback] (#fedback)

<a id="install"> </a>
## Installation
- The library can be found by the name ** Tachometer ** and installed through the library manager in:
    - Arduino ide
    - Arduino ide v2
    - Platformio
- [download the library] (https://github.com/gyverlibs/tachometer/archive/refs/heads/main.zip) .Zip archive for manual installation:
    - unpack and put in * C: \ Program Files (X86) \ Arduino \ Libraries * (Windows X64)
    - unpack and put in * C: \ Program Files \ Arduino \ Libraries * (Windows X32)
    - unpack and put in *documents/arduino/libraries/ *
    - (Arduino id) Automatic installation from. Zip: * sketch/connect the library/add .Zip library ... * and specify downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%BD%D0%BE%BE%BE%BED0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: errors and bugs are corrected in the new versions, as well as optimization and new features are added
- through the IDE library manager: find the library how to install and click "update"
- Manually: ** remove the folder with the old version **, and then put a new one in its place.“Replacement” cannot be done: sometimes in new versions, files that remain when replacing are deleted and can lead to errors!


<a id="init"> </a>
## initialization
`` `CPP
Tachometer Tacho;
`` `

<a id="usage"> </a>
## Usage
`` `CPP
VOID Tick ();// ticker - call in interruption on the front
VOID Setwindow (Uint8_T Window);// Installation of the number of revolutions for averaging (by the silence 10)
VOID settimeout (uint16_t tout);// Timesout of interruptions (MS), after which it is believed that the rotation has stopped (by the silence 1000)

uint32_t getrpm ();// Get momentum per minute
Float gethz ();// Get Hertsy
uint32_t getus ();// Get the period in the ISS
`` `

### computer fan
When connecting a tachometer of a computer fan, it is recommended to use an external luster of 4.7-10 kOhm to VCC.The built -in Pullup is not enough, sometimes interference arrives!
! [] (/doc/fan.png)

<a id="EXAMPLE"> </a>
## Example
The rest of the examples look at ** Examples **!
`` `CPP
// Measure the fan speed from PC
#define Tach_pin 2 // Tachometer Pin (external tightening 4.7k to VCC)

#include <Tachometer.h>
Tachometer Tacho;

VOID setup () {
  Serial.Begin (9600);

  // Pin of the fan tachometer we pull up to VCC
  Pinmode (tach_pin, input_pullup);

  // We set up an interruption
  Attachinterrupt (0, ISR, Falling);

  //tacho.setwindow(20);// Installation of the number of ticks for the score of BPEmein (by the silence 10)
  //tacho.settimeout (2000);// Tixout of interruptions (MS), after which it is believed that the rotation has stopped
}

// interruption processor
VOID isr () {
  tacho.tick ();// We inform the library about this
}

VOID loop () {
  // Display 10 times per second
  Static uint32_t tmr;
  if (millis () - tmr> 100) {
    TMR = Millis ();
    Serial.println (tacho.getrpm ());// RPM
    //Serial.println (tacho.gethz ());// hz
    //Serial.println (tacho.us ());// us
  }
}
`` `

<a id="versions"> </a>
## versions
- V1.1
- V1.2
- V1.3 - improved stability, reduced code weight

<a id="feedback"> </a>
## bugs and feedback
Create ** Issue ** when you find the bugs, and better immediately write to the mail [alex@alexgyver.ru] (mailto: alex@alexgyver.ru)
The library is open for refinement and your ** pull Request ** 'ow!


When reporting about bugs or incorrect work of the library, it is necessary to indicate:
- The version of the library
- What is MK used
- SDK version (for ESP)
- version of Arduino ide
- whether the built -in examples work correctly, in which the functions and designs are used, leading to a bug in your code
- what code has been loaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed.Not a canvas of a thousand lines, but a minimum code