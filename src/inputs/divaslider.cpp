#include "inputs/divaslider.h"

#include "storagemanager.h"

#include "GamepadEnums.h"

bool DivaSliderInput::available() {}

void DivaSliderInput::setup() {}

DpadMode DivaSliderInput::read() {

}

void DivaSliderInput::process() {
  Gamepad* gamepad = Storage::getInstance().GetGamepad();
}
