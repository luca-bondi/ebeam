#pragma once

#include <JuceHeader.h>
#include "ebeamerDefs.h"

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
    String appName;
    const String appManufacturer = "Eventide";
    
    //==============================================================================
    const Identifier energyIdentifier = Identifier("doaEnergy");
    Scene scene;
    
    //==============================================================================
    Label steerLabel;
    const Identifier steerX1Identifier = Identifier("steerBeamX1");
    const Identifier steerX2Identifier = Identifier("steerBeamX2");
    const Identifier steerY1Identifier = Identifier("steerBeamY1");
    const Identifier steerY2Identifier = Identifier("steerBeamY2");
    SteerSlider steerBeamX1Slider, steerBeamX2Slider;
    SteerSlider steerBeamY1Slider, steerBeamY2Slider;
    
    //==============================================================================
    Label widthLabel;
    const Identifier width1Identifier = Identifier("widthBeam1");
    const Identifier width2Identifier = Identifier("widthBeam2");
    WidthSlider widthBeam1Knob, widthBeam2Knob;
    
    //==============================================================================
    Label panLabel;
    const Identifier pan1Identifier = Identifier("panBeam1");
    const Identifier pan2Identifier = Identifier("panBeam2");
    PanSlider panBeam1Knob, panBeam2Knob;
    
    //==============================================================================
    Label levelLabel;
    const Identifier level1Identifier = Identifier("levelBeam1");
    const Identifier level2Identifier = Identifier("levelBeam2");
    LevelSlider levelBeam1Knob, levelBeam2Knob;
    
    //==============================================================================
    Label muteLabel;
    const Identifier mute1Identifier = Identifier("muteBeam1");
    const Identifier mute2Identifier = Identifier("muteBeam2");
    MuteButton muteBeam1Button, muteBeam2Button;
    
    //==============================================================================
    const Identifier inMetersIdentifier = Identifier("inMeters");
    MultiChannelLedBar inputMeter;
    const Identifier outMeter1Identifier = Identifier("outMeter1");
    const Identifier outMeter2Identifier = Identifier("outMeter2");
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
    
#ifdef TARGET_OS_IOS
    const bool controlTextBoxEditable = false;
#else
    const bool controlTextBoxEditable = true;
#endif
    
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
    
    void oscConnect();
    void oscDisconnect();
    
    //==============================================================================
    /* Listeners and callbacks */
    
    void buttonClicked (Button*) override;
    void comboBoxChanged(ComboBox *) override;
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
