#pragma once
#ifndef STEMSMIDI_ONE_POLE_FILTER_HPP
#define STEMSMIDI_ONE_POLE_FILTER_HPP

namespace kinoshita_lab
{
namespace stemsmidi
{
class OnePoleFilter
{
public:
    static constexpr float kDefaultAlpha = 0.8f; ///< Tuned for  500us, 512 resolution

    OnePoleFilter() : alpha_(kDefaultAlpha), output_(0.0f) {}

    virtual ~OnePoleFilter() = default;

    void setLastValue(const float value)
    {
        output_ = value;
    }

    void update(const float input)
    {
        const auto output = alpha_ * input + (1.0f - alpha_) * output_;
        output_           = output;
    }
    float alpha_  = kDefaultAlpha;
    float output_ = 0.0f;
};
} // namespace stemsmidi
} // namespace kinoshita_lab

#endif // STEMSMIDI_ONE_POLE_FILTER_HPP
