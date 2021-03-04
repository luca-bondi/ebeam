#pragma once

#include <JuceHeader.h>
#include "ebeamerDefs.h"
#include "PanSlider.h"
#include "FrequencySlider.h"
#include "DecibelSlider.h"
#include "MuteButton.h"
#include "CpuLoadComp.h"
#include "SingleChannelLedBar.h"
#include "MultiChannelLedBar.h"

using namespace juce;

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    //==============================================================================
//    TODO
//    SceneComp scene;
    
    //==============================================================================
    Label steerLabel;
    Label steerBeam1Label, steerBeam2Label;
    Slider steerBeamX1Slider, steerBeamX2Slider;
    Slider steerBeamY1Slider, steerBeamY2Slider;
    
    //==============================================================================
    Label widthLabel;
    Slider widthBeam1Knob, widthBeam2Knob;
    
    //==============================================================================
    Label panLabel;
    PanSlider panBeam1Knob, panBeam2Knob;
    
    //==============================================================================
    Label levelLabel;
    DecibelSlider levelBeam1Knob, levelBeam2Knob;
    
    //==============================================================================
    Label muteLabel;
    MuteButton muteBeam1Button, muteBeam2Button;
    
    //==============================================================================
    MultiChannelLedBar inputMeter;
    SingleChannelLedBar beam1Meter, beam2Meter;
    
    //==============================================================================
    Label hpfLabel;
    FrequencySlider hpfSlider;
    
    //==============================================================================
    Label gainLabel;
    DecibelSlider gainSlider;
    
    //==============================================================================
    /** CPU load component */
    CpuLoadComp cpuLoad;
    
    //==============================================================================
    /** Swap side toggle component */
    Label frontToggleLabel;
    ToggleButton frontToggle;
    
    //==============================================================================
    /** Configuration selection combo */
    
    Label configComboLabel;
    ComboBox configCombo;
    
    //==============================================================================
    const std::vector<Colour> beamColours = {Colours::orangered, Colours::royalblue};
    
    //==============================================================================
    /** State variables */
    MicConfig config = ULA_1ESTICK;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
