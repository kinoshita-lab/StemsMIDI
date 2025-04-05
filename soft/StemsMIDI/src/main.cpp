#include <Adafruit_TinyUSB.h>
#include <Arduino.h>
#include <MIDI.h>
#include <pico/stdlib.h>
#include <functional>

#include "stemsmidi_pin_config.h"
#include "stemsmidi_led_display.hpp"
#include "stemsmidi_knob.hpp"
#include "stemsmidi_knob_table.h"
#include "stemsmidi_switch_ids.h"
#include "stemsmidi_switch.hpp"
#include "stemsmidi_status.h"
#include "stemsmidi_cc_numbers.h"
#include "stemsmidi_product_test.h"
#include "stemsmidi_device_instances.h"

using namespace kinoshita_lab::stemsmidi;

bool timer_callback(struct repeating_timer* t);
void knob_callback(uint8_t knob_index, uint16_t value);
void switch_callback(uint32_t switch_index, const int off_on);
void main_loop();

Adafruit_USBD_MIDI usb_midi;
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, MIDI_USB);

int8_t knobToCCTable[kNumKnobs] = {
    cc_numbers::kDeckA_Slot1_Volume_Adjust,
    cc_numbers::kDeckA_Slot1_Filter_Adjust,
    cc_numbers::kDeckA_Slot1_FxSend_Adjust,
    cc_numbers::kDeckA_Slot2_Volume_Adjust,
    cc_numbers::kDeckA_Slot2_Filter_Adjust,
    cc_numbers::kDeckA_Slot2_FxSend_Adjust,
    cc_numbers::kDeckA_Slot3_Volume_Adjust,
    cc_numbers::kDeckA_Slot3_Filter_Adjust,
    cc_numbers::kDeckA_Slot3_FxSend_Adjust,
    cc_numbers::kDeckA_Slot4_Volume_Adjust,
    cc_numbers::kDeckA_Slot4_Filter_Adjust,
    cc_numbers::kDeckA_Slot4_FxSend_Adjust,
    cc_numbers::kDeckB_Slot1_Volume_Adjust,
    cc_numbers::kDeckB_Slot1_Filter_Adjust,
    cc_numbers::kDeckB_Slot1_FxSend_Adjust,
    cc_numbers::kDeckB_Slot2_Volume_Adjust,
    cc_numbers::kDeckB_Slot2_Filter_Adjust,
    cc_numbers::kDeckB_Slot2_FxSend_Adjust,
    cc_numbers::kDeckB_Slot3_Volume_Adjust,
    cc_numbers::kDeckB_Slot3_Filter_Adjust,
    cc_numbers::kDeckB_Slot3_FxSend_Adjust,
    cc_numbers::kDeckB_Slot4_Volume_Adjust,
    cc_numbers::kDeckB_Slot4_Filter_Adjust,
    cc_numbers::kDeckB_Slot4_FxSend_Adjust,
};

int8_t switchToCCTable[kNumSwitches] = {
    cc_numbers::kDeckA_Slot1_Mute_OnOff,
    cc_numbers::kDeckA_Slot1_Filter_OnOff,
    cc_numbers::kDeckA_Slot1_FxSend_OnOff,
    cc_numbers::kDeckA_Slot2_Mute_OnOff,
    cc_numbers::kDeckA_Slot2_Filter_OnOff,
    cc_numbers::kDeckA_Slot2_FxSend_OnOff,
    cc_numbers::kDeckA_Slot3_Mute_OnOff,
    cc_numbers::kDeckA_Slot3_Filter_OnOff,
    cc_numbers::kDeckA_Slot3_FxSend_OnOff,
    cc_numbers::kDeckA_Slot4_Mute_OnOff,
    cc_numbers::kDeckA_Slot4_Filter_OnOff,
    cc_numbers::kDeckA_Slot4_FxSend_OnOff,
    cc_numbers::kDeckB_Slot1_Mute_OnOff,
    cc_numbers::kDeckB_Slot1_Filter_OnOff,
    cc_numbers::kDeckB_Slot1_FxSend_OnOff,
    cc_numbers::kDeckB_Slot2_Mute_OnOff,
    cc_numbers::kDeckB_Slot2_Filter_OnOff,
    cc_numbers::kDeckB_Slot2_FxSend_OnOff,
    cc_numbers::kDeckB_Slot3_Mute_OnOff,
    cc_numbers::kDeckB_Slot3_Filter_OnOff,
    cc_numbers::kDeckB_Slot3_FxSend_OnOff,
    cc_numbers::kDeckB_Slot4_Mute_OnOff,
    cc_numbers::kDeckB_Slot4_Filter_OnOff,
    cc_numbers::kDeckB_Slot4_FxSend_OnOff,
};

bool timer_fired = false;
struct repeating_timer timer;

std::function<void()> main_loop_function                             = nullptr;
std::function<bool(struct repeating_timer*)> timer_callback_function = nullptr;

bool timer_callback(struct repeating_timer* t)
{
    timer_fired = true;
    return true;
}

void knob_callback(uint8_t knob_index, uint16_t value)
{
    const auto table_applied_value = knob_table::apply(knob_index, value);
    if (status.knob_scanned_value[knob_index] == table_applied_value) {
        return;
    }

    status.knob_scanned_value[knob_index] = table_applied_value;

    const auto index                        = status.getKnobMidiMessageSlotIndex(knob_index);
    status.midi_messages[index].should_send = true;
    status.midi_messages[index].value       = table_applied_value;
}

void switch_callback(uint32_t switch_index, const int off_on)
{
    const auto index                        = status.getSwitchMidiMessageSlotIndex(switch_index);
    status.midi_messages[index].should_send = true;
    status.midi_messages[index].value       = off_on ? 0 : 127;
}

void handle_control_change(const byte channel, const byte number, const byte value)
{
    if (channel != kMidiChannel) {
        return;
    }

    auto ccToLedId = [](const int cc) -> int {
        using namespace cc_numbers;
        switch (cc) {
        case kDeckA_Slot1_Mute_OnOff:
            return kLed_DeckA_Drums_Volume;
        case kDeckA_Slot1_Filter_OnOff:
            return kLed_DeckA_Drums_Filter;
        case kDeckA_Slot1_FxSend_OnOff:
            return kLed_DeckA_Drums_FxSend;
        case kDeckA_Slot2_Mute_OnOff:
            return kLed_DeckA_Bass_Volume;
        case kDeckA_Slot2_Filter_OnOff:
            return kLed_DeckA_Bass_Filter;
        case kDeckA_Slot2_FxSend_OnOff:
            return kLed_DeckA_Bass_FxSend;
        case kDeckA_Slot3_Mute_OnOff:
            return kLed_DeckA_Other_Volume;
        case kDeckA_Slot3_Filter_OnOff:
            return kLed_DeckA_Other_Filter;
        case kDeckA_Slot3_FxSend_OnOff:
            return kLed_DeckA_Other_FxSend;
        case kDeckA_Slot4_Mute_OnOff:
            return kLed_DeckA_Vocals_Volume;
        case kDeckA_Slot4_Filter_OnOff:
            return kLed_DeckA_Vocals_Filter;
        case kDeckA_Slot4_FxSend_OnOff:
            return kLed_DeckA_Vocals_FxSend;
        case kDeckB_Slot1_Mute_OnOff:
            return kLed_DeckB_Drums_Volume;
        case kDeckB_Slot1_Filter_OnOff:
            return kLed_DeckB_Drums_Filter;
        case kDeckB_Slot1_FxSend_OnOff:
            return kLed_DeckB_Drums_FxSend;
        case kDeckB_Slot2_Mute_OnOff:
            return kLed_DeckB_Bass_Volume;
        case kDeckB_Slot2_Filter_OnOff:
            return kLed_DeckB_Bass_Filter;
        case kDeckB_Slot2_FxSend_OnOff:
            return kLed_DeckB_Bass_FxSend;
        case kDeckB_Slot3_Mute_OnOff:
            return kLed_DeckB_Other_Volume;
        case kDeckB_Slot3_Filter_OnOff:
            return kLed_DeckB_Other_Filter;
        case kDeckB_Slot3_FxSend_OnOff:
            return kLed_DeckB_Other_FxSend;
        case kDeckB_Slot4_Mute_OnOff:
            return kLed_DeckB_Vocals_Volume;
        case kDeckB_Slot4_Filter_OnOff:
            return kLed_DeckB_Vocals_Filter;
        case kDeckB_Slot4_FxSend_OnOff:
            return kLed_DeckB_Vocals_FxSend;
        default:
            return -1;
        }
    };

    const auto led_id = ccToLedId(number);
    if (led_id != -1) {
        const auto off_on = value == 0 ? 0 : 1;
        led_display.setLed(led_id, off_on);
        status.updateLed = true;
    }
}

void set_test_mode()
{
    main_loop_function = product_test::test_loop;
    switches.setHandler(product_test::switch_callback);
    knobs.setHandler(product_test::knob_callback);
    product_test::initialize();
}

void set_normal_mode()
{
    main_loop_function = main_loop;
    switches.setHandler(switch_callback);
    knobs.setHandler(knob_callback);
}

void setup()
{
    Serial.begin(115200);
    // Manual begin() is required on core without built-in support e.g. mbed rp2040
    TinyUSBDevice.setManufacturerDescriptor("Kinoshita Laboratory");
    TinyUSBDevice.setProductDescriptor("Stems MIDI Controller");
    TinyUSBDevice.setSerialDescriptor("0xdeadbeef");
    if (!TinyUSBDevice.isInitialized()) {
        TinyUSBDevice.begin(0);
    }

    usb_midi.setStringDescriptor("Kinoshita Lab. Stems MIDI");

    MIDI_USB.begin();
    MIDI_USB.setThruFilterMode(midi::Thru::Off);
    if (TinyUSBDevice.mounted()) {
        TinyUSBDevice.detach();
        delay(10);
        TinyUSBDevice.attach();
    }

    led_display.init();

    // initialize cc numbers
    for (auto i = 0; i < kNumKnobs; i++) {
        status.midi_messages[Status::getKnobMidiMessageSlotIndex(i)].cc_number = knobToCCTable[i];
    }

    for (auto i = 0; i < kNumSwitches; i++) {
        status.midi_messages[Status::getSwitchMidiMessageSlotIndex(i)].cc_number = switchToCCTable[i];
    }

    // initial switch scan, to determine whether product testing should perform
    switches.forceScan();
    const auto deckADrumsVolSwitchOn    = switches.switchIsOn(kSwitch_DeckA_Drums_Volume);
    const auto deckADrumsFilterSwitchOn = switches.switchIsOn(kSwitch_DeckA_Drums_Filter);
    // enter test mode if both deck A drums volume and filter switches are on.
    if (deckADrumsVolSwitchOn && deckADrumsFilterSwitchOn) {

        set_test_mode();
    } else {
        set_normal_mode();
    }

    product_test::set_test_finish_callback(set_normal_mode);

    // start timer(500us)
    add_repeating_timer_us(500, timer_callback, NULL, &timer);

    MIDI_USB.setHandleControlChange(handle_control_change);

    // failsafe just in case.. do not want to check existence of main_loop_function in loop() every time
    if (!main_loop_function) {
        main_loop_function = main_loop;
    }
}

void loop()
{
    // common implementation
#ifdef TINYUSB_NEED_POLLING_TASK
    // Manual call tud_task since it isn't called by Core's background
    TinyUSBDevice.task();
#endif

    if (timer_fired) {
        timer_fired = false;
        knobs.readKnobs();
        switches.update();
    }

    main_loop_function();

    // update led display
    if (status.updateLed) {
        status.updateLed = false;
        led_display.update();
    }
}

void main_loop()
{
    // send midi messages
    for (auto i = 0; i < kNumTotalTweakableItems; i++) {
        if (status.midi_messages[i].should_send) {
            status.midi_messages[i].should_send = false;

            MIDI_USB.sendControlChange(status.midi_messages[i].cc_number, status.midi_messages[i].value, kMidiChannel);
        }
    }
    // receive midi messages
    MIDI_USB.read();
}
