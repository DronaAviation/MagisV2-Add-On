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
    if (Peripheral_Read(GPIO_1) == false) {
      Command_TakeOff(150);
    }
    Set_LED(GREEN,ON);
    Set_LED(RED,ON);
    Set_LED(BLUE,OFF);
  }

  void onLoopFinish() {
    Set_LED(GREEN,ON);
    onLoopStopAutoInsertion();
  }