/*
  ==============================================================================

    MuteButton.h
    Created: 3 Mar 2021 8:10:28pm
    Author:  Luca Bondi

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class MuteButton  : public juce::TextButton
{
public:
    MuteButton(){
        setClickingTogglesState(true);
    };

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MuteButton)
};
