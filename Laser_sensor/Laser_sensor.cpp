#include "PlutoPilot.h"

  void onLoopStartAutoInsertion() {
    Set_LED(STATUS, OFF);
  }

  void onLoopStopAutoInsertion() {
    Set_LED(STATUS, ON);
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
    Set_LED(BLUE,ON);
  }

  void plutoLoop () {
    if (Peripheral_Read(GPIO_1) == 0) {
      Command_TakeOff(170);
    }
    Set_LED(RED,ON);
    Set_LED(GREEN,ON);
  }

  void onLoopFinish() {
    Set_LED(GREEN,ON);
    onLoopStopAutoInsertion();
  }