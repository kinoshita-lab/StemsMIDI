#pragma once
#ifndef STEMSMIDI_KNOB_TABLE_H
#define STEMSMIDI_KNOB_TABLE_H

#include <cstdint>

namespace kinoshita_lab
{
namespace stemsmidi
{
namespace knob_table
{
/**
* @param  input: 0 - 511
* @retval 0 - 127(for MIDI)
*/
uint8_t apply(const uint16_t input);
} // namespace knob_table
} // namespace stemsmidi
} // namespace kinoshita_lab

#endif // STEMSMIDI_KNOB_TABLE_H
