#pragma once
#ifndef STEMSMIDI_STATUS_H
#define STEMSMIDI_STATUS_H

#include <cstdint>

#include "config.h"
namespace kinoshita_lab
{
namespace stemsmidi
{
struct Status
{
    uint8_t knob_last_values[kNumTotalTweakableItems] = {0};
};
} // namespace stemsmidi
} // namespace kinoshita_lab

#endif // STEMSMIDI_STATUS_H
