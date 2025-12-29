#include "PlutoPilot.h"

Interval Timer1;

void onLoopStartAutoInsertion() {
    Timer1.reset();
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
    Timer1.set(5000,true);
  }

void plutoLoop () {
    Monitor_Println("LDR_value" , Peripheral_Read(ADC_1));
    if (Peripheral_Read(ADC_1) >= 2500 && Timer1.check()) {
      Command_Land(105);
      Monitor_Println("Landed");
    }
  }

void onLoopFinish() {
    Timer1.reset();
    onLoopStopAutoInsertion();
  }