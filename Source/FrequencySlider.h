/*
  ==============================================================================

    FrequencySlider.h
    Created: 3 Mar 2021 8:09:10pm
    Author:  Luca Bondi

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FrequencySlider  : public Slider
{
public:
    FrequencySlider() {};

    double getValueFromText(const String &text) override {

        auto hzText = text.upToFirstOccurrenceOf("Hz", false, false).trim();
        auto hzVal = roundToInt(hzText.getDoubleValue());
        return hzVal;
    }

    String getTextFromValue(double value) override {
        std::ostringstream valueString;
        valueString << roundToInt(value) << " Hz";
        return valueString.str();
    }


private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FrequencySlider)
};
