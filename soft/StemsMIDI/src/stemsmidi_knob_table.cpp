#include <Arduino.h>
#include "stemsmidi_knob_table.h"
#include "stemsmidi_knob_ids.h"
#include "config.h"

namespace kinoshita_lab
{
namespace stemsmidi
{
namespace
{
bool has_center_plateau(const uint8_t knob_index)
{
    switch (knob_index) {
    case kKnob_DeckA_Drums_Filter:
    case kKnob_DeckA_Bass_Filter:
    case kKnob_DeckA_Other_Filter:
    case kKnob_DeckA_Vocals_Filter:
    case kKnob_DeckB_Drums_Filter:
    case kKnob_DeckB_Bass_Filter:
    case kKnob_DeckB_Other_Filter:
    case kKnob_DeckB_Vocals_Filter:
        return true;
    }
    return false;
};
}
namespace knob_table
{
uint8_t apply(const uint8_t knob_index, const uint16_t input)
{
    if (input < knob_table::kMaxTreatedZero) {
        return 0;
    }
    if (input > knob_table::kMinTreatedMax) {
        return 127;
    }

    if (has_center_plateau(knob_index)) {

        constexpr int plateau_start = 255 - knob_table::kCenterPlateauWidth / 2;
        constexpr int plateau_end   = 255 + knob_table::kCenterPlateauWidth / 2;

        if (input >= plateau_start && input <= plateau_end) {
            return 63;
        }

        // table(lower half)
        if (input < plateau_start) {
            constexpr float slope = 63.f / (plateau_start - knob_table::kMaxTreatedZero);
            return (uint8_t)(slope * (input - knob_table::kMaxTreatedZero));
        }

        // otherwise: table(upper half)
        constexpr float slope = 63.f / (knob_table::kMinTreatedMax - plateau_end);
        return 63 + slope * (input - plateau_end);
    }
    return input >> 2;
}
} // namespace knob_table
} // namespace stemsmidi
} // namespace kinoshita_lab