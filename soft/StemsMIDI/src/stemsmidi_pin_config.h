#pragma once
#ifndef STEMSMIDI_PIN_CONFIG_H
#define STEMSMIDI_PIN_CONFIG_H

#include <Arduino.h>
namespace kinoshita_lab
{
namespace stemsmidi
{
namespace pin_config
{
enum
{
    // analog pins
    kA1 = A0,
    kA2 = A1,
    kA3 = A2,

    // analog multiplexer
    kS0 = 6,
    kS1 = 7,
    kS2 = 0,

    // shift register
    kNPL       = 3,
    kCP        = 4,
    kSerialOut = 2,

    // neopixel
    kNeopixel = 1,
};
} // namespace pin_config
} // namespace stemsmidi
} // namespace kinoshita_lab
#endif // STEMSMIDI_PIN_CONFIG_H
