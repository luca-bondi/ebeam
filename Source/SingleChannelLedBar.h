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
class SingleChannelLedBar : public juce::Component{
public:
    
    SingleChannelLedBar(size_t numLeds = 7, bool isHorizontal = false);
    
    ~SingleChannelLedBar() {};
    
    void paint(Graphics &) override;
    
    void resized() override;
    
    static Colour dbToColour(float valDb, float thDb);
    
    void setValue(float);
    
    void reset();
    
private:
    
    int meterId;
    int channel;
    
    bool isHorizontal;
    
    std::vector<float> th;
    std::vector<std::unique_ptr<RoundLed>> leds;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SingleChannelLedBar)
};

