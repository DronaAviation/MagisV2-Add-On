// Do not remove the include below
#include "PlutoPilot.h"

/*
 * Laser-tag input on GPIO_1 — works with active-high OR active-low sensors.
 *
 * In plutoInit we read the sensor's idle level once: whatever it reads with no
 * laser present is "no hit", the opposite level is a "hit". Then plutoLoop just
 * fires takeoff once when a hit appears.
 */

#define LASER_PIN   GPIO_1
#define TAKEOFF_CM  170

static bool idleLevel = false;  // pin level that means "no hit"
static bool tookOff   = false;

/**
 * Configures Pluto's receiver to use PPM or default ESP mode; activate the line matching your setup.
 * AUX channel configurations is only for PPM recievers if no custom configureMode function is called this are the default setup
 * ARM mode : Rx_AUX2, range 1300 to 2100
 * ANGLE mode : Rx_AUX2, range 900 to 2100
 * BARO mode : Rx_AUX3, range 1300 to 2100
 * MAG mode : Rx_AUX1, range 900 to 1300
 * HEADFREE mode : Rx_AUX1, range 1300 to 1700
 * DEV mode : Rx_AUX4, range 1500 to 2100
 */
void plutoRxConfig ( void ) {
  // Receiver mode: Uncomment one line for ESP or CAM or PPM setup.
  Receiver_Mode ( Rx_ESP );    // Onboard ESP
  // Receiver_Mode ( Rx_CAM );    // WiFi CAMERA
  // Receiver_Mode ( Rx_PPM );    // PPM based
}

// The setup function is called once at Pluto's hardware startup
void plutoInit ( void ) {
  // Pull-down so a disconnected pin reads LOW (never a false hit).
  Peripheral_Init ( LASER_PIN, INPUT_PULL_DOWN );

  // Detect the sensor type: read its idle level now (no laser at power-up).
  idleLevel = Peripheral_Read ( LASER_PIN );
}

// The function is called once before plutoLoop when you activate Developer Mode
void onLoopStart ( void ) {
  // do your one time stuffs here
  tookOff = false;
}

// The loop function is called in an endless loop
void plutoLoop ( void ) {
  // A hit is any level different from the idle level we read in plutoInit.
  bool hit = ( Peripheral_Read ( LASER_PIN ) != idleLevel );

  if ( hit && !tookOff ) {
    Command_TakeOff ( TAKEOFF_CM );
    tookOff = true;
  }
}

// The function is called once after plutoLoop when you deactivate Developer Mode
void onLoopFinish ( void ) {
  // do your cleanup stuffs here
}
