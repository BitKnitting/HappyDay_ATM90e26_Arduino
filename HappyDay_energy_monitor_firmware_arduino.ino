/********************************************************
  Arduino firmware code to get energy readings from the
  two CTs (Current Transformers) attached to the power
  lines within a home's breaker box.  The readings are
  sent to an mqtt broker.

  The hardware setup is discussed in this blog post:
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
//#define DEBUG
#include <DebugLib.h>
#include "Common.h"
#include "mqttStuff.h"
#include "SPI2EnergyMonitorStuff.h"
#include "Blinks.h"
/********************************************************
   SETUP
 ********************************************************/
void setup() {
  // put your setup code here, to run once:

  BlinkInSetupStart
  initStuff();
  BlinkInSetupEnd
  myMQTT_sendAlert(msgBOOT);
}

void loop() {
  BlinkInLoop
  myEnergyMonitor_getReadings();
  myMQTT_publish(energyReadingJSON);
  delay(10000);  // take a reading every 10 seconds.
}
/********************************************************
   INITSTUFF
 ********************************************************/
void initStuff() {
  DEBUG_BEGIN;
  DEBUG_WAIT;
  myEnergyMonitor_init();
  myMQTT_init();
}
