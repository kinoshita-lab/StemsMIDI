#include "stemsmidi_product_test.h"
#include "stemsmidi_device_instances.h"
#include "stemsmidi_knob_table.h"
#include "stemsmidi_knob_ids.h"
#include "stemsmidi_switch_ids.h"
#include "stemsmidi_status.h"

namespace kinoshita_lab::stemsmidi::product_test
{
bool timer_fired                           = false;
std::function<void()> test_finish_callback = nullptr;

enum TestId
{
    kLed,
    kSwithch,
    kKnob,
    kFinish,
};
enum LedTestId
{
    kLedAllWhite,
    kLedAllBlack,
    kLedAllRed,
    kLedAllGreen,
    kLedAllBlue,
    kNumLedTestIds,
};

uint8_t switch_counter[kNumSwitches] = {0};

int currentTestId    = kLed;
int currentLedTestId = kLedAllWhite;

struct KnobStatus
{
    bool bottomOk = false;
    bool topOk    = false;
    bool centerOk = false;
};
KnobStatus knobStatus[kNumKnobs];
int currentKnobIndex = 0;

bool test_finished = false;

int knob_id_to_led_id(const int knob_id)
{
    switch (knob_id) {
    case kKnob_DeckA_Drums_Volume:
        return kLed_DeckA_Drums_Volume;
    case kKnob_DeckA_Drums_Filter:
        return kLed_DeckA_Drums_Filter;
    case kKnob_DeckA_Drums_FxSend:
        return kLed_DeckA_Drums_FxSend;
    case kKnob_DeckA_Bass_Volume:
        return kLed_DeckA_Bass_Volume;
    case kKnob_DeckA_Bass_Filter:
        return kLed_DeckA_Bass_Filter;
    case kKnob_DeckA_Bass_FxSend:
        return kLed_DeckA_Bass_FxSend;
    case kKnob_DeckA_Other_Volume:
        return kLed_DeckA_Other_Volume;
    case kKnob_DeckA_Other_Filter:
        return kLed_DeckA_Other_Filter;
    case kKnob_DeckA_Other_FxSend:
        return kLed_DeckA_Other_FxSend;
    case kKnob_DeckA_Vocals_Volume:
        return kLed_DeckA_Vocals_Volume;
    case kKnob_DeckA_Vocals_Filter:
        return kLed_DeckA_Vocals_Filter;
    case kKnob_DeckA_Vocals_FxSend:
        return kLed_DeckA_Vocals_FxSend;
    case kKnob_DeckB_Drums_Volume:
        return kLed_DeckB_Drums_Volume;
    case kKnob_DeckB_Drums_Filter:
        return kLed_DeckB_Drums_Filter;
    case kKnob_DeckB_Drums_FxSend:
        return kLed_DeckB_Drums_FxSend;
    case kKnob_DeckB_Bass_Volume:
        return kLed_DeckB_Bass_Volume;
    case kKnob_DeckB_Bass_Filter:
        return kLed_DeckB_Bass_Filter;
    case kKnob_DeckB_Bass_FxSend:
        return kLed_DeckB_Bass_FxSend;
    case kKnob_DeckB_Other_Volume:
        return kLed_DeckB_Other_Volume;
    case kKnob_DeckB_Other_Filter:
        return kLed_DeckB_Other_Filter;
    case kKnob_DeckB_Other_FxSend:
        return kLed_DeckB_Other_FxSend;
    case kKnob_DeckB_Vocals_Volume:
        return kLed_DeckB_Vocals_Volume;
    case kKnob_DeckB_Vocals_Filter:
        return kLed_DeckB_Vocals_Filter;
    case kKnob_DeckB_Vocals_FxSend:
        return kLed_DeckB_Vocals_FxSend;
    default:
        return -1;
    }
}

int switchToLedId(const int switch_index)
{
    switch (switch_index) {
    case kSwitch_DeckA_Drums_Volume:
        return kLed_DeckA_Drums_Volume;
    case kSwitch_DeckA_Drums_Filter:
        return kLed_DeckA_Drums_Filter;
    case kSwitch_DeckA_Drums_FxSend:
        return kLed_DeckA_Drums_FxSend;
    case kSwitch_DeckA_Bass_FxSend:
        return kLed_DeckA_Bass_FxSend;
    case kSwitch_DeckA_Bass_Filter:
        return kLed_DeckA_Bass_Filter;
    case kSwitch_DeckA_Bass_Volume:
        return kLed_DeckA_Bass_Volume;
    case kSwitch_DeckA_Other_Volume:
        return kLed_DeckA_Other_Volume;
    case kSwitch_DeckA_Other_Filter:
        return kLed_DeckA_Other_Filter;
    case kSwitch_DeckA_Other_FxSend:
        return kLed_DeckA_Other_FxSend;
    case kSwitch_DeckA_Vocals_Volume:
        return kLed_DeckA_Vocals_Volume;
    case kSwitch_DeckA_Vocals_Filter:
        return kLed_DeckA_Vocals_Filter;
    case kSwitch_DeckA_Vocals_FxSend:
        return kLed_DeckA_Vocals_FxSend;
    case kSwitch_DeckB_Drums_Volume:
        return kLed_DeckB_Drums_Volume;
    case kSwitch_DeckB_Drums_Filter:
        return kLed_DeckB_Drums_Filter;
    case kSwitch_DeckB_Drums_FxSend:
        return kLed_DeckB_Drums_FxSend;
    case kSwitch_DeckB_Bass_Volume:
        return kLed_DeckB_Bass_Volume;
    case kSwitch_DeckB_Bass_Filter:
        return kLed_DeckB_Bass_Filter;
    case kSwitch_DeckB_Bass_FxSend:
        return kLed_DeckB_Bass_FxSend;
    case kSwitch_DeckB_Other_Volume:
        return kLed_DeckB_Other_Volume;
    case kSwitch_DeckB_Other_Filter:
        return kLed_DeckB_Other_Filter;
    case kSwitch_DeckB_Other_FxSend:
        return kLed_DeckB_Other_FxSend;
    case kSwitch_DeckB_Vocals_Volume:
        return kLed_DeckB_Vocals_Volume;
    case kSwitch_DeckB_Vocals_Filter:
        return kLed_DeckB_Vocals_Filter;
    case kSwitch_DeckB_Vocals_FxSend:
        return kLed_DeckB_Vocals_FxSend;
    default:
        return -1;
    }
}

void knob_test_initilize()
{
    Serial.println("knob_test_initilize");
    Serial.flush();
    for (int i = 0; i < kNumKnobs; i++) {
        knobStatus[i].bottomOk = false;
        knobStatus[i].topOk    = false;
        knobStatus[i].centerOk = false;
    }
    CRGB color = CRGB::Red;
    for (int i = 0; i < kNumLedIds; i++) {
        led_display.setColor(i, color);
        led_display.setLed(i, true);
        status.updateLed = true;
    }
}
void knob_test(const int knob_index, const int value)
{
    auto hasCenterClick = [](const int index) -> bool {
        switch (index) {
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

    // check bottom first
    if (knobStatus[knob_index].bottomOk == false) {
        if (value == 0) {
            knobStatus[knob_index].bottomOk = true;
            CRGB color                      = CRGB::Blue;
            if (hasCenterClick(knob_index)) {
                color = CRGB::Yellow;
            }
            led_display.setColor(knob_id_to_led_id(knob_index), color);
            status.updateLed = true;
        }
        return;
    }

    auto all_test_ok = [](const KnobStatus* status) -> bool {
        for (int i = 0; i < kNumKnobs; i++) {
            if (status[i].topOk == false || status[i].bottomOk == false || status[i].centerOk == false) {
                return false;
            }
        }
        return true;
    };

    // check top
    if (knobStatus[knob_index].topOk == false) {
        if (value == 127) {
            knobStatus[knob_index].topOk = true;
            CRGB color                   = CRGB::Blue;
            if (!hasCenterClick(knob_index)) {
                knobStatus[knob_index].centerOk = true;
                color                           = CRGB::Green;
                if (all_test_ok(knobStatus)) {
                    currentTestId = kFinish;
                }
            }
            led_display.setColor(knob_id_to_led_id(knob_index), color);
            status.updateLed = true;
        }
        return;
    }

    // check center
    if (knobStatus[knob_index].centerOk == false) {
        if (value == 63) {
            knobStatus[knob_index].centerOk = true;
            CRGB color                      = CRGB::Green;
            led_display.setColor(knob_id_to_led_id(knob_index), color);
            status.updateLed = true;
            if (all_test_ok(knobStatus)) {
                currentTestId = kFinish;
            }
        }
        return;
    }
}

void setLedTest(const int ledTestId)
{
    Serial.printf("setLedTest: %d\n", ledTestId);
    Serial.flush();
    currentLedTestId = ledTestId;
    CRGB color       = CRGB::Black;

    switch (currentLedTestId) {
    case kLedAllWhite:
        color = CRGB::White;
        break;
    case kLedAllBlack:
        color = CRGB::Black;
        break;
    case kLedAllRed:
        color = CRGB::Red;
        break;
    case kLedAllGreen:
        color = CRGB::Green;
        break;
    case kLedAllBlue:
        color = CRGB::Blue;
        break;
    default:
        break;
    }
    for (int i = 0; i < kNumLedIds; i++) {
        led_display.setColor(i, color);
        led_display.setLed(i, true);
        status.updateLed = true;
    }
}

void init_switch_test()
{
    CRGB color = CRGB::Red;
    for (int i = 0; i < kNumLedIds; i++) {
        led_display.setColor(i, color);
        led_display.setLed(i, true);
        status.updateLed = true;
    }

    for (int i = 0; i < kNumSwitches; i++) {
        switch_counter[i] = 0;
    }
}

int switchoTLedId(const int switchId)
{
    switch (switchId) {
    case kSwitch_DeckA_Drums_Volume:
        return kLed_DeckA_Drums_Volume;
    case kSwitch_DeckA_Drums_Filter:
        return kLed_DeckA_Drums_Filter;
    case kSwitch_DeckA_Drums_FxSend:
        return kLed_DeckA_Drums_FxSend;
    case kSwitch_DeckA_Bass_FxSend:
        return kLed_DeckA_Bass_FxSend;
    case kSwitch_DeckA_Bass_Filter:
        return kLed_DeckA_Bass_Filter;
    case kSwitch_DeckA_Bass_Volume:
        return kLed_DeckA_Bass_Volume;
    case kSwitch_DeckA_Other_Volume:
        return kLed_DeckA_Other_Volume;
    case kSwitch_DeckA_Other_Filter:
        return kLed_DeckA_Other_Filter;
    case kSwitch_DeckA_Other_FxSend:
        return kLed_DeckA_Other_FxSend;
    case kSwitch_DeckA_Vocals_Volume:
        return kLed_DeckA_Vocals_Volume;
    case kSwitch_DeckA_Vocals_Filter:
        return kLed_DeckA_Vocals_Filter;
    case kSwitch_DeckA_Vocals_FxSend:
        return kLed_DeckA_Vocals_FxSend;
    case kSwitch_DeckB_Drums_Volume:
        return kLed_DeckB_Drums_Volume;
    case kSwitch_DeckB_Drums_Filter:
        return kLed_DeckB_Drums_Filter;
    case kSwitch_DeckB_Drums_FxSend:
        return kLed_DeckB_Drums_FxSend;
    case kSwitch_DeckB_Bass_Volume:
        return kLed_DeckB_Bass_Volume;
    case kSwitch_DeckB_Bass_Filter:
        return kLed_DeckB_Bass_Filter;
    case kSwitch_DeckB_Bass_FxSend:
        return kLed_DeckB_Bass_FxSend;
    case kSwitch_DeckB_Other_Volume:
        return kLed_DeckB_Other_Volume;
    case kSwitch_DeckB_Other_Filter:
        return kLed_DeckB_Other_Filter;
    case kSwitch_DeckB_Other_FxSend:
        return kLed_DeckB_Other_FxSend;
    case kSwitch_DeckB_Vocals_Volume:
        return kLed_DeckB_Vocals_Volume;
    case kSwitch_DeckB_Vocals_Filter:
        return kLed_DeckB_Vocals_Filter;
    case kSwitch_DeckB_Vocals_FxSend:
        return kLed_DeckB_Vocals_FxSend;
    default:
        return -1;
    }
}

void timer_callback(struct repeating_timer* t)
{
    timer_fired = true;
}

void knob_callback(uint8_t knob_index, uint16_t value)
{


    const auto table_applied_value = knob_table::apply(knob_index, value);

    if (status.knob_scanned_value[knob_index] == table_applied_value) {
        return;
    }
    const auto index                      = status.getKnobMidiMessageSlotIndex(knob_index);
    status.knob_scanned_value[knob_index] = table_applied_value;
    if (currentTestId == kKnob) {
        knob_test(knob_index, table_applied_value);
    }
    Serial.printf("knob_index: %d, value: %d\n", knob_index, table_applied_value);
    Serial.flush();
}
void switch_callback(uint32_t switch_index, const int off_on)
{

    Serial.printf("switch_index: %d, off_on: %d\n", switch_index, off_on);
    Serial.flush();

    switch (currentTestId) {
    case kLed: {
        if (off_on == 1) {
            return;
        }
        const auto next_test_id = static_cast<LedTestId>(currentLedTestId + 1);
        if (next_test_id == kNumLedTestIds) {
            currentTestId = kSwithch;
            init_switch_test();

        } else {
            setLedTest(next_test_id);
        }
    } break;
    case kSwithch: {
        if (switch_counter[switch_index] == 0) {
            // on trigger
            if (off_on == 0) {
                return;
            }
            switch_counter[switch_index]++;
            CRGB color           = CRGB::Blue;
            const auto led_index = switchToLedId(switch_index);
            led_display.setColor(led_index, color);
            status.updateLed = true;
        } else if (switch_counter[switch_index] == 1) {
            // off trigger
            if (off_on == 1) {
                return;
            }
            switch_counter[switch_index]++;
            CRGB color           = CRGB::Green;
            const auto led_index = switchToLedId(switch_index);
            led_display.setColor(led_index, color);
            status.updateLed = true;
            // all switches check finished? goto next
            bool all_finished = true;
            for (int i = 0; i < kNumSwitches; i++) {
                if (switch_counter[i] != 2) {
                    all_finished = false;
                    Serial.printf("switch_counter[%d]: %d\n", i, switch_counter[i]);
                    Serial.flush();
                    break;
                }
            }
            // all switches check finished? goto knob test
            if (all_finished) {
                currentTestId = kKnob;
                knob_test_initilize();
            }
        }

        else {
            // unknown state
        }
    } break;
    case kKnob:
        break;
    default:
        break;
    }
}

void initialize()
{
    setLedTest(currentLedTestId);
}
void test_loop()
{
    if (currentTestId == kFinish) {
        Serial.println("test finished");
        Serial.flush();
        led_display.init();
        // act as normal mode
        if (test_finish_callback) {
            test_finish_callback();
        }
    }
}

void set_test_finish_callback(std::function<void()> callback)
{
    test_finish_callback = callback;
}
} // namespace kinoshita_lab::stemsmidi::product_test