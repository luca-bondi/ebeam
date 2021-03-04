/*
  ==============================================================================

    PanSlider.h
    Created: 3 Mar 2021 8:06:08pm
    Author:  Luca Bondi

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

using namespace juce;

//==============================================================================
/*
*/
class PanSlider  : public juce::Slider
{
public:
    PanSlider() {};

    double getValueFromText(const String &text) override {

        if (text.startsWithIgnoreCase("C") || text.startsWithIgnoreCase("0")) {
            return 0;
        }

        float sign = 1;
        if (text.endsWithIgnoreCase("L")) {
            sign = -1;
        }

        String valueText = text.upToFirstOccurrenceOf("%", false, false).trim();
        double val = valueText.getDoubleValue() / 100.;
        return sign * val;
    }

    String getTextFromValue(double value) override {
        jassert(value >= -1 && value <= 1);
        std::ostringstream valueString;
        if (value == 0) {
            valueString << "C";
        } else if (value < 0) {
            valueString << roundToInt(abs(value) * 100) << " % L";
        } else {
            valueString << roundToInt((value) * 100) << " % R";
        }

        return valueString.str();
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanSlider)
};
