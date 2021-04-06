#pragma once

#include <JuceHeader.h>
#include "ebeamerDefs.h"
#include "PanSlider.h"
#include "MuteButton.h"
#include "SingleChannelLedBar.h"
#include "MultiChannelLedBar.h"
#include "SceneComp.h"
#include "RoundLed.h"
#include "ValueTreeFile.h"

//==============================================================================
/*
 This component lives inside our window, and this is where you should put all
 your controls and content.
 */
class MainComponent  :
public Component,
private ValueTree::Listener,
private Button::Listener,
private ComboBox::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;
    
    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    
    String appVersion;
    
    //==============================================================================
//    SceneComp scene;
    
    //==============================================================================
    Label steerLabel;
    Label steerBeam1Label, steerBeam2Label;
    Slider steerBeamX1Slider, steerBeamX2Slider;
    Slider steerBeamY1Slider, steerBeamY2Slider;
    
    //==============================================================================
    Label widthLabel1,widthLabel2,widthLabel;
    Slider widthBeam1Knob, widthBeam2Knob;
    
    //==============================================================================
    Label panLabel1,panLabel2,panLabel;
    PanSlider panBeam1Knob, panBeam2Knob;
    
    //==============================================================================
    Label levelLabel1,levelLabel2,levelLabel;
    DecibelSlider levelBeam1Knob, levelBeam2Knob;
    
    //==============================================================================
    Label muteLabel1,muteLabel2,muteLabel;
    MuteButton muteBeam1Button, muteBeam2Button;
    
    //==============================================================================
    MultiChannelLedBar inputMeter;
    SingleChannelLedBar beam1Meter, beam2Meter;
    
    //==============================================================================
    const Identifier hpfIdentifier = Identifier("hpf");
    HpfSlider hpfSlider;
    
    //==============================================================================
    const Identifier gainIdentifier = Identifier("gainMic");
    GainSlider gainSlider;
    
    //==============================================================================
    /** CPU load component */
    const Identifier cpuIdentifier = Identifier("cpuLoad");
    CpuLoad cpuLoad;
    
    //==============================================================================
    /** Swap side toggle component */
    const Identifier frontIdentifier = Identifier("frontFacing");
    FrontToggle frontToggle;
    
    //==============================================================================
    /** Configuration selection combo */
    const Identifier configIdentifier = Identifier("config");
    ConfigComboBox configComboBox;
    
    
    //==============================================================================
    /* Layout functions */
    void layoutConfigOsc(Rectangle<int>& );
    
    //==============================================================================
    const std::vector<Colour> beamColours = {Colours::orangered, Colours::royalblue};
    
    
    //==============================================================================
    /** OSC */
    
    const float oscPollingFreq = 10;
    
    bool connected;
    OSCController oscController;
    
    const Identifier serversIdentifier = Identifier("servers");
    std::map<int,Server> servers;
    
    Value serverIp;
    Value serverPort;
        
    ComboBox oscIp;
    Label oscIpLabel;
    
    TextEditor oscPort;
    Label oscPortLabel;
    
    TextButton oscConnectButton;
    ActivityLed oscStatus;
    
    void oscConnect();
    void oscDisconnect();
    
    //==============================================================================
    /* Listeners and callbacks */
    
//    void sliderValueChanged(Slider *) override;
    void buttonClicked (Button*) override;
    
    void comboBoxChanged(ComboBox *) override;
//    
//    void oscMessageReceived (const OSCMessage&) override;
//    
//    void timerCallback() override;
    
    void showConnectionErrorMessage (const String&);
    
    
    //==============================================================================
    /* ValueTree */
    File statusFile;
    ValueTree valueTreePersistent;
    ValueTree valueTreeSession;
    ValueTreeFile valueTreeFile;
    
    Identifier serverIpIdentifier = Identifier("serverIp");
    Identifier serverPortIdentifier = Identifier("serverPort");
    
    
    void valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged,
                                           const Identifier& property) override;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
