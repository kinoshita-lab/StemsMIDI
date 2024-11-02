#include <Arduino.h>
#include "stemsmidi_knob_table.h"
#include "config.h"

namespace kinoshita_lab
{
namespace stemsmidi
{

namespace knob_table
{
uint8_t apply(const uint16_t input)
{
    if (input < knob_table::kMaxTreatedZero) {
        return 0;
    }
    if (input > knob_table::kMinTreatedMax) {
        return 127;
    }

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
} // namespace knob_table
} // namespace stemsmidi
} // namespace kinoshita_lab