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

    int8_t knob_scanned_value[kNumKnobs];

    bool updateLed = false;

    struct MidiMessage
    {
        bool should_send = false;
        int8_t cc_number = -1;
        int8_t value     = -1;

        MidiMessage() = default;
    };
    MidiMessage midi_messages[kNumTotalTweakableItems]; // knob, switch

    static uint8_t getKnobMidiMessageSlotIndex(const uint8_t knob_index)
    {
        return knob_index;
    }
    static uint8_t getSwitchMidiMessageSlotIndex(const uint8_t switch_index)
    {
        return switch_index + kNumKnobs;
    }
};
extern Status status;
} // namespace stemsmidi
} // namespace kinoshita_lab

#endif // STEMSMIDI_STATUS_H
