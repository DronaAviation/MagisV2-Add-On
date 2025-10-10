#include "PlutoPilot.h"

void onLoopStartAutoInsertion() {
  }

void onLoopStopAutoInsertion() {
  }

void plutoInit() {
    setUserLoopFrequency(100);
    Peripheral_Init(GPIO_1,INPUT);
  }


void plutoRxConfig(void) {
    // Receiver mode: Uncomment one line for ESP or PPM setup.
    Receiver_Mode(Rx_ESP);  // Receiver mode for PrimusX2 / V5
  }

void onLoopStart () {
    onLoopStartAutoInsertion();
  }

void plutoLoop () {
    if (Peripheral_Read(GPIO_1) == 0) {
      Command_TakeOff(170);
    }
  }

void onLoopFinish() {
    onLoopStopAutoInsertion();
  }