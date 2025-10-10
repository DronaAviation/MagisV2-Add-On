#include "PlutoPilot.h"

Interval Timer1;

void onLoopStartAutoInsertion() {
    Timer1.reset();
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
    Timer1.set(1000,true);
  }

void plutoLoop () {
    if (Peripheral_Read(GPIO_1) == 0 && Timer1.check()) {
      RcCommand_Set(RC_PITCH,1350);
    } else {
      RcCommand_Set(RC_PITCH,RcData_Get(RC_PITCH));
    }
  }

void onLoopFinish() {
    Timer1.reset();
    onLoopStopAutoInsertion();
  }