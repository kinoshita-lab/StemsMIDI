#pragma once
#ifndef STEMSMIDI_KNOBS_HPP
#define STEMSMIDI_KNOBS_HPP

#include <Arduino.h>
#include "stemsmidi_one_pole_filter.hpp"

namespace kinoshita_lab
{
namespace stemsmidi
{

class Knobs
{
    struct Pins
    {
        uint8_t s0;
        uint8_t s1;
        uint8_t s2;

        uint8_t a0;
        uint8_t a1;
        uint8_t a2;

        Pins(const uint8_t s0, const uint8_t s1, const uint8_t s2, const uint8_t a0, const uint8_t a1, const uint8_t a2) : s0{s0}, s1{s1}, s2{s2}, a0{a0}, a1{a1}, a2{a2} {}
    };

    Pins pins_;

    enum
    {
        kNumKnobs          = 24,
        kNumKnobForEachMux = 8,
    };

    uint8_t knob_scan_index_ = 0;
    uint16_t knob_values_[kNumKnobs];
    OnePoleFilter filters_[kNumKnobs];

    void updateKnobIndex()
    {
        knob_scan_index_++;
        if (knob_scan_index_ >= kNumKnobForEachMux) {
            knob_scan_index_ = 0;
        }

        digitalWrite(pins_.s0, knob_scan_index_ & 0x01);
        digitalWrite(pins_.s1, knob_scan_index_ & 0x02);
        digitalWrite(pins_.s2, knob_scan_index_ & 0x04);
    }

public:
    typedef void (*KnobCallback)(uint8_t knob_index, uint16_t value);
    KnobCallback knob_callback_ = nullptr;

    Knobs(
        const uint8_t s0,
        const uint8_t s1,
        const uint8_t s2,
        const uint8_t a0,
        const uint8_t a1,
        const uint8_t a2,
        KnobCallback callback) : pins_{s0, s1, s2, a0, a1, a2}, knob_callback_(callback)
    {
        init();
    }

    ~Knobs() = default;

    void init()
    {
        pinMode(pins_.s0, OUTPUT);
        pinMode(pins_.s1, OUTPUT);
        pinMode(pins_.s2, OUTPUT);

        digitalWrite(pins_.s0, LOW);
        digitalWrite(pins_.s1, LOW);
        digitalWrite(pins_.s2, LOW);
    }

    void readKnobs()
    {
        constexpr int shift = 1;
        const uint16_t a0   = (int)(analogRead(pins_.a0)) >> shift;
        const uint16_t a1   = (int)(analogRead(pins_.a1)) >> shift;
        const uint16_t a2   = (int)(analogRead(pins_.a2)) >> shift;

        auto onChangeEmit = [&](uint8_t knob_index, uint16_t value) {
            filters_[knob_index].update(value);
            const auto output = (uint16_t)(filters_[knob_index].output_);
            const auto delta  = abs(knob_values_[knob_index] - output);

            if (delta > 1 || output == 0 || output == (1023 >> shift)) {
                if (knob_values_[knob_index] != output) {
                    knob_values_[knob_index] = output;
                    if (knob_callback_ != nullptr) {
                        (*knob_callback_)(knob_index, value);
                    }
                }
            }
        };

        onChangeEmit(knob_scan_index_, a0);
        onChangeEmit(knob_scan_index_ + kNumKnobForEachMux, a1);
        onChangeEmit(knob_scan_index_ + kNumKnobForEachMux * 2, a2);

        // prepare for next knob
        updateKnobIndex();
    }

    void setHandler(KnobCallback callback)
    {
        knob_callback_ = callback;
    }
};
} // namespace stemsmidi
} // namespace kinoshita_lab

#endif // STEMSMIDI_KNOBS_HPP
