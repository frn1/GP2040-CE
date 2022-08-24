/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: Copyright (c) 2021 Jason Skuby (mytechtoybox.com)
 */

#include "storagemanager.h"

#include <GamepadStorage.h>
#include <sstream>
#include "Animation.hpp"
#include "AnimationStation/src/Effects/StaticColor.hpp"
#include "AnimationStorage.hpp"
#include "BoardConfig.h"
#include "CRC32.h"
#include "FlashPROM.h"
#include "hardware/watchdog.h"

#include "addons/i2cdisplay.h"
#include "addons/neopicoleds.h"
#include "addons/playerleds.h"

#include "inputs/turbo.h"

#include "helper.h"

/* Board stuffs */
void Storage::initBoardOptions() {
  EEPROM.get(BOARD_STORAGE_INDEX, boardOptions);
  uint32_t lastCRC      = boardOptions.checksum;
  boardOptions.checksum = CHECKSUM_MAGIC;
  if (lastCRC != CRC32::calculate(&boardOptions, sizeof(BoardOptions))) {
    setDefaultBoardOptions();
  }
}

BoardOptions Storage::getBoardOptions() {
  return boardOptions;
}

void Storage::setDefaultBoardOptions() {
  // Set GP2040 version string and 0 mem after
  boardOptions.hasBoardOptions    = false;
  boardOptions.pinDpadUp          = PIN_DPAD_UP;
  boardOptions.pinDpadDown        = PIN_DPAD_DOWN;
  boardOptions.pinDpadLeft        = PIN_DPAD_LEFT;
  boardOptions.pinDpadRight       = PIN_DPAD_RIGHT;
  boardOptions.pinButtonB1        = PIN_BUTTON_B1;
  boardOptions.pinButtonB2        = PIN_BUTTON_B2;
  boardOptions.pinButtonB3        = PIN_BUTTON_B3;
  boardOptions.pinButtonB4        = PIN_BUTTON_B4;
  boardOptions.pinButtonL1        = PIN_BUTTON_L1;
  boardOptions.pinButtonR1        = PIN_BUTTON_R1;
  boardOptions.pinButtonL2        = PIN_BUTTON_L2;
  boardOptions.pinButtonR2        = PIN_BUTTON_R2;
  boardOptions.pinButtonS1        = PIN_BUTTON_S1;
  boardOptions.pinButtonS2        = PIN_BUTTON_S2;
  boardOptions.pinButtonL3        = PIN_BUTTON_L3;
  boardOptions.pinButtonR3        = PIN_BUTTON_R3;
  boardOptions.pinButtonA1        = PIN_BUTTON_A1;
  boardOptions.pinButtonA2        = PIN_BUTTON_A2;
  boardOptions.pinButtonTurbo     = PIN_BUTTON_TURBO;
  boardOptions.pinSliderLS        = PIN_SLIDER_LS;
  boardOptions.pinSliderRS        = PIN_SLIDER_RS;
  boardOptions.pinLeftSliderS0    = PIN_LEFT_SLIDER_S0;
  boardOptions.pinLeftSliderS1    = PIN_LEFT_SLIDER_S1;
  boardOptions.pinLeftSliderS2    = PIN_LEFT_SLIDER_S2;
  boardOptions.pinLeftSliderS3    = PIN_LEFT_SLIDER_S3;
  boardOptions.pinLeftSliderCOM0  = PIN_LEFT_SLIDER_COM0;
  boardOptions.pinLeftSliderCOM1  = PIN_LEFT_SLIDER_COM1;
  boardOptions.pinRightSliderS0   = PIN_RIGHT_SLIDER_S0;
  boardOptions.pinRightSliderS1   = PIN_RIGHT_SLIDER_S1;
  boardOptions.pinRightSliderS2   = PIN_RIGHT_SLIDER_S2;
  boardOptions.pinRightSliderS3   = PIN_RIGHT_SLIDER_S3;
  boardOptions.pinRightSliderCOM0 = PIN_RIGHT_SLIDER_COM0;
  boardOptions.pinRightSliderCOM1 = PIN_RIGHT_SLIDER_COM1;
  boardOptions.buttonLayout       = BUTTON_LAYOUT;
  boardOptions.i2cSDAPin          = I2C_SDA_PIN;
  boardOptions.i2cSCLPin          = I2C_SCL_PIN;
  boardOptions.i2cBlock           = (I2C_BLOCK == i2c0) ? 0 : 1;
  boardOptions.i2cSpeed           = I2C_SPEED;
  boardOptions.hasI2CDisplay      = HAS_I2C_DISPLAY;
  boardOptions.displayI2CAddress  = DISPLAY_I2C_ADDR;
  boardOptions.displaySize        = DISPLAY_SIZE;
  boardOptions.displayFlip        = DISPLAY_FLIP;
  boardOptions.displayInvert      = DISPLAY_INVERT;
  boardOptions.turboShotCount     = DEFAULT_SHOT_PER_SEC;
  boardOptions.checksum           = CHECKSUM_MAGIC;  // set checksum to magic number
  boardOptions.checksum           = CRC32::calculate(&boardOptions);
  EEPROM.set(BOARD_STORAGE_INDEX, boardOptions);
}

void Storage::setBoardOptions(BoardOptions options) {
  options.checksum = CHECKSUM_MAGIC;  // set checksum to magic number
  options.checksum = CRC32::calculate(&options);
  EEPROM.set(BOARD_STORAGE_INDEX, options);
  memcpy(&boardOptions, &options, sizeof(BoardOptions));
}

/* LED stuffs */
void Storage::initLEDOptions() {
  EEPROM.get(LED_STORAGE_INDEX, ledOptions);
  uint32_t lastCRC    = ledOptions.checksum;
  ledOptions.checksum = CHECKSUM_MAGIC;
  if (lastCRC != CRC32::calculate(&ledOptions, sizeof(ledOptions))) {
    setDefaultLEDOptions();
  }
}

LEDOptions Storage::getLEDOptions() {
  return ledOptions;
}

void Storage::setDefaultLEDOptions() {
  ledOptions.dataPin           = BOARD_LEDS_PIN;
  ledOptions.ledFormat         = LED_FORMAT;
  ledOptions.ledLayout         = BUTTON_LAYOUT;
  ledOptions.ledsPerButton     = LEDS_PER_PIXEL;
  ledOptions.brightnessMaximum = LED_BRIGHTNESS_MAXIMUM;
  ledOptions.brightnessSteps   = LED_BRIGHTNESS_STEPS;
  ledOptions.indexUp           = LEDS_DPAD_UP;
  ledOptions.indexDown         = LEDS_DPAD_DOWN;
  ledOptions.indexLeft         = LEDS_DPAD_LEFT;
  ledOptions.indexRight        = LEDS_DPAD_RIGHT;
  ledOptions.indexB1           = LEDS_BUTTON_B1;
  ledOptions.indexB2           = LEDS_BUTTON_B2;
  ledOptions.indexB3           = LEDS_BUTTON_B3;
  ledOptions.indexB4           = LEDS_BUTTON_B4;
  ledOptions.indexL1           = LEDS_BUTTON_L1;
  ledOptions.indexR1           = LEDS_BUTTON_R1;
  ledOptions.indexL2           = LEDS_BUTTON_L2;
  ledOptions.indexR2           = LEDS_BUTTON_R2;
  ledOptions.indexS1           = LEDS_BUTTON_S1;
  ledOptions.indexS2           = LEDS_BUTTON_S2;
  ledOptions.indexL3           = LEDS_BUTTON_L3;
  ledOptions.indexR3           = LEDS_BUTTON_R3;
  ledOptions.indexA1           = LEDS_BUTTON_A1;
  ledOptions.indexA2           = LEDS_BUTTON_A2;
  ledOptions.checksum          = CHECKSUM_MAGIC;  // set checksum to magic number
  ledOptions.checksum          = CRC32::calculate(&ledOptions);
  EEPROM.set(LED_STORAGE_INDEX, ledOptions);
}

void Storage::setLEDOptions(LEDOptions options) {
  options.checksum = CHECKSUM_MAGIC;  // set checksum to magic number
  options.checksum = CRC32::calculate(&options);
  EEPROM.set(LED_STORAGE_INDEX, options);
  memcpy(&ledOptions, &options, sizeof(LEDOptions));
}

void Storage::ResetSettings() {
  EEPROM.reset();
  watchdog_reboot(0, SRAM_END, 2000);
}

void Storage::SetConfigMode(bool mode) {  // hack for config mode
  CONFIG_MODE = mode;
}

bool Storage::GetConfigMode() {
  return CONFIG_MODE;
}

void Storage::SetGamepad(Gamepad* newpad) {
  gamepad = newpad;
}

Gamepad* Storage::GetGamepad() {
  return gamepad;
}

void Storage::SetFeatureData(uint8_t* newData) {
  memcpy(newData, featureData, sizeof(uint8_t) * sizeof(featureData));
}

void Storage::ClearFeatureData() {
  memset(featureData, 0, sizeof(uint8_t) * sizeof(featureData));
}

uint8_t* Storage::GetFeatureData() {
  return featureData;
}

/* Animation stuffs */
AnimationOptions AnimationStorage::getAnimationOptions() {
  AnimationOptions options;
  EEPROM.get(ANIMATION_STORAGE_INDEX, options);

  uint32_t lastCRC = options.checksum;
  options.checksum = CHECKSUM_MAGIC;
  if (CRC32::calculate(&options) != lastCRC) {
    options.baseAnimationIndex = LEDS_BASE_ANIMATION_INDEX;
    options.brightness         = LEDS_BRIGHTNESS;
    options.staticColorIndex   = LEDS_STATIC_COLOR_INDEX;
    options.buttonColorIndex   = LEDS_BUTTON_COLOR_INDEX;
    options.chaseCycleTime     = LEDS_CHASE_CYCLE_TIME;
    options.rainbowCycleTime   = LEDS_RAINBOW_CYCLE_TIME;
    options.themeIndex         = LEDS_THEME_INDEX;

    setAnimationOptions(options);
  }

  return options;
}

void AnimationStorage::setAnimationOptions(AnimationOptions options) {
  options.checksum = CHECKSUM_MAGIC;
  options.checksum = CRC32::calculate(&options);
  EEPROM.set(ANIMATION_STORAGE_INDEX, options);
}

void AnimationStorage::save() {
  bool             dirty        = false;
  AnimationOptions savedOptions = getAnimationOptions();

  if (memcmp(&savedOptions, &AnimationStation::options, sizeof(AnimationOptions))) {
    this->setAnimationOptions(AnimationStation::options);
    dirty = true;
  }

  if (dirty)
    EEPROM.commit();
}
