/*
  ==============================================================================

    CpuLoadComp.h
    Created: 3 Mar 2021 8:15:30pm
    Author:  Luca Bondi

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class CpuLoadComp : public Component {
public:
    CpuLoadComp();

    ~CpuLoadComp();

    void paint(Graphics &) override;

    void resized() override;
    
    void setLoad(float);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CpuLoadComp)

    /** Load indicator text */
    Label text;
    /** Label for load indicator text */
    Label label;

    // Constants
    const float labelWidth = 45;

};
