// Do not remove the include below
#include "PlutoPilot.h"

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
  // Receiver_Mode ( Rx_PPM );    // PPM based
}

// Set these to match YOUR wiring so that "forward" (pitch > 1600) drives both wheels forward.
#define M1_FWD ANTICLOCK_WISE
#define M1_REV CLOCK_WISE
#define M2_FWD CLOCK_WISE
#define M2_REV ANTICLOCK_WISE

// If roll feels reversed (stick right turns left), set to -1
#define ROLL_SIGN ( +1 )    // or -1
// If pitch feels reversed (stick forward goes backward), set to -1
#define PITCH_SIGN ( +1 )    // or -1

// The setup function is called once at Pluto's hardware startup
void plutoInit ( void ) {
  // Add your hardware initialization code here
  // Initialize Motor 1 for operation.
  Motor_Init ( M1 );

  // Initialize Motor 2 for operation.
  Motor_Init ( M2 );
}

// The function is called once before plutoLoop when you activate Developer Mode
void onLoopStart ( void ) {
  // do your one time stuffs here
  // Set the speed of Motor 1 to its minimum value (1000).
  Motor_Set ( M1, 1000 );

  // Set the speed of Motor 2 to its minimum value (1000).
  Motor_Set ( M2, 1000 );
}

/**
 * @brief Clamps the given value within the specified range.
 *
 * This function takes an input value `x` and ensures that it lies within the
 * inclusive range specified by `lo` (lower bound) and `hi` (upper bound). If `x`
 * is less than `lo`, the function returns `lo`. If `x` is greater than `hi`,
 * the function returns `hi`. Otherwise, it returns `x`.
 *
 * @param x The value to be clamped.
 * @param lo The lower bound of the range.
 * @param hi The upper bound of the range.
 * @return The clamped value within the range [lo, hi].
 */
static inline int16_t clamp16 ( int16_t x, int16_t lo, int16_t hi ) {
  // Check if the input value x is less than the lower bound lo.
  // If true, return the lower bound lo.
  if ( x < lo ) return lo;

  // Check if the input value x is greater than the upper bound hi.
  // If true, return the upper bound hi.
  if ( x > hi ) return hi;

  // If x is within the range [lo, hi], return x as it is already clamped.
  return x;
}

/**
 * @brief Converts a remote control signal value to a signed decibel representation.
 *
 * This function interprets a 16-bit unsigned integer `v` as a remote control signal
 * value and converts it into a signed decibel scale. It maps values below a certain
 * threshold (`LO`) to -1000, above another threshold (`HI`) to 1000, and applies
 * specific transformations within defined deadband thresholds (`DB_LO`, `DB_HI`) to
 * represent the signal in a normalized form.
 *
 * @param v The input remote control signal value.
 * @return The signed decibel equivalent of the input value.
 */
static int16_t rc_to_signed_db ( uint16_t v ) {
  // Define the constants for range limits and deadband
  const uint16_t LO = 1000, HI = 2000, DB_LO = 1400, DB_HI = 1600;

  // If the input value v is less than or equal to the lower limit LO,
  // return -1000 as it represents the minimum signed dB.
  if ( v <= LO ) return -1000;

  // If the input value v is greater than or equal to the upper limit HI,
  // return 1000 as it represents the maximum signed dB.
  if ( v >= HI ) return 1000;

  // If the input value v is within the deadband range [DB_LO, DB_HI],
  // return 0 as it indicates no deviation from the center.
  if ( v >= DB_LO && v <= DB_HI ) return 0;

  // If the input value v is above the deadband high limit DB_HI,
  // calculate the positive deviation in signed dB.
  if ( v > DB_HI ) {
    uint16_t num = v - DB_HI;                             // Calculate the amount over the deadband high limit
    return ( int16_t ) ( ( num * 1000 + 200 ) / 400 );    // Convert to signed dB with scaling
  } else {
    // If the input value v is below the deadband low limit DB_LO,
    // calculate the negative deviation in signed dB.
    uint16_t num = DB_LO - v;                                     // Calculate the amount below the deadband low limit
    int16_t m    = ( int16_t ) ( ( num * 1000 + 200 ) / 400 );    // Convert to signed dB with scaling
    return ( int16_t ) ( -m );                                    // Return the negative deviation
  }
}

/**
 * @brief Converts a throttle signal to a normalized 0-1000 range.
 *
 * This function processes a throttle signal represented by a 16-bit unsigned integer
 * `v` and normalizes it to a range from 0 to 1000. Values below or equal to 1000 are
 * clamped to 0, while those at or above 2000 are clamped to 1000. Values within the
 * range are linearly mapped between these bounds.
 *
 * @param v The input throttle signal value.
 * @return The normalized throttle value within 0 to 1000 range.
 */
static inline uint16_t rc_thr_0_1000 ( uint16_t v ) {
  // If the input value v is less than or equal to 1000,
  // return 0 as it represents the minimum threshold.
  if ( v <= 1000 ) return 0;

  // If the input value v is greater than or equal to 2000,
  // return 1000 as it represents the maximum threshold.
  if ( v >= 2000 ) return 1000;

  // For values between 1000 and 2000, subtract 1000 from v to
  // scale the result to a range of 0 to 1000.
  return ( uint16_t ) ( v - 1000 );
}

// static inline uint16_t mag_to_pwm_u16 ( uint16_t mag0_1000 ) {
//   if ( mag0_1000 > 1000 ) mag0_1000 = 1000;
//   return ( uint16_t ) ( 1000 + mag0_1000 );
// }

// The loop function is called in an endless loop
void plutoLoop ( void ) {
  // Add your repeated code here
  // Retrieve the current throttle, pitch, and roll values from the RC data.
  uint16_t TempThrottle = RcData_Get ( RC_THROTTLE );
  uint16_t TempPitch    = RcData_Get ( RC_PITCH );
  uint16_t TempRoll     = RcData_Get ( RC_ROLL );

  // Convert pitch to signed range for forward/backward direction (-1000 to +1000).
  int16_t v = rc_to_signed_db ( TempPitch );

  // Convert roll to signed range for left/right direction (-1000 to +1000).
  int16_t w = rc_to_signed_db ( TempRoll );

  // Scale throttle to a range of 0 to 1000.
  uint16_t t = rc_thr_0_1000 ( TempThrottle );

  // Apply axis polarity using predefined constants.
  v = ( int16_t ) ( v * PITCH_SIGN );
  w = ( int16_t ) ( w * ROLL_SIGN );

  // If both v and w are zero or throttle is zero, set motors to full forward speed and return.
  if ( ( v == 0 && w == 0 ) || t == 0 ) {
    Motor_SetDir ( M1, M1_FWD );
    Motor_Set ( M1, 1000 );
    Motor_SetDir ( M2, M2_FWD );
    Motor_Set ( M2, 1000 );
    return;
  }

  // Calculate differential mix using 32-bit intermediates for left and right commands.
  int32_t left_cmd  = ( int32_t ) clamp16 ( ( int16_t ) ( v + w ), -1000, 1000 );
  int32_t right_cmd = ( int32_t ) clamp16 ( ( int16_t ) ( v - w ), -1000, 1000 );

  // Scale left and right commands by throttle value.
  left_cmd  = ( left_cmd * ( int32_t ) t + 500 ) / 1000;
  right_cmd = ( right_cmd * ( int32_t ) t + 500 ) / 1000;

  // Clamp the scaled left and right commands to ensure they remain within bounds.
  left_cmd  = clamp16 ( ( int16_t ) left_cmd, -1000, 1000 );
  right_cmd = clamp16 ( ( int16_t ) right_cmd, -1000, 1000 );

  // Set motor directions and speeds based on the calculated commands.
  // For left motor
  if ( left_cmd >= 0 ) {
    Motor_SetDir ( M1, M1_FWD );
    Motor_Set ( M1, ( uint16_t ) ( 1000 + left_cmd ) );
  } else {
    Motor_SetDir ( M1, M1_REV );
    Motor_Set ( M1, ( uint16_t ) ( 1000 + ( -left_cmd ) ) );
  }

  // For right motor
  if ( right_cmd >= 0 ) {
    Motor_SetDir ( M2, M2_FWD );
    Motor_Set ( M2, ( uint16_t ) ( 1000 + right_cmd ) );
  } else {
    Motor_SetDir ( M2, M2_REV );
    Motor_Set ( M2, ( uint16_t ) ( 1000 + ( -right_cmd ) ) );
  }
}

// The function is called once after plutoLoop when you deactivate Developer Mode
void onLoopFinish ( void ) {
  // do your cleanup stuffs here
  // Set the speed of Motor 1 to its minimum value (1000).
  Motor_Set ( M1, 1000 );

  // Set the speed of Motor 2 to its minimum value (1000).
  Motor_Set ( M2, 1000 );
}
