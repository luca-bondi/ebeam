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
public EbeamerGUI::Callback
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
    /* GUI instance and utilities */
    EbeamerGUI gui;
    void showConnectionErrorMessage (const String&);
    
    //==============================================================================
    /* GUI callback */
    bool oscConnect(const String& serverIp, int serverPort) override;
    bool oscDisconnect(const String& serverIp, int serverPort) override;
    bool isConnected() const override;
    
    //==============================================================================
    /** OSC */
    
    const float oscPollingFreq = 10;
    bool connected;
    
    OSCController oscController;
    
    //==============================================================================
    /* ValueTree */
    File statusFile;
    ValueTree valueTree;
    ValueTreeFile valueTreeFile;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
