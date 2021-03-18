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
#include "SceneComp.h"
#include "RoundLed.h"

//==============================================================================
/*
 This component lives inside our window, and this is where you should put all
 your controls and content.
 */
class MainComponent  :
public Component,
private OSCReceiver::Listener<OSCReceiver::MessageLoopCallback>,
private Timer,
private Slider::Listener,
private Button::Listener,
private ComboBox::Listener,
private SceneComp::Callback
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
    SceneComp scene;
    
    //==============================================================================
    Label steerLabel;
    Label steerBeam1Label, steerBeam2Label;
    Slider steerBeamX1Slider, steerBeamX2Slider;
    Slider steerBeamY1Slider, steerBeamY2Slider;
    
    //==============================================================================
    Label widthLabel1,widthLabel2;
    Slider widthBeam1Knob, widthBeam2Knob;
    
    //==============================================================================
    Label panLabel1,panLabel2;
    PanSlider panBeam1Knob, panBeam2Knob;
    
    //==============================================================================
    Label levelLabel1,levelLabel2;
    DecibelSlider levelBeam1Knob, levelBeam2Knob;
    
    //==============================================================================
    Label muteLabel1,muteLabel2;
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
    /* Layout functions */
    void layoutConfigOsc(Rectangle<int>& );
    
    //==============================================================================
    const std::vector<Colour> beamColours = {Colours::orangered, Colours::royalblue};
    
    //==============================================================================
    /** State variables */
    std::atomic<float> config;
    std::atomic<float> frontFacing;
    std::atomic<float> mute[NUM_BEAMS];
    std::atomic<float> width[NUM_BEAMS];
    std::atomic<float> steerX[NUM_BEAMS];
    std::atomic<float> steerY[NUM_BEAMS];
    
    Mtx energy;
    
    //==============================================================================
    /** OSC */
    OSCSender sender;
    OSCReceiver receiver;
    DatagramSocket socket;
    
    bool connected = false;
    IPAddress serverIp;
    
    /** Ebeamer VST port */
    int serverPort = 9001;
    
    /** Local IP */
    IPAddress localIp;
    
    TextEditor oscIp;
    Label oscIpLabel;
    
    TextEditor oscPort;
    Label oscPortLabel;
    
    
    TextButton oscConnectButton;
    ActivityLed oscStatus;
    
    void sendOscMessage(const String& path, float value);
    void sendOscMessage(const String& path, bool value);
    void sendOscMessage(const String& path, MicConfig value);
    
    void oscConnect();
    void oscDisconnect();
    
    //==============================================================================
    /* Listeners and callbacks */
    
    void sliderValueChanged(Slider *) override;
    
    void buttonClicked (Button*) override;
    void buttonStateChanged(Button *) override;
    
    void comboBoxChanged(ComboBox *) override;
    
    void oscMessageReceived (const OSCMessage&) override;
    
    void timerCallback() override;
    
    void showConnectionErrorMessage (const String&);
    
    const std::atomic<float> *getConfigParam() const override{
        return &config;
    }
    const std::atomic<float> *getFrontFacingParam() const override{
        return &frontFacing;
    }
    const std::atomic<float> *getBeamMute(int idx) const override{
        return &(mute[idx]);
    }
    const std::atomic<float> *getBeamWidth(int idx) const override{
        return &(width[idx]);
    }
    const std::atomic<float> *getBeamSteerX(int idx) const override{
        return &(steerX[idx]);
    }
    const std::atomic<float> *getBeamSteerY(int idx) const override{
        return &(steerY[idx]);
    }
    void setBeamSteerX(int idx, float newVal) override;
    void setBeamSteerY(int idx, float newVal) override;
    
    void getDoaEnergy(Mtx &en) const override{
        en = energy;
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
