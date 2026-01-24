#include "PlutoPilot.h"

  void onLoopStartAutoInsertion() {
    Set_LED(STATUS, OFF);
  }

  void onLoopStopAutoInsertion() {
    Set_LED(STATUS, ON);
  }

  void plutoInit() {
    setUserLoopFrequency(100);
    Peripheral_Init(GPIO_2,INPUT);
    Peripheral_Init(GPIO_1,OUTPUT);
  }


  void plutoRxConfig(void) {
    // Receiver mode: Uncomment one line for ESP or PPM setup.
    Receiver_Mode(Rx_ESP);  // Receiver mode for PrimusX2 / V5
  }

  void onLoopStart () {
    onLoopStartAutoInsertion();
    Set_LED(BLUE,ON);
  }

  void plutoLoop () {
    if (Peripheral_Read(GPIO_2) == false) {
      Peripheral_Write(GPIO_1,STATE_HIGH);
    } else {
      Peripheral_Write(GPIO_1,STATE_LOW);
    }
    Set_LED(RED,ON);
    Set_LED(GREEN,ON);
  }

  void onLoopFinish() {
    Set_LED(GREEN,ON);
    onLoopStopAutoInsertion();
  }