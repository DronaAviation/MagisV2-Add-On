#include "PlutoPilot.h"

void onLoopStartAutoInsertion() {
    Set_LED(STATUS,OFF);
  }

void onLoopStopAutoInsertion() {
    Set_LED(STATUS, ON);
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
    if (Peripheral_Read(ADC_1) > 80 && Peripheral_Read(ADC_1) < 800) {
      Set_LED(RED,OFF);
      Set_LED(GREEN,ON);
      Set_LED(BLUE,OFF);
    }else if (Peripheral_Read(ADC_1) > 800 && Peripheral_Read(ADC_1) < 2000) {
      Set_LED(RED,ON);
      Set_LED(GREEN,ON);
      Set_LED(BLUE,OFF);
    }else if (Peripheral_Read(ADC_1) > 2000 && Peripheral_Read(ADC_1) < 3700) {
      Set_LED(RED,ON);
      Set_LED(GREEN,OFF);
      Set_LED(BLUE,ON);
    }else if (Peripheral_Read(ADC_1) > 3700 && Peripheral_Read(ADC_1) < 4500) {
      Set_LED(RED,ON);
      Set_LED(GREEN,OFF);
      Set_LED(BLUE,OFF);
    }
  }

void onLoopFinish() {
    onLoopStopAutoInsertion();
  }