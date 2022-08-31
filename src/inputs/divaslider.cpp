#include "inputs/divaslider.h"

#include "storagemanager.h"

#include "GamepadEnums.h"

bool DivaSliderInput::available() {}

void DivaSliderInput::setup() {
  goio_init(PIN_LEFT_SLIDER_COM0);
  gpio_set_dir(PIN_LEFT_SLIDER_COM0, GPIO_IN);
}

uint16_t DivaSliderInput::read() {

}

void DivaSliderInput::process() {
}
