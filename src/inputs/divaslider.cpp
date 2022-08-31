#include "inputs/divaslider.h"

#include "storagemanager.h"

#include "GamepadEnums.h"

bool DivaSliderInput::available() {}

void initPin(uint8_t pin, uint8_t mode) {
  goio_init(pin);
  gpio_set_dir(pin, mode);
}

void changeLeftChannel(uint8_t channel) {
  gpio_put(PIN_LEFT_SLIDER_S0, channel & (1 << 0));
  gpio_put(PIN_LEFT_SLIDER_S1, channel & (1 << 1));
  gpio_put(PIN_LEFT_SLIDER_S2, channel & (1 << 2));
  gpio_put(PIN_LEFT_SLIDER_S3, channel & (1 << 3));
}

void changeRightChannel(uint8_t channel) {
  gpio_put(PIN_RIGHT_SLIDER_S0, channel & (1 << 0));
  gpio_put(PIN_RIGHT_SLIDER_S1, channel & (1 << 1));
  gpio_put(PIN_RIGHT_SLIDER_S2, channel & (1 << 2));
  gpio_put(PIN_RIGHT_SLIDER_S3, channel & (1 << 3));
}

void DivaSliderInput::setup() {
  initPin(PIN_LEFT_SLIDER_S0, GPIO_OUT);
  initPin(PIN_LEFT_SLIDER_S1, GPIO_OUT);
  initPin(PIN_LEFT_SLIDER_S2, GPIO_OUT);
  initPin(PIN_LEFT_SLIDER_S3, GPIO_OUT);
  initPin(PIN_LEFT_SLIDER_COM0, GPIO_IN);
  initPin(PIN_LEFT_SLIDER_COM1, GPIO_IN);
  
  initPin(PIN_RIGHT_SLIDER_S0, GPIO_OUT);
  initPin(PIN_RIGHT_SLIDER_S1, GPIO_OUT);
  initPin(PIN_RIGHT_SLIDER_S2, GPIO_OUT);
  initPin(PIN_RIGHT_SLIDER_S3, GPIO_OUT);
  initPin(PIN_RIGHT_SLIDER_COM0, GPIO_IN);
  initPin(PIN_RIGHT_SLIDER_COM1, GPIO_IN);
}

uint16_t DivaSliderInput::read_left() {

}

uint16_t DivaSliderInput::read_right() {

}

void DivaSliderInput::process() {
}