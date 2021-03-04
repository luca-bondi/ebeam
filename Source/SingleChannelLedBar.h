/*
  ==============================================================================

    SingleChannelLedBar.h
    Created: 3 Mar 2021 8:17:46pm
    Author:  Luca Bondi

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "RoundLed.h"

//==============================================================================
/*
*/
class SingleChannelLedBar : public juce::Component, public juce::Timer {
public:
    
    SingleChannelLedBar(size_t numLeds = 7, bool isHorizontal = false);
    
    ~SingleChannelLedBar() {};
    
//    void setCallback(MeterDecay::Callback *cb, int meterId, int channel);
    
    void paint(Graphics &) override;
    
    void resized() override;
    
    static Colour dbToColour(float valDb, float thDb);
    
private:
    
//    MeterDecay::Callback *provider = nullptr;
    int meterId;
    int channel;
    
    bool isHorizontal;
    
    std::vector<float> th;
    std::vector<std::unique_ptr<RoundLed>> leds;
    
    void timerCallback() override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SingleChannelLedBar)
};

