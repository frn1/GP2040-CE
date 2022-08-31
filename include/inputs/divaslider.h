#ifndef _DivaSlider_H
#define _DivaSlider_H

#include "gpaddon.h"

#include "GamepadEnums.h"

#include <CapacitiveSensor.h>

#ifndef PIN_LEFT_SLIDER_S0
#define PIN_LEFT_SLIDER_S0 0
#endif
#ifndef PIN_LEFT_SLIDER_S1
#define PIN_LEFT_SLIDER_S1 0
#endif
#ifndef PIN_LEFT_SLIDER_S2
#define PIN_LEFT_SLIDER_S2 0
#endif
#ifndef PIN_LEFT_SLIDER_S3
#define PIN_LEFT_SLIDER_S3 0
#endif
#ifndef PIN_LEFT_SLIDER_COM0
#define PIN_LEFT_SLIDER_COM0 0
#endif
#ifndef PIN_LEFT_SLIDER_COM1
#define PIN_LEFT_SLIDER_COM1 0
#endif

#ifndef PIN_RIGHT_SLIDER_S0
#define PIN_RIGHT_SLIDER_S0 0
#endif
#ifndef PIN_RIGHT_SLIDER_S1
#define PIN_RIGHT_SLIDER_S1 0
#endif
#ifndef PIN_RIGHT_SLIDER_S2
#define PIN_RIGHT_SLIDER_S2 0
#endif
#ifndef PIN_RIGHT_SLIDER_S3
#define PIN_RIGHT_SLIDER_S3 0
#endif
#ifndef PIN_RIGHT_SLIDER_COM0
#define PIN_RIGHT_SLIDER_COM0 0
#endif
#ifndef PIN_RIGHT_SLIDER_COM1
#define PIN_RIGHT_SLIDER_COM1 0
#endif

#define DivaSliderName "DivaSlider"

class DivaSliderInput : public GPAddon {
 public:
  virtual bool        available();
  virtual void        setup();
  virtual void        process();
  virtual std::string name() { return DivaSliderName; }

 private:
  uint16_t read_left();
  uint16_t read_right();
  CapacitiveSensor capSensorLeft = CapacitiveSensor(PIN_LEFT_SLIDER_COM0, PIN_LEFT_SLIDER_COM1);
  CapacitiveSensor capSensorRight = CapacitiveSensor(PIN_RIGHT_SLIDER_COM0, PIN_RIGHT_SLIDER_COM1);
};

#endif