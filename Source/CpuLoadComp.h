/*
  ==============================================================================

    CpuLoadComp.h
    Created: 3 Mar 2021 8:15:30pm
    Author:  Luca Bondi

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

using namespace juce;
//==============================================================================
/*
*/
class CpuLoadComp : public juce::Component,
public juce::Timer {
public:
    CpuLoadComp();

    ~CpuLoadComp();

    class Callback {
    public:
        virtual ~Callback() = default;

        virtual float getCpuLoad() const = 0;
    };

    void setSource(Callback *cb);

    void paint(Graphics &) override;

    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CpuLoadComp)

    /** Load indicator text */
    Label text;
    /** Label for load indicator text */
    Label label;

    /** Timer callback */
    void timerCallback() override;

    /** Callback instance */
    Callback *callback = nullptr;

    // Constants
    const float labelWidth = 45;

};
