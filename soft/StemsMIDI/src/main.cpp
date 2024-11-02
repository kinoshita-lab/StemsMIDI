#include <Adafruit_TinyUSB.h>
#include <Arduino.h>
#include <MIDI.h>
#include <pico/stdlib.h>

#include "stemsmidi_pin_config.h"

#include "stemsmidi_led_display.hpp"
#include "stemsmidi_knob.hpp"
#include "stemsmidi_knob_table.h"

#include "stemsmidi_switch.hpp"

#include "stemsmidi_status.h"

using namespace kinoshita_lab::stemsmidi;

bool timer_callback(struct repeating_timer* t);
void knob_callback(uint8_t knob_index, uint16_t value);
void switch_callback(uint32_t switch_index, const int off_on);

Adafruit_USBD_MIDI usb_midi;
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, MIDI_USB);

LedDisplay<pin_config::kNeopixel> led_display;
Knobs knobs(
    pin_config::kS0,
    pin_config::kS1,
    pin_config::kS2,
    pin_config::kA1,
    pin_config::kA2,
    pin_config::kA3,
    knob_callback);

Switchs<24, 4> switches(
    pin_config::kNPL,
    pin_config::kCP,
    pin_config::kSerialOut,
    switch_callback);

Status status;

bool timer_fired = false;

bool timer_callback(struct repeating_timer* t)
{
    timer_fired = true;
    return true;
}

void knob_callback(uint8_t knob_index, uint16_t value)
{
    const auto table_applied_value = knob_table::apply(value);
    if (status.knob_last_values[knob_index] == table_applied_value) {
        return;
    }
    status.knob_last_values[knob_index] = table_applied_value;

    Serial.printf("Knob %d: %d\n", knob_index, table_applied_value);
    Serial.flush();
}

void switch_callback(uint32_t switch_index, const int off_on)
{
    Serial.printf("Switch %d: %d\n", switch_index, off_on);
    Serial.flush();
}

struct repeating_timer timer;
void setup()
{
    // Manual begin() is required on core without built-in support e.g. mbed rp2040
    if (!TinyUSBDevice.isInitialized()) {
        TinyUSBDevice.begin(0);
    }
    Serial.begin(115200);

    usb_midi.setStringDescriptor("Kinoshita Lab. Stems MIDI");

    MIDI_USB.begin();
    if (TinyUSBDevice.mounted()) {
        TinyUSBDevice.detach();
        delay(10);
        TinyUSBDevice.attach();
    }

    led_display.init();

    add_repeating_timer_us(500, timer_callback, NULL, &timer);
}
int count = 0;
void loop()
{
#ifdef TINYUSB_NEED_POLLING_TASK
    // Manual call tud_task since it isn't called by Core's background
    TinyUSBDevice.task();
#endif

    if (timer_fired) {
        timer_fired = false;

        knobs.readKnobs();
        switches.update();
    }
}
