#pragma once
#ifndef STEMSMIDI_DEVICE_INSTANCES_H
#define STEMSMIDI_DEVICE_INSTANCES_H

#include "stemsmidi_knob.hpp"
#include "stemsmidi_led_display.hpp"
#include "stemsmidi_switch.hpp"
#include "stemsmidi_pin_config.h"
namespace kinoshita_lab::stemsmidi
{
extern LedDisplay<pin_config::kNeopixel> led_display;
extern Knobs knobs;
extern Switchs<24, 4> switches;
}

#endif // STEMSMIDI_DEVICE_INSTANCES_H
