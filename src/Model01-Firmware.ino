// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif


/**
 * These #include directives pull in the Kaleidoscope firmware core,
 * as well as the Kaleidoscope plugins we use in the Model 01's firmware
 */

#include "Kaleidoscope.h"
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"
#include "Kaleidoscope-FocusSerial.h"
#include "Kaleidoscope-LEDControl.h"
#include "Kaleidoscope-NumPad.h"
#include "Kaleidoscope-LEDEffect-BootGreeting.h"
#include "Kaleidoscope-LEDEffect-SolidColor.h"
#include "Kaleidoscope-LEDEffect-Breathe.h"
#include "Kaleidoscope-LEDEffect-Chase.h"
#include "Kaleidoscope-LEDEffect-Rainbow.h"
#include "Kaleidoscope-LED-Stalker.h"
#include "Kaleidoscope-LED-AlphaSquare.h"
#include "Kaleidoscope-LED-Palette-Theme.h"
#include "Kaleidoscope-Colormap.h"
#include "Kaleidoscope-HardwareTestMode.h"
#include "Kaleidoscope-HostPowerManagement.h"
#include "Kaleidoscope-MagicCombo.h"
#include "Kaleidoscope-USB-Quirks.h"
#include "Kaleidoscope-ModifierLayers.h"

enum { Base
     , Numbers // Programmer dvorak numbers layout
     , Function
     }; // layers

/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// *INDENT-OFF*

KEYMAPS(
  [Base] = KEYMAP_STACKED
  (___,             Key_LeftBracket, LSHIFT(Key_LeftBracket), LSHIFT(Key_RightBracket), LSHIFT(Key_2),    Key_Equals,    Key_LEDEffectNext,
   Key_Backtick,    Key_Quote,       Key_Comma,               Key_Period,               Key_P,            Key_Y,         Key_Tab,
   Key_PageUp,      Key_A,           Key_O,                   Key_E,                    Key_U,            Key_I,
   Key_PageDown,    Key_Semicolon,   Key_Q,                   Key_J,                    Key_K,            Key_X,         Key_Escape,
   Key_Delete,      Key_Backspace,   Key_LeftShift,           Key_LeftAlt,
   Key_LeftControl,

   Key_F12,         LSHIFT(Key_8),   LSHIFT(Key_6),           LSHIFT(Key_Equals),       Key_RightBracket, LSHIFT(Key_1), LSHIFT(Key_3),
   LSHIFT(Key_4),   Key_F,           Key_G,                   Key_C,                    Key_R,            Key_L,         Key_Slash,
                    Key_D,           Key_H,                   Key_T,                    Key_N,            Key_S,         Key_Minus,
   Key_RightGui,    Key_B,           Key_M,                   Key_W,                    Key_V,            Key_Z,         Key_Pipe,
   Key_LeftAlt,     Key_RightShift,  Key_Spacebar,            Key_Enter,
   Key_RightControl),

  // Programmer Dvorak overrides the behavior of a number of keys when shift is
  // held. The ModifierLayers plugin allows us to specify this as a keymap.
  [Numbers] = KEYMAP_STACKED
  (___, Key_7, Key_5, Key_3, Key_1, Key_9, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,

   ___, Key_0, Key_2, Key_4, Key_6, Key_8, Key_Backtick,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___),

  [Function] = KEYMAP_STACKED
  (___,      Key_F7,          Key_F5,                     Key_F3,                   Key_F1,                   Key_F9, ___,
   ___,      ___,             Consumer_ScanPreviousTrack, Consumer_PlaySlashPause,  Consumer_ScanNextTrack,   ___,    ___,
   Key_Home, ___,             Consumer_Mute,              Consumer_VolumeDecrement, Consumer_VolumeIncrement, ___,
   Key_End,  ___,             ___,                        Key_PrintScreen,         Key_Insert,               ___,    ___,
   ___, ___, ___, ___,
   ___,

   ___, Key_F10,       Key_F2,        Key_F4,      Key_F6,         Key_F8, Key_F11,
   ___, ___,           ___,           ___,         ___,            ___,    ___,
        Key_LeftArrow, Key_DownArrow, Key_UpArrow, Key_RightArrow, ___,    ___,
   ___, ___,           ___,           ___,         ___,            ___,    ___,
   ___, ___, ___, ___,
   ___)


  // [Numpad] =  KEYMAP_STACKED
  // (___, ___, ___, ___, ___, ___, ___,
  //  ___, ___, ___, ___, ___, ___, ___,
  //  ___, ___, ___, ___, ___, ___,
  //  ___, ___, ___, ___, ___, ___, ___,
  //  ___, ___, ___, ___,
  //  ___,

  //  M(MACRO_VERSION_INFO),  ___, Key_7, Key_8,      Key_9,              Key_KeypadSubtract, ___,
  //  ___,                    ___, Key_4, Key_5,      Key_6,              Key_KeypadAdd,      ___,
  //                          ___, Key_1, Key_2,      Key_3,              Key_Equals,         ___,
  //  ___,                    ___, Key_0, Key_Period, Key_KeypadMultiply, Key_KeypadDivide,   Key_Enter,
  //  ___, ___, ___, ___,
  //  ___),

) // KEYMAPS(

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*

// These 'solid' color effect definitions define a rainbow of
// LED color modes calibrated to draw 500mA or less on the
// Keyboardio Model 01.

static kaleidoscope::plugin::LEDSolidColor solidRed(160, 0, 0);
static kaleidoscope::plugin::LEDSolidColor solidOrange(140, 70, 0);
static kaleidoscope::plugin::LEDSolidColor solidYellow(130, 100, 0);
static kaleidoscope::plugin::LEDSolidColor solidGreen(0, 160, 0);
static kaleidoscope::plugin::LEDSolidColor solidBlue(0, 70, 130);
static kaleidoscope::plugin::LEDSolidColor solidIndigo(0, 0, 170);
static kaleidoscope::plugin::LEDSolidColor solidViolet(130, 0, 120);

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
 * firmware The names aren't particularly important. What is important is that
 * each is unique.
 *
 * These are the names of your magic combos. They will be used by the
 * `USE_MAGIC_COMBOS` call below.
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
static void toggleKeyboardProtocol(uint8_t combo_index) {
  USBQuirks.toggleKeyboardProtocol();
}

/**
 *  This enters the hardware test mode
 */
static void enterHardwareTestMode(uint8_t combo_index) {
  HardwareTestMode.runTests();
}


/** Magic combo list, a list of key combo and action pairs the firmware should
 * recognise.
 */
USE_MAGIC_COMBOS({.action = toggleKeyboardProtocol,
                  // Left Fn + Esc + Shift
                  .keys = { R3C6, R2C6, R3C7 }
}, {
  .action = enterHardwareTestMode,
  // Left Fn + Prog + LED
  .keys = { R3C6, R0C0, R0C6 }
});

// First, tell Kaleidoscope which plugins you want to use.
// The order can be important. For example, LED effects are
// added in the order they're listed here.
KALEIDOSCOPE_INIT_PLUGINS(
  // The EEPROMSettings & EEPROMKeymap plugins make it possible to have an
  // editable keymap in EEPROM.
  EEPROMSettings,
  EEPROMKeymap,

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
  LEDRainbowEffect,

  // The rainbow wave effect lights up your keyboard with all the colors of a rainbow
  // and slowly moves the rainbow across your keyboard
  LEDRainbowWaveEffect,

  // The chase effect follows the adventure of a blue pixel which chases a red pixel across
  // your keyboard. Spoiler: the blue pixel never catches the red pixel
  LEDChaseEffect,

  // These static effects turn your keyboard's LEDs a variety of colors
  solidRed, solidOrange, solidYellow, solidGreen, solidBlue, solidIndigo, solidViolet,

  // The breathe effect slowly pulses all of the LEDs on your keyboard
  LEDBreatheEffect,

  // The AlphaSquare effect prints each character you type, using your
  // keyboard's LEDs as a display
  AlphaSquareEffect,

  // The stalker effect lights up the keys you've pressed recently
  StalkerEffect,

  // The LED Palette Theme plugin provides a shared palette for other plugins,
  // like Colormap below
  LEDPaletteTheme,

  // The Colormap effect makes it possible to set up per-layer colormaps
  ColormapEffect,

  // The numpad plugin is responsible for lighting up the 'numpad' mode
  // with a custom LED effect
  NumPad,

  // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
  // MouseKeys,

  // The HostPowerManagement plugin allows us to turn LEDs off when then host
  // goes to sleep, and resume them when it wakes up.
  HostPowerManagement,

  // The MagicCombo plugin lets you use key combinations to trigger custom
  // actions - a bit like Macros, but triggered by pressing multiple keys at the
  // same time.
  MagicCombo,

  // The USBQuirks plugin lets you do some things with USB that we aren't
  // comfortable - or able - to do automatically, but can be useful
  // nevertheless. Such as toggling the key report protocol between Boot (used
  // by BIOSes) and Report (NKRO).
  USBQuirks,

  // Use shift to switch layers
  ModifierLayers
);

static const kaleidoscope::ModifierLayers::overlay_t overlays[] = {
  // When either shift key is held, overlay the PDVORAK_NUMBERS layer if the
  // PDVORAK layer is active. Note that keys defined directly in the
  // PDVORAK_NUMBERS will not have the shift modifier applied to them.
  {LAYER_MODIFIER_KEY(Key_LeftShift) | LAYER_MODIFIER_KEY(Key_RightShift), Base, Numbers},
  // The last element must be an all-zero terminator
  {0, 0, 0}
};

/** The 'setup' function is one of the two standard Arduino sketch functions.
 * It's called when your keyboard first powers up. This is where you set up
 * Kaleidoscope and any plugins.
 */
void setup() {
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  // While we hope to improve this in the future, the NumPad plugin
  // needs to be explicitly told which keymap layer is your numpad layer
  // TODO: when figured out layers
  // NumPad.numPadLayer = NUMPAD;

  // We configure the AlphaSquare effect to use RED letters
  AlphaSquare.color = CRGB(255, 0, 0);

  // We set the brightness of the rainbow effects to 150 (on a scale of 0-255)
  // This draws more than 500mA, but looks much nicer than a dimmer effect
  LEDRainbowEffect.brightness(150);
  LEDRainbowWaveEffect.brightness(150);

  // Set the action key the test mode should listen for to Left Fn
  HardwareTestMode.setActionKey(R3C6);

  // The LED Stalker mode has a few effects. The one we like is called
  // 'BlazingTrail'. For details on other options, see
  // https://github.com/keyboardio/Kaleidoscope/blob/master/doc/plugin/LED-Stalker.md
  StalkerEffect.variant = STALKER(BlazingTrail);

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  LEDOff.activate();

  // To make the keymap editable without flashing new firmware, we store
  // additional layers in EEPROM. For now, we reserve space for five layers. If
  // one wants to use these layers, just set the default layer to one in EEPROM,
  // by using the `settings.defaultLayer` Focus command, or by using the
  // `keymap.onlyCustom` command to use EEPROM layers only.
  EEPROMKeymap.setup(5);

  // We need to tell the Colormap plugin how many layers we want to have custom
  // maps for. To make things simple, we set it to five layers, which is how
  // many editable layers we have (see above).
  ColormapEffect.max_layers(5);

  ModifierLayers.overlays = overlays;
}

/** loop is the second of the standard Arduino sketch functions.
  * As you might expect, it runs in a loop, never exiting.
  *
  * For Kaleidoscope-based keyboard firmware, you usually just want to
  * call Kaleidoscope.loop(); and not do anything custom here.
  */

void loop() {
  Kaleidoscope.loop();
}
