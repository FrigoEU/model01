// -*- mode: c++ -*- // Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif



/**
   These #include directives pull in the Kaleidoscope firmware core,
   as well as the Kaleidoscope plugins we use in the Model 01's firmware
*/


// The Kaleidoscope core
#include "Kaleidoscope.h"

// Custom plugins
#include "Kaleidoscope-ModifierLayers.h"

// Support for storing the keymap in EEPROM
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"

// Support for communicating with the host via a simple Serial protocol
#include "Kaleidoscope-FocusSerial.h"

// Support for keys that move the mouse
// #include "Kaleidoscope-MouseKeys.h"

// Support for macros
#include "Kaleidoscope-Macros.h"

// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"

// Support for "Numpad" mode, which is mostly just the Numpad specific LED mode
//#include "Kaleidoscope-NumPad.h"

// Support for the "Boot greeting" effect, which pulses the 'LED' button for 10s
// when the keyboard is connected to a computer (or that computer is powered on)
#include "Kaleidoscope-LEDEffect-BootGreeting.h"

// Support for LED modes that set all LEDs to a single color
// #include "Kaleidoscope-LEDEffect-SolidColor.h"

// Support for an LED mode that makes a red pixel chase a blue pixel across the keyboard
// #include "Kaleidoscope-LEDEffect-Chase.h"

// Support for LED modes that pulse the keyboard's LED in a rainbow pattern
// #include "Kaleidoscope-LEDEffect-Rainbow.h"

// Support for an LED mode that lights up the keys as you press them
// #include "Kaleidoscope-LED-Stalker.h"

// Support for an LED mode that prints the keys you press in letters 4px high
// #include "Kaleidoscope-LED-AlphaSquare.h"

// Support for shared palettes for other plugins, like Colormap below
#include "Kaleidoscope-LED-Palette-Theme.h"

// Support for an LED mode that lets one configure per-layer color maps
// #include "Kaleidoscope-Colormap.h"

// Support for Keyboardio's internal keyboard testing mode
#include "Kaleidoscope-HardwareTestMode.h"

// Support for host power management (suspend & wakeup)
#include "Kaleidoscope-HostPowerManagement.h"

// Support for magic combos (key chords that trigger an action)
//#include "Kaleidoscope-MagicCombo.h"

// Support for USB quirks, like changing the key state report protocol
#include "Kaleidoscope-USB-Quirks.h"


/** This 'enum' is a list of all the macros used by the Model 01's firmware
    The names aren't particularly important. What is important is that each
    is unique.

    These are the names of your macros. They'll be used in two places.
    The first is in your keymap definitions. There, you'll use the syntax
    `M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`

    The second usage is in the 'switch' statement in the `macroAction` function.
    That switch statement actually runs the code associated with a macro when
    a macro key is pressed.
*/

enum { MACRO_VERSION_INFO,
       MACRO_ANY
     };



/** The Model 01's key layouts are defined as 'keymaps'. By default, there are three
  * keymaps: The standard QWERTY keymap, the "Function layer" keymap and the "Numpad"
  * keymap.
  *
  * Each keymap is defined as a list using the 'KEYMAP_STACKED' macro, built
  * of first the left hand's layout, followed by the right hand's layout.
  *
  * Keymaps typically consist mostly of `Key_` definitions. There are many, many keys
  * defined as part of the USB HID Keyboard specification. You can find the names
  * (if not yet the explanations) for all the standard `Key_` defintions offered by
  * Kaleidoscope in these files:
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keyboard.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_consumerctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_sysctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keymaps.h
  *
  * Additional things that should be documented here include
  *   using ___ to let keypresses fall through to the previously active layer
  *   using XXX to mark a keyswitch as 'blocked' on this layer
  *   using ShiftToLayer() and LockLayer() keys to change the active keymap.
  *   keeping NUM and FN consistent and accessible on all layers
  *
  * The PROG key is special, since it is how you indicate to the board that you
  * want to flash the firmware. However, it can be remapped to a regular key.
  * When the keyboard boots, it first looks to see whether the PROG key is held
  * down; if it is, it simply awaits further flashing instructions. If it is
  * not, it continues loading the rest of the firmware and the keyboard
  * functions normally, with whatever binding you have set to PROG. More detail
  * here: https://community.keyboard.io/t/how-the-prog-key-gets-you-into-the-bootloader/506/8
  *
  * The "keymaps" data structure is a list of the keymaps compiled into the firmware.
  * The order of keymaps in the list is important, as the ShiftToLayer(#) and LockLayer(#)
  * macros switch to key layers based on this list.
  *
  *

  * A key defined as 'ShiftToLayer(FUNCTION)' will switch to FUNCTION while held.
  * Similarly, a key defined as 'LockLayer(NUMPAD)' will switch to NUMPAD when tapped.
  */

/**
    Layers are "0-indexed" -- That is the first one is layer 0. The second one is layer 1.
    The third one is layer 2.
    This 'enum' lets us use names like QWERTY, FUNCTION, and NUMPAD in place of
    the numbers 0, 1 and 2.

*/

enum { PRIMARY, PRIMARY_SHIFTED, FUNCTION, NUMPAD }; // layers

/* This comment temporarily turns off astyle's indent enforcement
     so we can make the keymaps actually resemble the physical key layout better
*/
// *INDENT-OFF*


KEYMAPS(
  // Edit this keymap to make a custom layout
  [PRIMARY] = KEYMAP_STACKED
  (___,                  LSHIFT(Key_2), Key_Backtick, LSHIFT(Key_Quote), Key_Quote,         LSHIFT(Key_3), Key_LEDEffectNext,
   LSHIFT(Key_Backtick), Key_A,         Key_Z,        Key_E,             Key_R,             Key_T,         Key_Tab,
   Key_Enter,            Key_Q,         Key_S,        Key_D,             Key_F,             Key_G,
   Key_Spacebar,         Key_W,         Key_X,        Key_C,             Key_V,             Key_B,         ShiftToLayer(NUMPAD),
   Key_LeftControl,      Key_Backspace, Key_LeftGui,  Key_LeftShift,
   ShiftToLayer(FUNCTION),

   ___,           LSHIFT(Key_8), Key_Slash, LSHIFT(Key_1), LSHIFT(Key_6),         LSHIFT(Key_5), ___,
   Key_Enter,     Key_Y,         Key_U,     Key_I,         Key_O,                 Key_P,         LSHIFT(Key_4),
                  Key_H,         Key_J,     Key_K,         Key_L,                 Key_M,         Key_Minus,
   ___,           Key_N,         Key_Comma, Key_Semicolon, LSHIFT(Key_Semicolon), Key_Equals,    Key_Pipe,
   Key_RightShift, Key_LeftAlt, Key_Spacebar, Key_RightControl,
   ShiftToLayer(FUNCTION)),

   [PRIMARY_SHIFTED] = KEYMAP_STACKED
   (___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,

   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
        ___, ___, ___, ___, ___, ___,
   ___, ___, LSHIFT(Key_Slash), Key_Period, Key_Slash, LSHIFT(Key_Equals), LSHIFT(Key_7), 
   ___, ___, ___, ___,
   ___),

//  [NUMPAD] =  KEYMAP_STACKED
//  (___, ___, ___, ___, ___, ___, ___,
//   ___, ___, ___, ___, ___, ___, ___,
//   ___, ___, ___, ___, ___, ___,
//   ___, ___, ___, ___, ___, ___, ___,
//   ___, ___, ___, ___,
//   ___,

//   M(MACRO_VERSION_INFO),  ___, Key_Keypad7, Key_Keypad8,   Key_Keypad9,        Key_KeypadSubtract, ___,
//   ___,                    ___, Key_Keypad4, Key_Keypad5,   Key_Keypad6,        Key_KeypadAdd,      ___,
//                           ___, Key_Keypad1, Key_Keypad2,   Key_Keypad3,        Key_Equals,         ___,
//   ___,                    ___, Key_Keypad0, Key_KeypadDot, Key_KeypadMultiply, Key_KeypadDivide,   Key_Enter,
//   ___, ___, ___, ___,
//   ___),
   
   [FUNCTION] =  KEYMAP_STACKED
  (___,      Key_F1,               Key_F2,                Key_F3,      Key_F4,                 Key_F5,                  ___,           
   Key_Home, Key_LeftCurlyBracket, Key_RightCurlyBracket, Key_Pipe,    LSHIFT(Key_Comma)/*<*/, LSHIFT(Key_Period)/*>*/, ___,
   Key_Tab,  Key_Escape,           Key_LeftBracket,       Key_Period,  Key_RightBracket,       Key_Equals,     
   Key_End,  Key_F6,               Key_F7,                Key_F8,      Key_F9,                 Key_F10,                 ___,
   ___, Key_Delete, ___, ___,
   ___,

   Consumer_ScanPreviousTrack, Key_F6,                 Key_F7,                   Key_F8,                   Key_F9,          Key_F10,          Key_F11,
   Consumer_PlaySlashPause,    Consumer_ScanNextTrack, LSHIFT(Key_9),            LSHIFT(Key_0),            Key_LeftBracket, Key_RightBracket, Key_F12,
                               Key_LeftArrow,          Key_DownArrow,            Key_UpArrow,              Key_RightArrow,  Key_Enter,        ___,
   ___,                        Consumer_Mute,          Consumer_VolumeDecrement, Consumer_VolumeIncrement, Key_Backslash,   Key_Backslash,    Key_Pipe,
   ___, ___, Key_Enter, ___,
   ___),

  [NUMPAD] = KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,

   ___, ___, ___,   ___,   ___,   ___,   ___,
   ___, ___, Key_7, Key_8, Key_9, ___,   ___,
        ___, Key_4, Key_5, Key_6, ___,   ___,
   ___, ___, Key_1, Key_2, Key_3, Key_0, ___, 
   ___, ___, ___, ___,
   ___)
); // KEYMAPS(

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*

static const kaleidoscope::ModifierLayers::overlay_t overlays[] = {
  // When either shift key is held, overlay the PRIMARY_SHIFTED layer if the
  // PRIMARY layer is active. Note that keys defined directly in the
  // PRIMARY_SHIFTED will not have the shift modifier applied to them.
  {LAYER_MODIFIER_KEY(Key_LeftShift) | LAYER_MODIFIER_KEY(Key_RightShift), 
   PRIMARY, 
   PRIMARY_SHIFTED},
  // The last element must be an all-zero terminator
  {0, 0, 0}
};

/** versionInfoMacro handles the 'firmware version info' macro
    When a key bound to the macro is pressed, this macro
    prints out the firmware build information as virtual keystrokes
*/

/*
static void versionInfoMacro(uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
    Macros.type(PSTR(BUILD_INFORMATION));
  }
}
*/

/** anyKeyMacro is used to provide the functionality of the 'Any' key.

   When the 'any key' macro is toggled on, a random alphanumeric key is
   selected. While the key is held, the function generates a synthetic
   keypress event repeating that randomly selected key.

*/

/*
static void anyKeyMacro(uint8_t keyState) {
  static Key lastKey;
  bool toggledOn = false;
  if (keyToggledOn(keyState)) {
    lastKey.keyCode = Key_A.keyCode + (uint8_t)(millis() % 36);
    toggledOn = true;
  }

  if (keyIsPressed(keyState))
    kaleidoscope::hid::pressKey(lastKey, toggledOn);
}
*/


/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

*/

/*
const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {

    case MACRO_VERSION_INFO:
      versionInfoMacro(keyState);
      break;

    case MACRO_ANY:
      anyKeyMacro(keyState);
      break;
  }
  return MACRO_NONE;
}
*/



// These 'solid' color effect definitions define a rainbow of
// LED color modes calibrated to draw 500mA or less on the
// Keyboardio Model 01.


// static kaleidoscope::plugin::LEDSolidColor solidRed(160, 0, 0);
// static kaleidoscope::plugin::LEDSolidColor solidOrange(140, 70, 0);
// static kaleidoscope::plugin::LEDSolidColor solidYellow(130, 100, 0);
// static kaleidoscope::plugin::LEDSolidColor solidGreen(0, 160, 0);
// static kaleidoscope::plugin::LEDSolidColor solidBlue(0, 70, 130);
// static kaleidoscope::plugin::LEDSolidColor solidIndigo(0, 0, 170);
// static kaleidoscope::plugin::LEDSolidColor solidViolet(130, 0, 120);

/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::plugin::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::plugin::HostPowerManagement::Suspend:
    LEDControl.set_all_leds_to({0, 0, 0});
    LEDControl.syncLeds();
    LEDControl.paused = true;
    break;
  case kaleidoscope::plugin::HostPowerManagement::Resume:
    LEDControl.paused = false;
    LEDControl.refreshAll();
    break;
  case kaleidoscope::plugin::HostPowerManagement::Sleep:
    break;
  }
}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::plugin::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}

/** This 'enum' is a list of all the magic combos used by the Model 01's
   firmware The names aren't particularly important. What is important is that
   each is unique.

   These are the names of your magic combos. They will be used by the
   `USE_MAGIC_COMBOS` call below.
*/
enum {
  // Toggle between Boot (6-key rollover; for BIOSes and early boot) and NKRO
  // mode.
  COMBO_TOGGLE_NKRO_MODE,
  // Enter test mode
  COMBO_ENTER_TEST_MODE
};

/** Wrappers, to be used by MagicCombo. **/

/**
 * This simply toggles the keyboard protocol via USBQuirks, and wraps it within
 * a function with an unused argument, to match what MagicCombo expects.
 */
// static void toggleKeyboardProtocol(uint8_t combo_index) {
//   USBQuirks.toggleKeyboardProtocol();
// }

/**
 *  This enters the hardware test mode
 */
// static void enterHardwareTestMode(uint8_t combo_index) {
//   HardwareTestMode.runTests();
// }


/** Magic combo list, a list of key combo and action pairs the firmware should
   recognise.
*/
/*
USE_MAGIC_COMBOS({.action = toggleKeyboardProtocol,
                  // Left Fn + Esc + Shift
                  .keys = { R3C6, R2C6, R3C7 }
}, {
  .action = enterHardwareTestMode,
  // Left Fn + Prog + LED
  .keys = { R3C6, R0C0, R0C6 }
});
*/

// kaleidoscope::plugin::LEDFunctionalColor::FunctionalColor funColor;
// kaleidoscope::plugin::ledfunctionalcolor::FunctionalColor funColor1(200, kaleidoscope::plugin::LEDFunctionalColor::Fruit);

// using namespace kaleidoscope::plugin::LEDFunctionalColor;

// FunctionalColor funColorMyTheme;
// struct myTheme: public colorMapMono {
//   FC_MAP_COLOR(defaultColor, nocolor);

//   FC_MAP_COLOR(shift, skyblue)
//   FC_MAP_COLOR(control, skyblue)
//   FC_MAP_COLOR(alt, skyblue)
//   FC_MAP_COLOR(gui, skyblue)

//   FC_MAP_COLOR(space, pink)
//   FC_MAP_COLOR(enter, pink)
//   FC_MAP_COLOR(backspace, pink)

//   FC_MAP_COLOR(media, purple)
//   FC_MAP_COLOR(arrow, purple)

//   FC_MAP_COLOR(alpha, blue)
//   FC_MAP_COLOR(number, yellow)
//   FC_MAP_COLOR(punctuation, orange)

//   //You can also set something to "nocolor" which will avoid coloring a set of keys
//   // if they already are part of another larger group - ie set shift to nocolor and
//   // shiftkeys will inherit the color assigned to modifier
//   // FC_MAP_COLOR(shift, nocolor);
// };

// static constexpr tuple<byte, byte> layout_to_number[4][16] = KEYMAP_STACKED
//   (0, 0, 1, 1, 0, 0, 0,
//    0, 0, 1, 1, 0, 0, 0,
//    0, 0, 1, 1, 0, 0,
//    0, 0, 1, 1, 0, 0, 0,
//    0, 0, 1, 1,
//    0,

//    1, 1, 0, 0, 1, 1, 1,
//    1, 1, 0, 0, 1, 1, 1,
//    1, 1, 0, 0, 1, 1,
//    1, 1, 0, 0, 1, 1, 1,
//    1, 1, 0, 0,
//    1)

// static constexpr uint8_t key_led_map[4][16] = {
//   {3, 4, 11, 12, 19, 20, 26, 27,     36, 37, 43, 44, 51, 52, 59, 60},
//   {2, 5, 10, 13, 18, 21, 25, 28,     35, 38, 42, 45, 50, 53, 58, 61},
//   {1, 6, 9, 14, 17, 22, 24, 29,     34, 39, 41, 46, 49, 54, 57, 62},
//   {0, 7, 8, 15, 16, 23, 31, 30,     33, 32, 40, 47, 48, 55, 56, 63},
// };


namespace kaleidoscope {
  namespace plugin {

    class MyLEDTheme : public LEDMode {
    public:
      MyLEDTheme(void) {}

      void update(void) final {
        if (Layer.isActive(PRIMARY)) {
            
        // http://www.keyboard-layout-editor.com/#/gists/5311d4007dc7ed12df81487a1f82bb23

          // left row 1
          ::LEDControl.setCrgbAt(3, black);
          ::LEDControl.setCrgbAt(4, letters);
          ::LEDControl.setCrgbAt(11, letters);
          ::LEDControl.setCrgbAt(12, letters);
          ::LEDControl.setCrgbAt(19, letters);
          ::LEDControl.setCrgbAt(20, letters);
          ::LEDControl.setCrgbAt(26, black);

          // left row 2
          ::LEDControl.setCrgbAt(2, black);
          ::LEDControl.setCrgbAt(5, letters);
          ::LEDControl.setCrgbAt(10, letters);
          ::LEDControl.setCrgbAt(13, letters);
          ::LEDControl.setCrgbAt(18, letters);
          ::LEDControl.setCrgbAt(21, letters);
          ::LEDControl.setCrgbAt(25, black);

          // left row 3 (no "middle" button)
          ::LEDControl.setCrgbAt(1, extras);
          ::LEDControl.setCrgbAt(6, letters);
          ::LEDControl.setCrgbAt(9, letters);
          ::LEDControl.setCrgbAt(14, letters);
          ::LEDControl.setCrgbAt(17, letters);
          ::LEDControl.setCrgbAt(22, letters);

          // left row 4
          ::LEDControl.setCrgbAt(0, extras);
          ::LEDControl.setCrgbAt(7, letters);
          ::LEDControl.setCrgbAt(8, letters);
          ::LEDControl.setCrgbAt(15, letters);
          ::LEDControl.setCrgbAt(16, letters);
          ::LEDControl.setCrgbAt(23, letters);
          ::LEDControl.setCrgbAt(24, modifiers);

          // thumb left
          ::LEDControl.setCrgbAt(27, modifiers);
          ::LEDControl.setCrgbAt(28, modifiers);
          ::LEDControl.setCrgbAt(29, modifiers);
          ::LEDControl.setCrgbAt(30, modifiers);

          // fn left
          ::LEDControl.setCrgbAt(31, modifiers);

          // fn right
          ::LEDControl.setCrgbAt(32, modifiers);

          // thumb right
          ::LEDControl.setCrgbAt(33, modifiers);
          ::LEDControl.setCrgbAt(34, modifiers);
          ::LEDControl.setCrgbAt(35, modifiers);
          ::LEDControl.setCrgbAt(36, modifiers);

          // right row 1
          ::LEDControl.setCrgbAt(37, black);
          ::LEDControl.setCrgbAt(43, letters);
          ::LEDControl.setCrgbAt(44, letters);
          ::LEDControl.setCrgbAt(51, letters);
          ::LEDControl.setCrgbAt(52, letters);
          ::LEDControl.setCrgbAt(59, letters);
          ::LEDControl.setCrgbAt(60, black);

          // right row 2
          ::LEDControl.setCrgbAt(38, black);
          ::LEDControl.setCrgbAt(42, letters);
          ::LEDControl.setCrgbAt(45, letters);
          ::LEDControl.setCrgbAt(50, letters);
          ::LEDControl.setCrgbAt(53, letters);
          ::LEDControl.setCrgbAt(58, letters);
          ::LEDControl.setCrgbAt(61, letters);

          // right row 3 (no "middle" button)
          ::LEDControl.setCrgbAt(41, letters);
          ::LEDControl.setCrgbAt(46, letters);
          ::LEDControl.setCrgbAt(49, letters);
          ::LEDControl.setCrgbAt(54, letters);
          ::LEDControl.setCrgbAt(57, letters);
          ::LEDControl.setCrgbAt(62, letters);

          // right row 4
          ::LEDControl.setCrgbAt(39, black);
          ::LEDControl.setCrgbAt(40, letters);
          ::LEDControl.setCrgbAt(47, letters);
          ::LEDControl.setCrgbAt(48, letters);
          ::LEDControl.setCrgbAt(55, letters);
          ::LEDControl.setCrgbAt(56, letters);
          ::LEDControl.setCrgbAt(63, letters);
            }

        if (Layer.isActive(PRIMARY_SHIFTED)) {
          // left row 1
          ::LEDControl.setCrgbAt(3, black);
          ::LEDControl.setCrgbAt(4, black);
          ::LEDControl.setCrgbAt(11, black);
          ::LEDControl.setCrgbAt(12, black);
          ::LEDControl.setCrgbAt(19, black);
          ::LEDControl.setCrgbAt(20, black);
          ::LEDControl.setCrgbAt(26, black);

          // left row 2
          ::LEDControl.setCrgbAt(2, black);
          ::LEDControl.setCrgbAt(5, black);
          ::LEDControl.setCrgbAt(10, black);
          ::LEDControl.setCrgbAt(13, black);
          ::LEDControl.setCrgbAt(18, black);
          ::LEDControl.setCrgbAt(21, black);
          ::LEDControl.setCrgbAt(25, black);

          // left row 3 (no "middle" button)
          ::LEDControl.setCrgbAt(1, black);
          ::LEDControl.setCrgbAt(6, black);
          ::LEDControl.setCrgbAt(9, black);
          ::LEDControl.setCrgbAt(14, black);
          ::LEDControl.setCrgbAt(17, black);
          ::LEDControl.setCrgbAt(22, black);

          // left row 4
          ::LEDControl.setCrgbAt(0, black);
          ::LEDControl.setCrgbAt(7, black);
          ::LEDControl.setCrgbAt(8, black);
          ::LEDControl.setCrgbAt(15, black);
          ::LEDControl.setCrgbAt(16, black);
          ::LEDControl.setCrgbAt(23, black);
          ::LEDControl.setCrgbAt(24, black);

          // thumb left
          ::LEDControl.setCrgbAt(27, black);
          ::LEDControl.setCrgbAt(28, black);
          ::LEDControl.setCrgbAt(29, black);
          ::LEDControl.setCrgbAt(30, black);

          // fn left
          ::LEDControl.setCrgbAt(31, black);

          // fn right
          ::LEDControl.setCrgbAt(32, black);

          // thumb right
          ::LEDControl.setCrgbAt(33, black);
          ::LEDControl.setCrgbAt(34, black);
          ::LEDControl.setCrgbAt(35, black);
          ::LEDControl.setCrgbAt(36, black);

          // right row 1
          ::LEDControl.setCrgbAt(37, black);
          ::LEDControl.setCrgbAt(43, black);
          ::LEDControl.setCrgbAt(44, black);
          ::LEDControl.setCrgbAt(51, black);
          ::LEDControl.setCrgbAt(52, black);
          ::LEDControl.setCrgbAt(59, black);
          ::LEDControl.setCrgbAt(60, black);

          // right row 2
          ::LEDControl.setCrgbAt(38, black);
          ::LEDControl.setCrgbAt(42, black);
          ::LEDControl.setCrgbAt(45, black);
          ::LEDControl.setCrgbAt(50, black);
          ::LEDControl.setCrgbAt(53, black);
          ::LEDControl.setCrgbAt(58, black);
          ::LEDControl.setCrgbAt(61, letters);

          // right row 3 (no "middle" button)
          ::LEDControl.setCrgbAt(41, black);
          ::LEDControl.setCrgbAt(46, black);
          ::LEDControl.setCrgbAt(49, black);
          ::LEDControl.setCrgbAt(54, black);
          ::LEDControl.setCrgbAt(57, black);
          ::LEDControl.setCrgbAt(62, letters);

          // right row 4
          ::LEDControl.setCrgbAt(39, black);
          ::LEDControl.setCrgbAt(40, black);
          ::LEDControl.setCrgbAt(47, letters);
          ::LEDControl.setCrgbAt(48, letters);
          ::LEDControl.setCrgbAt(55, letters);
          ::LEDControl.setCrgbAt(56, letters);
          ::LEDControl.setCrgbAt(63, letters);
          }

        if (Layer.isActive(NUMPAD)) {
          // left row 1
          ::LEDControl.setCrgbAt(3, black);
          ::LEDControl.setCrgbAt(4, black);
          ::LEDControl.setCrgbAt(11, black);
          ::LEDControl.setCrgbAt(12, black);
          ::LEDControl.setCrgbAt(19, black);
          ::LEDControl.setCrgbAt(20, black);
          ::LEDControl.setCrgbAt(26, black);

          // left row 2
          ::LEDControl.setCrgbAt(2, black);
          ::LEDControl.setCrgbAt(5, black);
          ::LEDControl.setCrgbAt(10, black);
          ::LEDControl.setCrgbAt(13, black);
          ::LEDControl.setCrgbAt(18, black);
          ::LEDControl.setCrgbAt(21, black);
          ::LEDControl.setCrgbAt(25, black);

          // left row 3 (no "middle" button)
          ::LEDControl.setCrgbAt(1, black);
          ::LEDControl.setCrgbAt(6, black);
          ::LEDControl.setCrgbAt(9, black);
          ::LEDControl.setCrgbAt(14, black);
          ::LEDControl.setCrgbAt(17, black);
          ::LEDControl.setCrgbAt(22, black);

          // left row 4
          ::LEDControl.setCrgbAt(0, black);
          ::LEDControl.setCrgbAt(7, black);
          ::LEDControl.setCrgbAt(8, black);
          ::LEDControl.setCrgbAt(15, black);
          ::LEDControl.setCrgbAt(16, black);
          ::LEDControl.setCrgbAt(23, black);
          ::LEDControl.setCrgbAt(24, black);

          // thumb left
          ::LEDControl.setCrgbAt(27, black);
          ::LEDControl.setCrgbAt(28, black);
          ::LEDControl.setCrgbAt(29, black);
          ::LEDControl.setCrgbAt(30, black);

          // fn left
          ::LEDControl.setCrgbAt(31, black);

          // fn right
          ::LEDControl.setCrgbAt(32, black);

          // thumb right
          ::LEDControl.setCrgbAt(33, black);
          ::LEDControl.setCrgbAt(34, black);
          ::LEDControl.setCrgbAt(35, black);
          ::LEDControl.setCrgbAt(36, black);

          // right row 1
          ::LEDControl.setCrgbAt(37, black);
          ::LEDControl.setCrgbAt(43, black);
          ::LEDControl.setCrgbAt(44, black);
          ::LEDControl.setCrgbAt(51, black);
          ::LEDControl.setCrgbAt(52, black);
          ::LEDControl.setCrgbAt(59, black);
          ::LEDControl.setCrgbAt(60, black);

          // right row 2
          ::LEDControl.setCrgbAt(38, black);
          ::LEDControl.setCrgbAt(42, black);
          ::LEDControl.setCrgbAt(45, arrows);
          ::LEDControl.setCrgbAt(50, arrows);
          ::LEDControl.setCrgbAt(53, arrows);
          ::LEDControl.setCrgbAt(58, black);
          ::LEDControl.setCrgbAt(61, black);

          // right row 3 (no "middle" button)
          ::LEDControl.setCrgbAt(41, black);
          ::LEDControl.setCrgbAt(46, arrows);
          ::LEDControl.setCrgbAt(49, arrows);
          ::LEDControl.setCrgbAt(54, arrows);
          ::LEDControl.setCrgbAt(57, black);
          ::LEDControl.setCrgbAt(62, black);

          // right row 4
          ::LEDControl.setCrgbAt(39, black);
          ::LEDControl.setCrgbAt(40, black);
          ::LEDControl.setCrgbAt(47, arrows);
          ::LEDControl.setCrgbAt(48, arrows);
          ::LEDControl.setCrgbAt(55, arrows);
          ::LEDControl.setCrgbAt(56, arrows);
          ::LEDControl.setCrgbAt(63, black);
          }

        if (Layer.isActive(FUNCTION)) {
          // left row 1
          ::LEDControl.setCrgbAt(3, black);
          ::LEDControl.setCrgbAt(4, black);
          ::LEDControl.setCrgbAt(11, black);
          ::LEDControl.setCrgbAt(12, black);
          ::LEDControl.setCrgbAt(19, black);
          ::LEDControl.setCrgbAt(20, black);
          ::LEDControl.setCrgbAt(26, black);

          // left row 2
          ::LEDControl.setCrgbAt(2, black);
          ::LEDControl.setCrgbAt(5, brackets);
          ::LEDControl.setCrgbAt(10, brackets);
          ::LEDControl.setCrgbAt(13, black);
          ::LEDControl.setCrgbAt(18, brackets);
          ::LEDControl.setCrgbAt(21, brackets);
          ::LEDControl.setCrgbAt(25, black);

          // left row 3 (no "middle" button)
          ::LEDControl.setCrgbAt(1, black);
          ::LEDControl.setCrgbAt(6, extras);
          ::LEDControl.setCrgbAt(9, black);
          ::LEDControl.setCrgbAt(14, black);
          ::LEDControl.setCrgbAt(17, black);
          ::LEDControl.setCrgbAt(22, black);

          // left row 4
          ::LEDControl.setCrgbAt(0, black);
          ::LEDControl.setCrgbAt(7, black);
          ::LEDControl.setCrgbAt(8, black);
          ::LEDControl.setCrgbAt(15, black);
          ::LEDControl.setCrgbAt(16, black);
          ::LEDControl.setCrgbAt(23, black);
          ::LEDControl.setCrgbAt(24, black);

          // thumb left
          ::LEDControl.setCrgbAt(27, black);
          ::LEDControl.setCrgbAt(28, black);
          ::LEDControl.setCrgbAt(29, black);
          ::LEDControl.setCrgbAt(30, black);

          // fn left
          ::LEDControl.setCrgbAt(31, black);

          // fn right
          ::LEDControl.setCrgbAt(32, black);

          // thumb right
          ::LEDControl.setCrgbAt(33, black);
          ::LEDControl.setCrgbAt(34, black);
          ::LEDControl.setCrgbAt(35, black);
          ::LEDControl.setCrgbAt(36, black);

          // right row 1
          ::LEDControl.setCrgbAt(37, modifiers);
          ::LEDControl.setCrgbAt(43, black);
          ::LEDControl.setCrgbAt(44, black);
          ::LEDControl.setCrgbAt(51, black);
          ::LEDControl.setCrgbAt(52, black);
          ::LEDControl.setCrgbAt(59, black);
          ::LEDControl.setCrgbAt(60, black);

          // right row 2
          ::LEDControl.setCrgbAt(38, modifiers);
          ::LEDControl.setCrgbAt(42, modifiers);
          ::LEDControl.setCrgbAt(45, brackets);
          ::LEDControl.setCrgbAt(50, brackets);
          ::LEDControl.setCrgbAt(53, brackets);
          ::LEDControl.setCrgbAt(58, brackets);
          ::LEDControl.setCrgbAt(61, black);

          // right row 3 (no "middle" button)
          ::LEDControl.setCrgbAt(41, arrows);
          ::LEDControl.setCrgbAt(46, arrows);
          ::LEDControl.setCrgbAt(49, arrows);
          ::LEDControl.setCrgbAt(54, arrows);
          ::LEDControl.setCrgbAt(57, extras);
          ::LEDControl.setCrgbAt(62, black);

          // right row 4
          ::LEDControl.setCrgbAt(39, black);
          ::LEDControl.setCrgbAt(40, modifiers);
          ::LEDControl.setCrgbAt(47, modifiers);
          ::LEDControl.setCrgbAt(48, modifiers);
          ::LEDControl.setCrgbAt(55, black);
          ::LEDControl.setCrgbAt(56, black);
          ::LEDControl.setCrgbAt(63, black);
          }
      }

    private:
      cRGB black = CRGB(0, 0, 0);

      cRGB red = CRGB(160, 0, 0);
      cRGB orange = CRGB(140, 70, 0);
      cRGB yellow = CRGB(130, 100, 0);
      cRGB green = CRGB(0, 160, 0);
      cRGB blue = CRGB(0, 70, 130);
      cRGB indigo = CRGB(0, 0, 170);
      cRGB violet = CRGB(130, 0, 120);

      cRGB letters = orange;
      cRGB modifiers = blue;
      cRGB brackets = yellow;
      cRGB extras = violet;
      cRGB arrows = green;
    };
  }
}

kaleidoscope::plugin::MyLEDTheme MyLEDTheme;

// First, tell Kaleidoscope which plugins you want to use.
// The order can be important. For example, LED effects are
// added in the order they're listed here.
KALEIDOSCOPE_INIT_PLUGINS(

  ModifierLayers,

  MyLEDTheme,

  // funColor,
  // funColor1,
  // funColorMyTheme,

  // The EEPROMSettings & EEPROMKeymap plugins make it possible to have an
  // editable keymap in EEPROM.
 //  EEPROMSettings,
 // EEPROMKeymap,

  // Focus allows bi-directional communication with the host, and is the
  // interface through which the keymap in EEPROM can be edited.
  Focus,

  // FocusSettingsCommand adds a few Focus commands, intended to aid in
  // changing some settings of the keyboard, such as the default layer (via the
  // `settings.defaultLayer` command)
  FocusSettingsCommand,

  // FocusEEPROMCommand adds a set of Focus commands, which are very helpful in
  // both debugging, and in backing up one's EEPROM contents.
  FocusEEPROMCommand,

  // The boot greeting effect pulses the LED button for 10 seconds after the
  // keyboard is first connected
  BootGreetingEffect,

  // The hardware test mode, which can be invoked by tapping Prog, LED and the
  // left Fn button at the same time.
  HardwareTestMode,

  // LEDControl provides support for other LED modes
  LEDControl,

  // We start with the LED effect that turns off all the LEDs.
  LEDOff,

  // The rainbow effect changes the color of all of the keyboard's keys at the same time
  // running through all the colors of the rainbow.
  // LEDRainbowEffect,

  // The rainbow wave effect lights up your keyboard with all the colors of a rainbow
  // and slowly moves the rainbow across your keyboard
  // LEDRainbowWaveEffect,

  // The chase effect follows the adventure of a blue pixel which chases a red pixel across
  // your keyboard. Spoiler: the blue pixel never catches the red pixel
  // LEDChaseEffect,

  // These static effects turn your keyboard's LEDs a variety of colors
  // solidRed, solidOrange, solidYellow, solidGreen, solidBlue, solidIndigo, solidViolet,

  // The breathe effect slowly pulses all of the LEDs on your keyboard
  // LEDBreatheEffect,

  // The AlphaSquare effect prints each character you type, using your
  // keyboard's LEDs as a display
  // AlphaSquareEffect,

  // The stalker effect lights up the keys you've pressed recently
  // StalkerEffect,

  // The LED Palette Theme plugin provides a shared palette for other plugins,
  // like Colormap below
  // LEDPaletteTheme,

  // The Colormap effect makes it possible to set up per-layer colormaps
  // ColormapEffect,

  // The numpad plugin is responsible for lighting up the 'numpad' mode
  // with a custom LED effect
//  NumPad,

  // The macros plugin adds support for macros
//  Macros,

  // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
//  MouseKeys,

  // The HostPowerManagement plugin allows us to turn LEDs off when then host
  // goes to sleep, and resume them when it wakes up.
  HostPowerManagement,

  // The MagicCombo plugin lets you use key combinations to trigger custom
  // actions - a bit like Macros, but triggered by pressing multiple keys at the
  // same time.
//  MagicCombo,

  // The USBQuirks plugin lets you do some things with USB that we aren't
  // comfortable - or able - to do automatically, but can be useful
  // nevertheless. Such as toggling the key report protocol between Boot (used
  // by BIOSes) and Report (NKRO).
  USBQuirks
);

/** The 'setup' function is one of the two standard Arduino sketch functions.
   It's called when your keyboard first powers up. This is where you set up
   Kaleidoscope and any plugins.
*/

void setup() {
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();
  ModifierLayers.overlays = overlays;
  Layer.activate(PRIMARY); // Persoonlijke touch om nieuwe versie van ModifierLayers te laten werken

  // FC_SET_THEME(funColorMyTheme, myTheme);

  // While we hope to improve this in the future, the NumPad plugin
  // needs to be explicitly told which keymap layer is your numpad layer
//  NumPad.numPadLayer = NUMPAD;

  // We configure the AlphaSquare effect to use RED letters
  // AlphaSquare.color = CRGB(255, 0, 0);

  // We set the brightness of the rainbow effects to 150 (on a scale of 0-255)
  // This draws more than 500mA, but looks much nicer than a dimmer effect
  // LEDRainbowEffect.brightness(150);
  // LEDRainbowWaveEffect.brightness(150);

  // Set the action key the test mode should listen for to Left Fn
  HardwareTestMode.setActionKey(R3C6);

  // The LED Stalker mode has a few effects. The one we like is called
  // 'BlazingTrail'. For details on other options, see
  // https://github.com/keyboardio/Kaleidoscope/blob/master/doc/plugin/LED-Stalker.md
  // StalkerEffect.variant = STALKER(BlazingTrail);

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  LEDOff.activate();

  // To make the keymap editable without flashing new firmware, we store
  // additional layers in EEPROM. For now, we reserve space for five layers. If
  // one wants to use these layers, just set the default layer to one in EEPROM,
  // by using the `settings.defaultLayer` Focus command, or by using the
  // `keymap.onlyCustom` command to use EEPROM layers only.
  // EEPROMKeymap.setup(5);

  // We need to tell the Colormap plugin how many layers we want to have custom
  // maps for. To make things simple, we set it to five layers, which is how
  // many editable layers we have (see above).
  // ColormapEffect.max_layers(5);
}

/** loop is the second of the standard Arduino sketch functions.
    As you might expect, it runs in a loop, never exiting.

    For Kaleidoscope-based keyboard firmware, you usually just want to
    call Kaleidoscope.loop(); and not do anything custom here.
*/

void loop() {
  Kaleidoscope.loop();
}
