#pragma once
#ifndef STEMSMIDI_LED_IDS_HPP
#define STEMSMIDI_LED_IDS_HPP

namespace kinoshita_lab
{
namespace stemsmidi
{
// corresponds  to the circuit diagram for LED connection order
enum LedId
{
    kLed_DeckA_Drums_Volume,
    kLed_DeckA_Drums_Filter,
    kLed_DeckA_Drums_FxSend,

    kLed_DeckA_Bass_FxSend,
    kLed_DeckA_Bass_Filter,
    kLed_DeckA_Bass_Volume,

    kLed_DeckA_Other_Volume,
    kLed_DeckA_Other_Filter,
    kLed_DeckA_Other_FxSend,

    kLed_DeckA_Vocals_FxSend,
    kLed_DeckA_Vocals_Filter,
    kLed_DeckA_Vocals_Volume,

    kLed_DeckB_Drums_Volume,
    kLed_DeckB_Drums_Filter,
    kLed_DeckB_Drums_FxSend,

    kLed_DeckB_Bass_FxSend,
    kLed_DeckB_Bass_Filter,
    kLed_DeckB_Bass_Volume,

    kLed_DeckB_Other_Volume,
    kLed_DeckB_Other_Filter,
    kLed_DeckB_Other_FxSend,

    kLed_DeckB_Vocals_FxSend,
    kLed_DeckB_Vocals_Filter,
    kLed_DeckB_Vocals_Volume,

    kNumLedIds,
};
} // namespace stemsmidi
} // namespace kinoshita_lab

#endif // STEMSMIDI_LED_ID_HPP
