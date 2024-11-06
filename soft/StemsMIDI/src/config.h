#pragma once
#ifndef CONFIG_H
#define CONFIG_H

namespace kinoshita_lab
{
namespace stemsmidi
{
enum
{
    kMidiChannel = 1,
};
enum
{
    kNumKnobs               = 24,
    kNumSwitches            = 24,
    kNumTotalTweakableItems = kNumKnobs + kNumSwitches,
};

namespace knob_table
{
enum
{
    kMaxTreatedZero     = 10,
    kMinTreatedMax      = 501,
    kCenterPlateauWidth = 20,
};
} // namespace knob_table
} // namespace stemsmidi
} // namespace kinoshita_lab

#endif // CONFIG_H
