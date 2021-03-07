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
class MultiChannelLedBar : public juce::Component{
public:
    
    MultiChannelLedBar();
    
    ~MultiChannelLedBar() {};
    
    void paint(Graphics &) override;
    
    void resized() override;
    
    void setHorizontal() { isHorizontal = true; };
    
    void setVertical() { isHorizontal = false; };
    
    static Colour dbToColor(float valDb);
    
    void setValues(const std::vector<float>&);
    
    
private:
    
    int meterId;
    
    bool isHorizontal = true;
    
    std::vector<std::unique_ptr<RoundLed>> leds;
    std::vector<float> values = {0,0};
    
    void makeLayout();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultiChannelLedBar)
};
