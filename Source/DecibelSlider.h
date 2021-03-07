/*
  ==============================================================================

    DecibelSlider.h
    Created: 3 Mar 2021 8:08:08pm
    Author:  Luca Bondi

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#define DB_MINUS_INF -100.0

//==============================================================================
/*
*/
class DecibelSlider  : public Slider
{
public:
    DecibelSlider() {};

    double getValueFromText(const String &text) override {

        auto decibelText = text.upToFirstOccurrenceOf("dB", false, false).trim();

        return decibelText.equalsIgnoreCase("-INF") ? DB_MINUS_INF
                                                    : decibelText.getDoubleValue();  // [2]
    }

    String getTextFromValue(double value) override {
        return Decibels::toString(value, 1, DB_MINUS_INF);
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DecibelSlider)
};
