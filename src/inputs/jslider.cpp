#include "inputs/jslider.h"

#include "storagemanager.h"

#include "GamepadEnums.h"

#define JSLIDER_DEBOUNCE_MILLIS 5

#define DPAD_MODE_MASK (DPAD_MODE_LEFT_ANALOG & DPAD_MODE_RIGHT_ANALOG & DPAD_MODE_DIGITAL)

bool JSliderInput::available() {
    BoardOptions boardOptions = Storage::getInstance().getBoardOptions();
	return ( boardOptions.pinSliderLS != (uint8_t)-1 && boardOptions.pinSliderRS != (uint8_t)-1);
}

void JSliderInput::setup()
{
    BoardOptions boardOptions = Storage::getInstance().getBoardOptions();
}

DpadMode JSliderInput::read() {
    BoardOptions boardOptions = Storage::getInstance().getBoardOptions();
    return  DPAD_MODE_DIGITAL;
}

void JSliderInput::debounce()
{
    uint32_t uNowTime = getMillis();
    if ((dDebState != dpadState) && ((uNowTime - uDebTime) > JSLIDER_DEBOUNCE_MILLIS)) {
        if ( (dpadState ^ dDebState) == DPAD_MODE_RIGHT_ANALOG )
            dDebState = (DpadMode)(dDebState ^ DPAD_MODE_RIGHT_ANALOG); // Bounce Right Analog
        else if ( (dpadState ^ dDebState) & DPAD_MODE_LEFT_ANALOG )
            dDebState = (DpadMode)(dDebState ^ DPAD_MODE_LEFT_ANALOG); // Bounce Left Analog
        uDebTime = uNowTime;
    }
    dpadState = dDebState;
}

void JSliderInput::process()
{
    // Get Slider State
    dpadState = read();
#if JSLIDER_DEBOUNCE_MILLIS > 0
    debounce();
#endif

    Gamepad * gamepad = Storage::getInstance().GetGamepad();
    if ( gamepad->options.dpadMode != dpadState) {
        gamepad->options.dpadMode = dpadState;
        gamepad->save();
    }
}
