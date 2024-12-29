#include "stemsmidi_device_instances.h"

namespace kinoshita_lab::stemsmidi
{
LedDisplay<pin_config::kNeopixel> led_display;
Knobs knobs(
    pin_config::kS0,
    pin_config::kS1,
    pin_config::kS2,
    pin_config::kA1,
    pin_config::kA2,
    pin_config::kA3,
    nullptr);
Switchs<24, 4> switches(
    pin_config::kNPL,
    pin_config::kCP,
    pin_config::kSerialOut,
    nullptr);
} // namespace kinoshita_lab::stemsmidi