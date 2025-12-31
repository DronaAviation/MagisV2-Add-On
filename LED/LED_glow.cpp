#include "PlutoPilot.h"

int32_t PWM_vallue;
Interval Timer1;

  void onLoopStartAutoInsertion() {
    Timer1.reset();
    Set_LED(STATUS, OFF);
  }

  void onLoopStopAutoInsertion() {
    Set_LED(STATUS, ON);
  }

  void plutoInit() {
    setUserLoopFrequency(100);
    Peripheral_Init(PWM_1);
  }


  void plutoRxConfig(void) {
    // Receiver mode: Uncomment one line for ESP or PPM setup.
    Receiver_Mode(Rx_ESP);  // Receiver mode for PrimusX2 / V5
  }

  void onLoopStart () {
    onLoopStartAutoInsertion();
    PWM_vallue = 500;
    Timer1.set(500,true);
  }

  void plutoLoop () {
    while (PWM_vallue <= 2000) {
      if (Timer1.check()) {
        Peripheral_Write(PWM_1,PWM_vallue);
        PWM_vallue = (PWM_vallue + 100);
      }
    }
    Set_LED(RED,ON);
    Set_LED(GREEN,ON);
  }

  void onLoopFinish() {
    Timer1.reset();
    onLoopStopAutoInsertion();
  }