#include "PlutoPilot.h"

Interval Timer1;
int32_t time;

void onLoopStartAutoInsertion() {
    Timer1.reset();
  }

void onLoopStopAutoInsertion() {
  }

void plutoInit() {
    setUserLoopFrequency(100);
    Peripheral_Init(ADC_1);
    Peripheral_Init(GPIO_1,OUTPUT);
  }


void plutoRxConfig(void) {
    // Receiver mode: Uncomment one line for ESP or PPM setup.
    Receiver_Mode(Rx_ESP);  // Receiver mode for PrimusX2 / V5
  }

void onLoopStart () {
    onLoopStartAutoInsertion();
    Timer1.set(time,true);
  }

void plutoLoop () {
    Monitor_Println("somkin" , Peripheral_Read(ADC_1));
    time = (((1100 - Peripheral_Read(ADC_1))) * 3);
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