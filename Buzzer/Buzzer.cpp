#include "PlutoPilot.h"

Interval Timer1;

void onLoopStartAutoInsertion() {
    Timer1.reset();
  }

void onLoopStopAutoInsertion() {
  }

void plutoInit() {
    Peripheral_Init(GPIO_1,OUTPUT);
    setUserLoopFrequency(100);
  }


void plutoRxConfig(void) {
    // Receiver mode: Uncomment one line for ESP or PPM setup.
    Receiver_Mode(Rx_ESP);  // Receiver mode for PrimusX2 / V5
  }

void onLoopStart () {
    onLoopStartAutoInsertion();
    Timer1.set(1000,true);
    Peripheral_Write(GPIO_1,STATE_LOW);
  }

void plutoLoop () {
    if (Timer1.check()) {
      Peripheral_Write(GPIO_1,STATE_HIGH);
    } else {
      Peripheral_Write(GPIO_1,STATE_LOW);
    }
  }

void onLoopFinish() {
    Timer1.reset();
    onLoopStopAutoInsertion();
  }