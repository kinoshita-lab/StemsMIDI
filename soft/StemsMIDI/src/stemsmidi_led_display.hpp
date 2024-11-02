#pragma once
#ifndef STEMSMIDI_LED_HPP
#define STEMSMIDI_LED_HPP

#include <Arduino.h>
#include <FastLED.h>

#include "stemsmidi_led_ids.hpp"

namespace kinoshita_lab
{
namespace stemsmidi
{

template <uint8_t data_pin>
class LedDisplay
{
    enum DefaultColors
    {
        kDefaultColorVolume = 0xe1e1e1,
        kDefaultColorFilter = 0x0362f2,
        kDefaultColorFxSend = 0xf94201,
    };

public:
    LedDisplay()
    {
        FastLED.addLeds<WS2812, data_pin, GRB>(_leds, kNumLedIds);
    }

    void init()
    {
        // set defaut colors
        _ledStatus[kLed_DeckA_Drums_Volume].color = kDefaultColorVolume;
        _ledStatus[kLed_DeckA_Drums_Filter].color = kDefaultColorFilter;
        _ledStatus[kLed_DeckA_Drums_FxSend].color = kDefaultColorFxSend;

        _ledStatus[kLed_DeckA_Bass_FxSend].color = kDefaultColorFxSend;
        _ledStatus[kLed_DeckA_Bass_Filter].color = kDefaultColorFilter;
        _ledStatus[kLed_DeckA_Bass_Volume].color = kDefaultColorVolume;

        _ledStatus[kLed_DeckA_Other_Volume].color = kDefaultColorVolume;
        _ledStatus[kLed_DeckA_Other_Filter].color = kDefaultColorFilter;
        _ledStatus[kLed_DeckA_Other_FxSend].color = kDefaultColorFxSend;

        _ledStatus[kLed_DeckA_Vocals_FxSend].color = kDefaultColorFxSend;
        _ledStatus[kLed_DeckA_Vocals_Filter].color = kDefaultColorFilter;
        _ledStatus[kLed_DeckA_Vocals_Volume].color = kDefaultColorVolume;

        _ledStatus[kLed_DeckB_Drums_Volume].color = kDefaultColorVolume;
        _ledStatus[kLed_DeckB_Drums_Filter].color = kDefaultColorFilter;
        _ledStatus[kLed_DeckB_Drums_FxSend].color = kDefaultColorFxSend;

        _ledStatus[kLed_DeckB_Bass_FxSend].color = kDefaultColorFxSend;
        _ledStatus[kLed_DeckB_Bass_Filter].color = kDefaultColorFilter;
        _ledStatus[kLed_DeckB_Bass_Volume].color = kDefaultColorVolume;

        _ledStatus[kLed_DeckB_Other_Volume].color = kDefaultColorVolume;
        _ledStatus[kLed_DeckB_Other_Filter].color = kDefaultColorFilter;
        _ledStatus[kLed_DeckB_Other_FxSend].color = kDefaultColorFxSend;

        _ledStatus[kLed_DeckB_Vocals_FxSend].color = kDefaultColorFxSend;
        _ledStatus[kLed_DeckB_Vocals_Filter].color = kDefaultColorFilter;
        _ledStatus[kLed_DeckB_Vocals_Volume].color = kDefaultColorVolume;

        for (int i = 0; i < kNumLedIds; i++) {
            _leds[i] = CRGB(_ledStatus[i].color);
            _leds[i].maximizeBrightness(64);
        }
        FastLED.show();
    }

private:
    int _pin;
    CRGB _leds[kNumLedIds];

    struct LedStatus
    {
        CRGB color;
        uint8_t brightness;
    };
    LedStatus _ledStatus[kNumLedIds];
};
} // namespace stemsmidi
} // namespace kinoshita_lab

#endif // STEMSMIDI_LED_HPP
