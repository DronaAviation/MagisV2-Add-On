#include "PlutoPilot.h"

void onLoopStartAutoInsertion() {
  }

void onLoopStopAutoInsertion() {
  }

void plutoInit() {
    setUserLoopFrequency(100);
    Peripheral_Init(ADC_1);
  }


void plutoRxConfig(void) {
    // Receiver mode: Uncomment one line for ESP or PPM setup.
    Receiver_Mode(Rx_ESP);  // Receiver mode for PrimusX2 / V5
  }

void onLoopStart () {
    onLoopStartAutoInsertion();
  }

void plutoLoop () {
    if (Peripheral_Read(ADC_1) > 130) {
      Command_TakeOff(150);
    }
    Monitor_Println("Sound" , Peripheral_Read(ADC_1));
  }

void onLoopFinish() {
    onLoopStopAutoInsertion();
  }