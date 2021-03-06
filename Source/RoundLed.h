/*
 ==============================================================================
 
 RoundLed.h
 Created: 3 Mar 2021 8:18:08pm
 Author:  Luca Bondi
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>

using namespace juce;

//==============================================================================
/*
 */
class RoundLed : public Component {
public:
    
    RoundLed() {};
    
    void paint(Graphics &) override;
    
    void resized() override;
    
    void setColour(const Colour&);
    
protected:
    
    Colour colour;
    
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RoundLed)
};

class ActivityLed: public RoundLed {
    
public:
    
    ActivityLed(){};
    
    void setColours(const Colour& colour1_,const Colour& colour2_);
    
    void toggle();
    
private:
    
    Colour colour1, colour2;
    
};
