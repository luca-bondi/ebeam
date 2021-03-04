/*
  ==============================================================================

    MultiChannelLedBar.h
    Created: 3 Mar 2021 8:17:37pm
    Author:  Luca Bondi

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "RoundLed.h"

//==============================================================================
/*
*/
class MultiChannelLedBar : public juce::Component, public juce::Timer {
public:
    
    MultiChannelLedBar();
    
    ~MultiChannelLedBar() {};
    
    void paint(Graphics &) override;
    
    void resized() override;
    
//    void setCallback(MeterDecay::Callback *cb, int metId);
    
    void setHorizontal() { isHorizontal = true; };
    
    void setVertical() { isHorizontal = false; };
    
    static Colour dbToColor(float valDb);
    
    
private:
    
//    MeterDecay::Callback *callback = nullptr;
    int meterId;
    
    bool isHorizontal = true;
    
    std::vector<std::unique_ptr<RoundLed>> leds;
    std::vector<float> values;
    
    void timerCallback() override;
    
    void makeLayout();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultiChannelLedBar)
};
