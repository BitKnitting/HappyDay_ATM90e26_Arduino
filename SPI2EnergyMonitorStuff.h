/********************************************************
  Arduino firmware code to talk to Tisham's atm90e26 FeatherWing

  Discussed in this blog post:
  https://bitknitting.wordpress.com/2017/10/07/trying-out-the-atm90e26-featherwing/

  v0.1
  Copyright HappyDay, 2018
  The MIT License (MIT)

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.

 ********************************************************/
#include "Common.h"
#include <SPI.h>
#include "energyic_SPI.h"
//********************>>>>>> Using Both SPIs <<<<<<<<************
ATM90E26_SPI eic0(0); // CS pin = 0
ATM90E26_SPI eic1(15); // CS pin = 15

/********************************************************
   myEnergyMonitor_init
 ********************************************************/
void myEnergyMonitor_init() {
  eic0.InitEnergyIC();
  eic1.InitEnergyIC();
}
/********************************************************
   myEnergyMonitor_getReadings
   - take readings....NOTE: I am only taking power readings....
   - put into a JSON formatted string.
 ********************************************************/
void myEnergyMonitor_getReadings() {
  // Check to see if the ATM90 is working...if the system status returns 2, it is...
  bool atm90needsReset = false;
  if ( (eic0.GetSysStatus() != 2) || (eic1.GetSysStatus() != 2) ) {
    atm90needsReset = true;
  }
  if (atm90needsReset) {
    myEnergyMonitor_init();
    strcpy_P(energyReadingJSON, msgRESET);
    return;
  }
  int wholePower = abs(eic0.GetActivePower()) + abs(eic1.GetActivePower());
  // Make JSON string
  strcpy(energyReadingJSON, "{\"p\":");
  char buf[10];
  itoa(wholePower, buf, 10);
  strcat(energyReadingJSON, buf);
  strcat(energyReadingJSON, "}");
}
