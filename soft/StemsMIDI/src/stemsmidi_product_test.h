#pragma once
#ifndef STEMSMIDI_PRODUCT_TEST_H
#define STEMSMIDI_PRODUCT_TEST_H

#include <functional>
#include <Arduino.h>
#include <stdint.h>
namespace kinoshita_lab::stemsmidi::product_test
{
void initialize();
void timer_callback(struct repeating_timer* t);
void knob_callback(uint8_t knob_index, uint16_t value);
void switch_callback(uint32_t switch_index, const int off_on);
void test_loop();
void set_test_finish_callback(std::function<void()> callback);
} // namespace kinoshita_lab::stemsmidi::product_test

#endif // STEMSMIDI_PRODUCT_TEST_H
