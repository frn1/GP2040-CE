/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: Copyright (c) 2021 Jason Skuby (mytechtoybox.com)
 */

#ifndef STORAGE_H_
#define STORAGE_H_

#include <stdint.h>
#include "NeoPico.hpp"

#include "enums.h"
#include "gamepad.h"
#include "gpaddon.h"
#include "helper.h"

#define GAMEPAD_STORAGE_INDEX   0     // 1024 bytes for gamepad options
#define BOARD_STORAGE_INDEX     1024  //  512 bytes for hardware options
#define LED_STORAGE_INDEX       1536  //  512 bytes for LED configuration
#define TURBO_STORAGE_INDEX     2048  //   64 bytes for TURBO options
#define ANIMATION_STORAGE_INDEX 2112  // ???? bytes for LED animations

#define CHECKSUM_MAGIC 0  // Checksum CRC

struct BoardOptions {
  bool         hasBoardOptions;
  uint8_t      pinDpadUp;
  uint8_t      pinDpadDown;
  uint8_t      pinDpadLeft;
  uint8_t      pinDpadRight;
  uint8_t      pinButtonB1;
  uint8_t      pinButtonB2;
  uint8_t      pinButtonB3;
  uint8_t      pinButtonB4;
  uint8_t      pinButtonL1;
  uint8_t      pinButtonR1;
  uint8_t      pinButtonL2;
  uint8_t      pinButtonR2;
  uint8_t      pinButtonS1;
  uint8_t      pinButtonS2;
  uint8_t      pinButtonL3;
  uint8_t      pinButtonR3;
  uint8_t      pinButtonA1;
  uint8_t      pinButtonA2;
  uint8_t      pinButtonTurbo;
  uint8_t      pinSliderLS;
  uint8_t      pinSliderRS;
  uint8_t      pinLeftSliderS0;
  uint8_t      pinLeftSliderS1;
  uint8_t      pinLeftSliderS2;
  uint8_t      pinLeftSliderS3;
  uint8_t      pinLeftSliderCOM0;
  uint8_t      pinLeftSliderCOM1;
  uint8_t      pinRightSliderS0;
  uint8_t      pinRightSliderS1;
  uint8_t      pinRightSliderS2;
  uint8_t      pinRightSliderS3;
  uint8_t      pinRightSliderCOM0;
  uint8_t      pinRightSliderCOM1;
  ButtonLayout buttonLayout;
  int          i2cSDAPin;
  int          i2cSCLPin;
  int          i2cBlock;
  uint32_t     i2cSpeed;
  bool         hasI2CDisplay;
  int          displayI2CAddress;
  uint8_t      displaySize;
  bool         displayFlip;
  bool         displayInvert;
  uint8_t      turboShotCount;  // Turbo
  // char boardVersion[32]; // 32-char limit to board name
  uint32_t checksum;
};

struct LEDOptions {
  bool         useUserDefinedLEDs;
  int          dataPin;
  LEDFormat    ledFormat;
  ButtonLayout ledLayout;
  uint8_t      ledsPerButton;
  uint8_t      brightnessMaximum;
  uint8_t      brightnessSteps;
  int          indexUp;
  int          indexDown;
  int          indexLeft;
  int          indexRight;
  int          indexB1;
  int          indexB2;
  int          indexB3;
  int          indexB4;
  int          indexL1;
  int          indexR1;
  int          indexL2;
  int          indexR2;
  int          indexS1;
  int          indexS2;
  int          indexL3;
  int          indexR3;
  int          indexA1;
  int          indexA2;
  uint32_t     checksum;
};

#define SI Storage::getInstance()

// Storage manager for board, LED options, and thread-safe settings
class Storage {
 public:
  Storage(Storage const&)                   = delete;
  void            operator=(Storage const&) = delete;
  static Storage& getInstance()  // Thread-safe storage ensures cross-thread talk
  {
    static Storage instance;
    return instance;
  }

  void         setBoardOptions(BoardOptions);  // Board Options
  void         setDefaultBoardOptions();
  BoardOptions getBoardOptions();

  void       setLEDOptions(LEDOptions);  // LED Options
  void       setDefaultLEDOptions();
  LEDOptions getLEDOptions();

  void SetConfigMode(bool);  // Config Mode (on-boot)
  bool GetConfigMode();

  void     SetGamepad(Gamepad*);  // MPGS Gamepad Get/Set
  Gamepad* GetGamepad();

  void     SetFeatureData(uint8_t*);  // USB Feature Data Get/Set
  void     ClearFeatureData();
  uint8_t* GetFeatureData();

  void ResetSettings();  // EEPROM Reset Feature

  std::vector<GPAddon*> Addons;  // Modular Features
  std::vector<GPAddon*> Inputs;

 private:
  Storage() : gamepad(0) {
    initBoardOptions();
    initLEDOptions();
  }
  void         initBoardOptions();
  void         initLEDOptions();
  bool         CONFIG_MODE;  // Config mode (boot)
  Gamepad*     gamepad;      // Gamepad data
  BoardOptions boardOptions;
  LEDOptions   ledOptions;
  uint8_t      featureData[32];  // USB X-Input Feature Data
};

#endif
