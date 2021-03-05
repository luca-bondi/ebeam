#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    
    //==============================================================================
    /* Initialize parameters */
    config = 0;
    frontFacing = 0;
    for (auto beamIdx = 0; beamIdx < NUM_BEAMS; beamIdx++){
        mute[beamIdx] = 0;
        width[beamIdx] = 0;
        steerX[beamIdx] = 0;
        steerY[beamIdx] = 0;
    }
    
    //==============================================================================
    setSize(GUI_WIDTH, GUI_HEIGHT);
    
    //==============================================================================
    scene.setCallback(this);
    scene.setBeamColors(beamColours);
    addAndMakeVisible(scene);
    
    //==============================================================================
    steerLabel.setText("STEER", NotificationType::dontSendNotification);
    steerLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(steerLabel);
    
    steerBeam1Label.setText("1", NotificationType::dontSendNotification);
    steerBeam1Label.setJustificationType(Justification::left);
    steerBeam1Label.attachToComponent(&steerBeamX1Slider, true);
    addAndMakeVisible(steerBeam1Label);
    
    steerBeam2Label.setText("2", NotificationType::dontSendNotification);
    steerBeam2Label.setJustificationType(Justification::left);
    steerBeam2Label.attachToComponent(&steerBeamX2Slider, true);
    addAndMakeVisible(steerBeam2Label);
    
    steerBeamX1Slider.setSliderStyle(Slider::LinearHorizontal);
    steerBeamX1Slider.setTextBoxStyle(Slider::TextBoxRight, false, LABEL_WIDTH, LABEL_HEIGHT);
    steerBeamX1Slider.setColour(Slider::thumbColourId, beamColours[0]);
    steerBeamX1Slider.setRange(-1,1,0.01);
    steerBeamX1Slider.addListener(this);
    addAndMakeVisible(steerBeamX1Slider);
    
    steerBeamX2Slider.setSliderStyle(Slider::LinearHorizontal);
    steerBeamX2Slider.setTextBoxStyle(Slider::TextBoxRight, false, LABEL_WIDTH, LABEL_HEIGHT);
    steerBeamX2Slider.setColour(Slider::thumbColourId, beamColours[1]);
    steerBeamX2Slider.setRange(-1,1,0.01);
    steerBeamX2Slider.addListener(this);
    addAndMakeVisible(steerBeamX2Slider);
    
    steerBeamY1Slider.setSliderStyle(Slider::LinearVertical);
    steerBeamY1Slider.setTextBoxStyle(Slider::TextBoxAbove, false, LABEL_WIDTH, LABEL_HEIGHT);
    steerBeamY1Slider.setColour(Slider::thumbColourId, beamColours[0]);
    steerBeamY1Slider.setRange(-1,1,0.01);
    steerBeamY1Slider.addListener(this);
    addAndMakeVisible(steerBeamY1Slider);
    
    steerBeamY2Slider.setSliderStyle(Slider::LinearVertical);
    steerBeamY2Slider.setTextBoxStyle(Slider::TextBoxAbove, false, LABEL_WIDTH, LABEL_HEIGHT);
    steerBeamY2Slider.setColour(Slider::thumbColourId, beamColours[1]);
    steerBeamY2Slider.setRange(-1,1,0.01);
    steerBeamY2Slider.addListener(this);
    addAndMakeVisible(steerBeamY2Slider);
    
    //==============================================================================
    widthLabel.setText("WIDTH", NotificationType::dontSendNotification);
    widthLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(widthLabel);
    
    widthBeam1Knob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    widthBeam1Knob.setTextBoxStyle(Slider::TextBoxRight, false, LABEL_WIDTH, LABEL_HEIGHT);
    widthBeam1Knob.setColour(Slider::thumbColourId, beamColours[0]);
    widthBeam1Knob.setRange(-1,1,0.01);
    widthBeam1Knob.addListener(this);
    addAndMakeVisible(widthBeam1Knob);
    
    widthBeam2Knob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    widthBeam2Knob.setTextBoxStyle(Slider::TextBoxLeft, false, LABEL_WIDTH, LABEL_HEIGHT);
    widthBeam2Knob.setColour(Slider::thumbColourId, beamColours[1]);
    widthBeam2Knob.setRange(-1,1,0.01);
    widthBeam2Knob.addListener(this);
    addAndMakeVisible(widthBeam2Knob);
    
    
    //==============================================================================
    panLabel.setText("PAN", NotificationType::dontSendNotification);
    panLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(panLabel);
    
    panBeam1Knob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    panBeam1Knob.setTextBoxStyle(Slider::TextBoxRight, false, LABEL_WIDTH, LABEL_HEIGHT);
    panBeam1Knob.setColour(Slider::thumbColourId, beamColours[0]);
    panBeam1Knob.setPopupMenuEnabled(true);
    panBeam1Knob.addListener(this);
    addAndMakeVisible(panBeam1Knob);
    
    panBeam2Knob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    panBeam2Knob.setTextBoxStyle(Slider::TextBoxLeft, false, LABEL_WIDTH, LABEL_HEIGHT);
    panBeam2Knob.setColour(Slider::thumbColourId, beamColours[1]);
    panBeam2Knob.setPopupMenuEnabled(true);
    panBeam2Knob.addListener(this);
    addAndMakeVisible(panBeam2Knob);
    
    //==============================================================================
    
    levelLabel.setText("LEVEL", NotificationType::dontSendNotification);
    levelLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(levelLabel);
    
    levelBeam1Knob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    levelBeam1Knob.setTextBoxStyle(Slider::TextBoxRight, false, LABEL_WIDTH, LABEL_HEIGHT);
    levelBeam1Knob.setColour(Slider::thumbColourId, beamColours[0]);
    levelBeam1Knob.setPopupMenuEnabled(true);
    levelBeam1Knob.addListener(this);
    addAndMakeVisible(levelBeam1Knob);
    
    levelBeam2Knob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    levelBeam2Knob.setTextBoxStyle(Slider::TextBoxLeft, false, LABEL_WIDTH, LABEL_HEIGHT);
    levelBeam2Knob.setColour(Slider::thumbColourId, beamColours[1]);
    levelBeam2Knob.setPopupMenuEnabled(true);
    levelBeam2Knob.addListener(this);
    addAndMakeVisible(levelBeam2Knob);
    
    
    //==============================================================================
    
    muteLabel.setText("MUTE", NotificationType::dontSendNotification);
    muteLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(muteLabel);
    
    muteBeam1Button.setButtonText("1");
    muteBeam1Button.addListener(this);
    addAndMakeVisible(muteBeam1Button);
    
    muteBeam2Button.setButtonText("2");
    muteBeam2Button.addListener(this);
    addAndMakeVisible(muteBeam2Button);
    
    getLookAndFeel().setColour(MuteButton::buttonOnColourId, Colours::darkred);
    
    //==============================================================================
    
//    beam1Meter.setCallback(&processor, 1, 0);
//    beam1Meter.startTimerHz(BEAM_METER_UPDATE_FREQ);
    addAndMakeVisible(beam1Meter);
    
//    beam2Meter.setCallback(&processor, 1, 1);
//    beam2Meter.startTimerHz(BEAM_METER_UPDATE_FREQ);
    addAndMakeVisible(beam2Meter);
    
    //==============================================================================
    
    hpfLabel.setText("HPF", NotificationType::dontSendNotification);
    hpfLabel.setJustificationType(Justification::left);
    hpfLabel.attachToComponent(&hpfSlider, true);
    
    hpfSlider.setSliderStyle(Slider::LinearHorizontal);
    hpfSlider.setTextBoxStyle(Slider::TextBoxRight, false, LABEL_WIDTH, LABEL_HEIGHT);
    hpfSlider.setPopupMenuEnabled(true);
    hpfSlider.addListener(this);
    addAndMakeVisible(hpfSlider);
    
//    hpfSliderAttachment.reset(new SliderAttachment(valueTreeState, "hpf", hpfSlider));
    
    //==============================================================================
    
//    inputMeter.setCallback(&processor, 0);
//    inputMeter.startTimerHz(INPUT_METER_UPDATE_FREQ);
    addAndMakeVisible(inputMeter);
    
    //==============================================================================
    
    gainLabel.setText("GAIN", NotificationType::dontSendNotification);
    gainLabel.setJustificationType(Justification::left);
    gainLabel.attachToComponent(&gainSlider, true);
    
    gainSlider.setSliderStyle(Slider::LinearHorizontal);
    gainSlider.setTextBoxStyle(Slider::TextBoxRight, false, LABEL_WIDTH, LABEL_HEIGHT);
    gainSlider.addListener(this);
    addAndMakeVisible(gainSlider);
    
    //=====================================================
    // Add CPU Load and start its timer
//    cpuLoad.setSource(&processor);
    cpuLoad.startTimerHz(CPULOAD_UPDATE_FREQ);
    addAndMakeVisible(cpuLoad);
    
    //=====================================================
    // Add front facing toggle
    frontToggleLabel.setText("FRONT", NotificationType::dontSendNotification);
    frontToggleLabel.attachToComponent(&frontToggle, true);
    frontToggle.addListener(this);
    addAndMakeVisible(frontToggle);
    
    
    //=====================================================
    // Configuration selection combo
    configComboLabel.setText("SETUP", NotificationType::dontSendNotification);
    configComboLabel.attachToComponent(&configCombo, true);
    configCombo.addItemList(micConfigLabels, 10);
    configCombo.addListener(this);
    addAndMakeVisible(configCombo);

    
    /* Initialize OSC */
    oscIpLabel.setText("IP", NotificationType::dontSendNotification);
    oscIpLabel.attachToComponent(&oscIp, true);
    oscIp.setText(serverIp);
    addAndMakeVisible(oscIp);
    
    oscPortLabel.setText("PORT", NotificationType::dontSendNotification);
    oscPortLabel.attachToComponent(&oscPort, true);
    oscPort.setText(String(serverPort));
    addAndMakeVisible(oscPort);
    
    oscConnect.setButtonText("Connect");
    oscConnect.addListener(this);
    addAndMakeVisible(oscConnect);
    
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
    
    g.setColour(Colours::white);
    g.setFont(15.0f);
    
    auto versionArea = getBounds().removeFromBottom(12);
    versionArea.removeFromBottom(2);
    g.setColour(Colours::lightgrey);
    g.setFont(12);
    //    TODO: app version
    g.drawText("Eventide - Ebeamer Controller v", versionArea, Justification::centredBottom, false);
}

void MainComponent::resized()
{
    auto area = getLocalBounds();
    area.removeFromTop(TOP_BOTTOM_MARGIN);
    area.removeFromBottom(TOP_BOTTOM_MARGIN);
    
    auto oscArea = area.removeFromTop(OSC_HEIGHT);
    oscArea.removeFromLeft(OSC_IP_LABEL_WIDTH);
    oscIp.setBounds(oscArea.removeFromLeft(OSC_IP_WIDTH));
    oscArea.removeFromLeft(OSC_PORT_LABEL_WIDTH);
    oscPort.setBounds(oscArea.removeFromLeft(OSC_PORT_WIDTH));
    oscArea.removeFromLeft(OSC_CONNECT_MARGIN_LEFT);
    oscConnect.setBounds(oscArea.removeFromLeft(OSC_CONNECT_WIDTH));
    
    area.removeFromTop(OSC_BOTTOM_MARGIN);
    auto sceneArea = area.removeFromTop(SCENE_HEIGHT);
    
    if (isLinearArray(static_cast<MicConfig>((int)config))){
        steerBeamY1Slider.setVisible(false);
        steerBeamY2Slider.setVisible(false);
        sceneArea.removeFromRight((area.getWidth() - SCENE_WIDTH) / 2);
        sceneArea.removeFromLeft((area.getWidth() - SCENE_WIDTH) / 2);
        scene.setBounds(sceneArea);
    }else{
        steerBeamY1Slider.setVisible(true);
        steerBeamY2Slider.setVisible(true);
        sceneArea.removeFromLeft(15);
        sceneArea.removeFromRight(15);
        steerBeamY1Slider.setBounds(sceneArea.removeFromLeft(50));
        steerBeamY2Slider.setBounds(sceneArea.removeFromRight(50));
        sceneArea.removeFromLeft(5);
        sceneArea.removeFromRight(5);
        sceneArea.removeFromTop(10);
        sceneArea.removeFromBottom(10);
        scene.setBounds(sceneArea);
    }
    
    area.removeFromLeft(LEFT_RIGHT_MARGIN);
    area.removeFromRight(LEFT_RIGHT_MARGIN);
    
    
    area.removeFromTop(STEER_SLIDER_TOP_MARGIN);
    steerBeamX1Slider.setBounds(area.removeFromTop(STEER_SLIDER_HEIGHT).withTrimmedLeft(LABEL_BEAM_WIDTH));
    steerBeamX2Slider.setBounds(area.removeFromTop(STEER_SLIDER_HEIGHT).withTrimmedLeft(LABEL_BEAM_WIDTH));
    
    steerLabel.setBounds(area.removeFromTop(LABEL_HEIGHT));
    
    area.removeFromLeft(KNOBS_LEFT_RIGHT_MARGIN);
    area.removeFromRight(KNOBS_LEFT_RIGHT_MARGIN);
    
    auto knobsArea = area.removeFromTop(KNOB_HEIGHT + KNOB_TOP_MARGIN);
    knobsArea.removeFromTop(KNOB_TOP_MARGIN);
    widthBeam1Knob.setBounds(knobsArea.removeFromLeft(KNOB_WIDTH));
    widthBeam2Knob.setBounds(knobsArea.removeFromRight(KNOB_WIDTH));
    widthLabel.setBounds(knobsArea);
    
    knobsArea = area.removeFromTop(KNOB_HEIGHT + KNOB_TOP_MARGIN);
    knobsArea.removeFromTop(KNOB_TOP_MARGIN);
    panBeam1Knob.setBounds(knobsArea.removeFromLeft(KNOB_WIDTH));
    panBeam2Knob.setBounds(knobsArea.removeFromRight(KNOB_WIDTH));
    panLabel.setBounds(knobsArea);
    
    knobsArea = area.removeFromTop(KNOB_HEIGHT + KNOB_TOP_MARGIN);
    knobsArea.removeFromTop(KNOB_TOP_MARGIN);
    levelBeam1Knob.setBounds(knobsArea.removeFromLeft(KNOB_WIDTH));
    levelBeam2Knob.setBounds(knobsArea.removeFromRight(KNOB_WIDTH));
    auto meterArea = knobsArea.removeFromLeft(BEAM_LED_WIDTH + BEAM_LEFT_RIGHT_MARGIN);
    meterArea.removeFromTop(BEAM_TOP_BOTTOM_MARGIN);
    meterArea.removeFromBottom(BEAM_TOP_BOTTOM_MARGIN);
    meterArea.removeFromLeft(BEAM_LEFT_RIGHT_MARGIN);
    beam1Meter.setBounds(meterArea.removeFromLeft(BEAM_LED_WIDTH));
    meterArea = knobsArea.removeFromRight(BEAM_LED_WIDTH + BEAM_LEFT_RIGHT_MARGIN);
    meterArea.removeFromTop(BEAM_TOP_BOTTOM_MARGIN);
    meterArea.removeFromBottom(BEAM_TOP_BOTTOM_MARGIN);
    meterArea.removeFromRight(BEAM_LEFT_RIGHT_MARGIN);
    beam2Meter.setBounds(meterArea.removeFromRight(BEAM_LED_WIDTH));
    levelLabel.setBounds(knobsArea);
    
    auto mutesArea = area.removeFromTop(MUTE_HEIGHT + MUTE_TOP_MARGIN);
    mutesArea.removeFromTop(MUTE_TOP_MARGIN);
    mutesArea.removeFromLeft(MUTE_LEFT_RIGHT_MARGIN);
    mutesArea.removeFromRight(MUTE_LEFT_RIGHT_MARGIN);
    muteBeam1Button.setBounds(mutesArea.removeFromLeft(MUTE_WIDTH));
    muteBeam2Button.setBounds(mutesArea.removeFromRight(MUTE_WIDTH));
    muteLabel.setBounds(mutesArea);
    
    area.removeFromTop(INPUT_SECTION_TOP_MARGIN);
    hpfSlider.setBounds(area.removeFromTop(INPUT_HPF_SLIDER_HEIGHT).withTrimmedLeft(INPUT_HPF_LABEL_WIDTH));
    
    auto inputLedArea = area.removeFromTop(INPUT_LED_HEIGHT);
    inputLedArea.removeFromLeft(INPUT_LEFT_RIGHT_MARGIN+4);
    inputLedArea.removeFromRight(INPUT_LEFT_RIGHT_MARGIN+23);
    inputMeter.setBounds(inputLedArea);
    
    gainSlider.setBounds(area.removeFromTop(INPUT_GAIN_SLIDER_HEIGHT).withTrimmedLeft(INPUT_GAIN_LABEL_WIDTH));
    
    //===============================================================
    /** Prepare area for the footer */
    area.removeFromTop(FOOTER_MARGIN);
    auto footerArea = area.removeFromTop(FOOTER_HEIGHT);
    
    /** Set area for CPU Load */
    cpuLoad.setBounds(footerArea.removeFromLeft(CPULOAD_WIDTH));
    
    /** Set area for front toggle */
    frontToggle.setBounds(footerArea.removeFromRight(FRONT_TOGGLE_WIDTH));
    footerArea.removeFromRight(FRONT_TOGGLE_LABEL_WIDTH);
    
    /** Set area for config combo */
    footerArea.removeFromLeft(CONFIG_COMBO_LABEL_WIDTH);
    configCombo.setBounds(footerArea.removeFromLeft(CONFIG_COMBO_WIDTH));
}

//====================================================================
/* Callbacks and listeners */

void MainComponent::sliderValueChanged(Slider * slider){
    //TODO: implement
}

void MainComponent::buttonClicked (Button* button){
    if (button == &oscConnect){
        if (connected){
            if (sender.disconnect()){
                oscConnect.setButtonText("Connect");
                connected = false;
            }else{
                showConnectionErrorMessage ("Error: could not disconnect");
            }
        }else{
            serverIp = oscIp.getTextValue().toString();
            serverPort = oscPort.getTextValue().toString().getIntValue();
            if (sender.connect(serverIp,serverPort)){
                oscConnect.setButtonText("Disconnect");
                connected = true;
            }else{
                std::ostringstream errMsg;
                errMsg << "Error: could not connect to " << serverIp << " on " << serverPort;
                showConnectionErrorMessage (errMsg.str());
            }
        }
    }
}

void MainComponent::buttonStateChanged(Button * button){
    //TODO: implement
}

void MainComponent::comboBoxChanged(ComboBox * comboBox){
    //TODO: implement
}

void MainComponent::oscMessageReceived (const OSCMessage& message){
    //TODO: implement
}

void MainComponent::timerCallback(){
    //TODO: implement
}

void MainComponent::showConnectionErrorMessage (const String& messageText){
    juce::AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                            "OSC error",
                                            messageText,
                                            "OK");
}

void MainComponent::setBeamSteerX(int idx, float newVal){
    steerX[idx] = newVal;
    if (idx==0){
        steerBeamX1Slider.setValue(newVal,dontSendNotification);
    }else{
        steerBeamX2Slider.setValue(newVal,dontSendNotification);
    }
    if (connected){
        OSCMessage msg(String("/ebeamer/steerX") + String(idx+1));
        msg.addFloat32(newVal);
        sender.send(msg);
    }
}

void MainComponent::setBeamSteerY(int idx, float newVal){
    steerY[idx] = newVal;
    if (idx==0){
        steerBeamY1Slider.setValue(newVal,dontSendNotification);
    }else{
        steerBeamY2Slider.setValue(newVal,dontSendNotification);
    }
    if (connected){
        OSCMessage msg(String("/ebeamer/steerY") + String(idx+1));
        msg.addFloat32(newVal);
        sender.send(msg);
    }
}
