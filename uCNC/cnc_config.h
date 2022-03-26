/*
        Name: cnc_config.h
        Description: Compile time configurations for µCNC.

        Copyright: Copyright (c) João Martins
        Author: João Martins
        Date: 19/09/2019

        µCNC is free software: you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
        the Free Software Foundation, either version 3 of the License, or
        (at your option) any later version. Please see
   <http://www.gnu.org/licenses/>

        µCNC is distributed WITHOUT ANY WARRANTY;
        Also without the implied warranty of MERCHANTABILITY or FITNESS FOR A
   PARTICULAR PURPOSE. See the	GNU General Public License for more details.
*/

#ifndef CNC_CONFIG_H
#define CNC_CONFIG_H

#ifdef __cplusplus
extern "C"
{
#endif

#define INTERFACE_USART 0
#define INTERFACE_USB 1

  /**
   * Serial COM
   * Defines the serial COM baud rate
   * Uses 1 start bit + 8 bit + 1 stop bit (no parity)
   * */

#ifndef BAUDRATE
#define BAUDRATE 115200
#endif

#ifndef INTERFACE
#define INTERFACE INTERFACE_USART
#endif

  /**
   * uncomment to force enable synchronized TX/RX (used in USB VCP)
   * enable these options to perform comunications in the mcu tasks function
   * call instead of being interrupt driven (sync RX may cause problems with
   * hardware USART)
   * */

  //  #define ENABLE_SYNC_TX
  //  #define ENABLE_SYNC_RX

  /**
   * Choose the board
   * Check boardss.h for list of available/supported boards
   * */

#ifndef BOARD
#define BOARD BOARD_RAMPS14
#endif

  /**
   * Kinematic
   *
   * Defines axis count
   * Defines the machine kinematics (cartesian, corexy, delta, custom, ...)
   * For custom/advanced configurations go to the specified kinematics header
   * file
   * */

#ifndef AXIS_COUNT
#define AXIS_COUNT 3
#endif

#ifndef KINEMATIC
#define KINEMATIC KINEMATIC_DELTA
#endif

  /**
   * Defines the number of supported coordinate systems supported by µCNC
   * Can be any value between 1 and 9
   * */

#define COORD_SYS_COUNT 6

  /**
   * Number of segments of an arc computed with aprox. of sin/cos math
   * operation before performing a full calculation
   * */

#define N_ARC_CORRECTION 16

  /**
   * Echo recieved commands.
   * Uncomment to enable. Only necessary to debug communication problems
   * */

  //#define ECHO_CMD

  /**
   * Sets/limits the number of tools to be used
   * The tool and tool order are configured in the cnc_hal_config.h
   * */

#ifndef TOOL_COUNT
#define TOOL_COUNT 1
#endif

#if TOOL_COUNT > 0
  /**
   * Number of seconds of delay before motions restart after releasing from a
   * hold or after setting a new spindle speed This is used by spindle to
   * ensure spindle gets up to speed in motions
   * */

#define DELAY_ON_RESUME_SPINDLE 4
#define DELAY_ON_SPINDLE_SPEED_CHANGE 1
// minimum output if the value of S is other then 0
#define PWM_MIN_OUTPUT 0
// define coolant delay at restart
#define DELAY_ON_RESUME_COOLANT 1
// uncomment to make M7 act as M8
//#define M7_SAME_AS_M8
#endif

  /**
   * Feed overrides increments and percentage ranges
   * */

#define FEED_OVR_MAX 200
#define FEED_OVR_MIN 10
#define FEED_OVR_COARSE 10
#define FEED_OVR_FINE 1

  /**
   * Rapid feed overrides percentages
   * */

#define RAPID_FEED_OVR1 50
#define RAPID_FEED_OVR2 25

  /**
   * Spindle speed overrides increments percentages and ranges
   * */

#define SPINDLE_OVR_MAX 200
#define SPINDLE_OVR_MIN 10
#define SPINDLE_OVR_COARSE 10
#define SPINDLE_OVR_FINE 1

/**
 * G-code options
 */

/**
 * ignores undefined axis in gcode instead of sending an error
 * */
#define IGNORE_UNDEFINED_AXIS

/**
 * processes and displays the currently executing gcode numbered line
 * */

//#define GCODE_PROCESS_LINE_NUMBERS
#ifdef GCODE_PROCESS_LINE_NUMBERS
// uncomment this line to ignore the value in the N parameter and count real
// text lines
//#define GCODE_COUNT_TEXT_LINES
#endif

  /**
   * processes comment as defined in the RS274NGC
   * */

  //#define PROCESS_COMMENTS

  /**
   * Enables RS274NGC canned cycles
   * */

  // #define ENABLE_CANNED_CYCLES

  /**
   * accepts the E word (currently is processed has A)
   * */

  //#define GCODE_ACCEPT_WORD_E

  /**
   * Uncomment to enable module extensions
   * */
// #define ENABLE_MAIN_LOOP_MODULES
// #define ENABLE_IO_MODULES
// #define ENABLE_PARSER_MODULES
// #define ENABLE_INTERPOLATOR_MODULES
// #define ENABLE_SETTINGS_MODULES
// #define ENABLE_PROTOCOL_MODULES

/**
 * Report specific options
 * */
#define STATUS_WCO_REPORT_MIN_FREQUENCY 30
#define STATUS_OVR_REPORT_MIN_FREQUENCY STATUS_WCO_REPORT_MIN_FREQUENCY - 1

  /**
   * If the type of machine supports skew and needs skew correction
   *  (defined in the specified kinematics_xxx.h file)
   * */

#ifdef ENABLE_SKEW_COMPENSATION
// uncomment to correct only in the xy axis
//#define SKEW_COMPENSATION_XY_ONLY
#endif

  /**
   * Changes the planner acceleration profile generation from axis driven to
   * linear actuator driven
   * */

  //#define ENABLE_LINACT_PLANNER
#ifdef ENABLE_LINACT_PLANNER
  // uncomment to do a stop and start if any of the linear actuators is at a
  // still state or changes direction
  //#define ENABLE_LINACT_COLD_START
#endif

  /**
   * If the type of machine need backlash compensation configure here
   * */

  //#define ENABLE_BACKLASH_COMPENSATION

  /**
   * Uncomment these to enable step ISR calculation strategies (uses more
   * memory) STEP_ISR_SKIP_MAIN - carries the information about the main
   * stepper (performs a step in every ISR tick) and skips calculations
   * STEP_ISR_SKIP_IDLE - carries the information about the idle steppers
   * (performs 0 steps in the ISR tick) and skips calculations
   * */

#define STEP_ISR_SKIP_MAIN
#define STEP_ISR_SKIP_IDLE

  /**
   * Sets the maximum number of step doubling loops carried by the DSS (Dynamic
   * Step Spread) algorithm (Similar to Grbl AMASS). The DSS algorithm allows
   * to spread stepps by over sampling bresenham line algorithm at lower
   * frequencies and reduce vibrations of the stepper motors Value should range
   * from 0 to 3. With a value o 0 the DSS will be disabled.
   * */

#define DSS_MAX_OVERSAMPLING 0
#define DSS_CUTOFF_FREQ 500

  /**
   * Modifies the bresenham algorithm to use a 16-version (experimental).
   * This uses less memory, faster ISR stepping, but increases motion and
   * planner calculations since line segments are divided into smaller
   * segments.
   * */

  // #define BRESENHAM_16BIT

  /**
   * Performs motions with variable acceleration (trapezoidal speed profile
   * with roundend speed transition between accel/deaccel and constant speed)
   * instead of constant acceleration (trapezoizal speed profile)
   *
   * */

  // #define ENABLE_S_CURVE_ACCELERATION

  /**
   * Enables legacy step interpolation generator (prior to version 1.4)
   * This runs a variable time window Riemman sum integrator. S-Curve
   * acceleration will have no effect
   * code size will also be reduced
   * */

  // #define USE_LEGACY_STEP_INTERPOLATOR

  /**
   * Forces pin pooling for all limits and control pins (with or without
   * interrupts)
   * */

  //#define FORCE_SOFT_POLLING

  /**
   * Runs a check for state change inside the scheduler. This is a failsafe
   * check to pin ISR checking The value sets the frequency of this safety
   * check that is executed every 2^(CONTROLS_SCHEDULE_CHECK) milliseconds. A
   * negative value will disable this feature. The maximum is 7
   * */

#define CTRL_SCHED_CHECK 4

  /**
   * Disable/enable all control, limits or/and probing input pins. This
   * helps to reduce code size if features are not needed
   * */

#define DISABLE_ALL_CONTROLS
  // #define DISABLE_ALL_LIMITS
  // #define DISABLE_PROBE

  /**
   * Modifies the startup message to emulate Grbl (required by some programs so
   * that uCNC is recognized a Grbl protocol controller device)
   * */

#define EMULATE_GRBL_STARTUP

  /**
   * Enables aditional grbl-type commands
   * For settings allows settings to only be stored in EEPROM/Flash explicitly
   * on special command This makes that all $<setting-id>=<setting-value>
   * commands are only performed in SRAM and not stored directly to
   * EEPROM/Flash A few commands are added: $SS - Settings store - records
   * settings from SRAM to EEPROM/Flash $SL - Settings load - Loads settings
   * from EEPROM/Flash to SRAM $SR - Settings reset - Reloads the default value
   * settings from ROM to SRAM
   *
   * For pin diagnostics enables command $P
   * */

#define ENABLE_EXTRA_SYSTEM_CMDS

  /**
   * Compilation specific options
   * */

  /**
   * ensure all variables are set to 0 at start up
   * */

#define FORCE_GLOBALS_TO_0

  /**
   * saves a little program memory bytes but much more slow CRC check
   * */

#define CRC_WITHOUT_LOOKUP_TABLE

  /**
   * EXPERIMENTAL! Uncomment to enable fast math macros to reduce the number of
   * required cpu cycles needed for a few math operations (mainly on 8-bit
   * processors) This will affect the feed rate precision in about ~5%. Output
   * binary will be bigger. No fast math macros are and shoud be used in
   * functions that calculate coordinates to avoid positional errors except
   * multiply and divide by powers of 2 macros
   * */

  // #define ENABLE_FAST_MATH

#ifdef __cplusplus
}
#endif

#endif
