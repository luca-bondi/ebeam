#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    
    appVersion = JUCEApplication::getInstance()->getApplicationVersion();
    
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
    widthBeam1Knob.setRange(0,1,0.01);
    widthBeam1Knob.addListener(this);
    addAndMakeVisible(widthBeam1Knob);
    
    widthBeam2Knob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    widthBeam2Knob.setTextBoxStyle(Slider::TextBoxLeft, false, LABEL_WIDTH, LABEL_HEIGHT);
    widthBeam2Knob.setColour(Slider::thumbColourId, beamColours[1]);
    widthBeam2Knob.setRange(0,1,0.01);
    widthBeam2Knob.addListener(this);
    addAndMakeVisible(widthBeam2Knob);
    
    
    //==============================================================================
    panLabel.setText("PAN", NotificationType::dontSendNotification);
    panLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(panLabel);
    
    panBeam1Knob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    panBeam1Knob.setTextBoxStyle(Slider::TextBoxRight, false, LABEL_WIDTH, LABEL_HEIGHT);
    panBeam1Knob.setColour(Slider::thumbColourId, beamColours[0]);
    panBeam1Knob.setRange(-1,1,0.01);
    panBeam1Knob.addListener(this);
    addAndMakeVisible(panBeam1Knob);
    
    panBeam2Knob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    panBeam2Knob.setTextBoxStyle(Slider::TextBoxLeft, false, LABEL_WIDTH, LABEL_HEIGHT);
    panBeam2Knob.setColour(Slider::thumbColourId, beamColours[1]);
    panBeam2Knob.setRange(-1,1,0.01);
    panBeam2Knob.addListener(this);
    addAndMakeVisible(panBeam2Knob);
    
    //==============================================================================
    
    levelLabel.setText("LEVEL", NotificationType::dontSendNotification);
    levelLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(levelLabel);
    
    levelBeam1Knob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    levelBeam1Knob.setTextBoxStyle(Slider::TextBoxRight, false, LABEL_WIDTH, LABEL_HEIGHT);
    levelBeam1Knob.setColour(Slider::thumbColourId, beamColours[0]);
    levelBeam1Knob.setRange(-10,10,0.1);
    levelBeam1Knob.addListener(this);
    addAndMakeVisible(levelBeam1Knob);
    
    levelBeam2Knob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    levelBeam2Knob.setTextBoxStyle(Slider::TextBoxLeft, false, LABEL_WIDTH, LABEL_HEIGHT);
    levelBeam2Knob.setColour(Slider::thumbColourId, beamColours[1]);
    levelBeam2Knob.setRange(-10,10,0.1);
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

    addAndMakeVisible(beam1Meter);
    addAndMakeVisible(beam2Meter);
    
    //==============================================================================
    
    hpfLabel.setText("HPF", NotificationType::dontSendNotification);
    hpfLabel.setJustificationType(Justification::left);
    hpfLabel.attachToComponent(&hpfSlider, true);
    
    hpfSlider.setSliderStyle(Slider::LinearHorizontal);
    hpfSlider.setTextBoxStyle(Slider::TextBoxRight, false, LABEL_WIDTH, LABEL_HEIGHT);
    hpfSlider.setRange(20,500,1);
    hpfSlider.addListener(this);
    addAndMakeVisible(hpfSlider);
    
    //==============================================================================

    addAndMakeVisible(inputMeter);
    
    //==============================================================================
    
    gainLabel.setText("GAIN", NotificationType::dontSendNotification);
    gainLabel.setJustificationType(Justification::left);
    gainLabel.attachToComponent(&gainSlider, true);
    
    gainSlider.setSliderStyle(Slider::LinearHorizontal);
    gainSlider.setTextBoxStyle(Slider::TextBoxRight, false, LABEL_WIDTH, LABEL_HEIGHT);
    gainSlider.setRange(0,40,0.1);
    gainSlider.addListener(this);
    addAndMakeVisible(gainSlider);
    
    //=====================================================
    // Add CPU Load
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
    configCombo.setSelectedItemIndex(0);
    addAndMakeVisible(configCombo);
    
    
    /* Initialize OSC */
    serverIp = IPAddress("127.0.0.1");
    oscIpLabel.setText("IP", NotificationType::dontSendNotification);
    oscIpLabel.attachToComponent(&oscIp, true);
    oscIp.setText(serverIp.toString());
    oscIp.setJustification(Justification::centred);
    addAndMakeVisible(oscIp);
    
    oscPortLabel.setText("PORT", NotificationType::dontSendNotification);
    oscPortLabel.attachToComponent(&oscPort, true);
    oscPort.setText(String(serverPort));
    oscPort.setJustification(Justification::centred);
    addAndMakeVisible(oscPort);
    
    oscConnectButton.setButtonText("Connect");
    oscConnectButton.addListener(this);
    addAndMakeVisible(oscConnectButton);
    
    oscStatus.setColours(Colours::red,Colours::grey);
    addAndMakeVisible(oscStatus);
    
    //=====================================================
    /* Set polling timer to fetch updates from VST */
    startTimerHz(10);
    
    /* Set this as a listener for OSC messages */
    receiver.addListener(this);
    
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
    g.drawText(String("Eventide - Ebeamer Controller v") + appVersion, versionArea, Justification::centredBottom, false);
}

void MainComponent::resized()
{
    auto area = getLocalBounds();
    area.removeFromTop(TOP_BOTTOM_MARGIN);
    area.removeFromBottom(TOP_BOTTOM_MARGIN);
    
    auto oscArea = area.removeFromTop(OSC_HEIGHT);
    
    // Center area
    const int oscTotalWidth = OSC_IP_LABEL_WIDTH+OSC_IP_WIDTH+OSC_PORT_LABEL_WIDTH+OSC_PORT_WIDTH+OSC_CONNECT_MARGIN_LEFT+OSC_CONNECT_WIDTH+OSC_LED_MARGIN_LEFT+OSC_LED_WIDTH;
    oscArea = oscArea.withSizeKeepingCentre(oscTotalWidth, OSC_HEIGHT);
    
    oscArea.removeFromLeft(OSC_IP_LABEL_WIDTH);
    oscIp.setBounds(oscArea.removeFromLeft(OSC_IP_WIDTH));
    oscArea.removeFromLeft(OSC_PORT_LABEL_WIDTH);
    oscPort.setBounds(oscArea.removeFromLeft(OSC_PORT_WIDTH));
    oscArea.removeFromLeft(OSC_CONNECT_MARGIN_LEFT);
    oscConnectButton.setBounds(oscArea.removeFromLeft(OSC_CONNECT_WIDTH));
    oscArea.removeFromLeft(OSC_LED_MARGIN_LEFT);
    oscStatus.setBounds(oscArea.removeFromLeft(OSC_LED_WIDTH));
    
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
    if (slider == &steerBeamX1Slider){
        steerX[0] = slider->getValue();
        setBeamSteerX(0,slider->getValue());
    }else if(slider == &steerBeamX2Slider){
        steerX[1] = slider->getValue();
        setBeamSteerX(1,slider->getValue());
    }else if (slider == &steerBeamY1Slider){
        steerY[0] = slider->getValue();
        setBeamSteerY(0,slider->getValue());
    }else if(slider == &steerBeamY2Slider){
        steerY[1] = slider->getValue();
        setBeamSteerY(1,slider->getValue());
    }else if(slider == &widthBeam1Knob){
        width[0] = slider->getValue();
        if (connected) sendOscMessage("widthBeam1", width[0]);
    }else if(slider == &widthBeam2Knob){
        width[1] = slider->getValue();
        if (connected) sendOscMessage("widthBeam2", width[1]);
    }else if(slider == &panBeam1Knob){
        if (connected) sendOscMessage("panBeam1", (float)panBeam1Knob.getValue());
    }else if(slider == &panBeam2Knob){
        if (connected) sendOscMessage("panBeam2", (float)panBeam2Knob.getValue());
    }else if(slider == &levelBeam1Knob){
        if (connected) sendOscMessage("levelBeam1", (float)levelBeam1Knob.getValue());
    }else if(slider == &levelBeam2Knob){
        if (connected) sendOscMessage("levelBeam2", (float)levelBeam2Knob.getValue());
    }else if(slider == &hpfSlider){
        if (connected) sendOscMessage("hpf", (float)hpfSlider.getValue());
    }else if(slider == &gainSlider){
        if (connected) sendOscMessage("gainMic", (float)gainSlider.getValue());
    }
}

void MainComponent::buttonClicked (Button* button){
    if (button == &oscConnectButton){
        if (connected){
            oscDisconnect();
        }else{
            serverIp = IPAddress(oscIp.getTextValue().toString());
            serverPort = oscPort.getTextValue().toString().getIntValue();
            oscConnect();
        }
    }
}

void MainComponent::buttonStateChanged(Button * button){
    if (button == &frontToggle){
        frontFacing = frontToggle.getToggleState();
        scene.resized();
        if (connected)
            sendOscMessage("frontFacing", (bool)frontFacing);
    } else if (button == &muteBeam1Button){
        mute[0] = muteBeam1Button.getToggleState();
        scene.resized();
        if (connected)
            sendOscMessage("muteBeam1", (bool)mute[0]);
    } else if (button == &muteBeam2Button){
        mute[1] = muteBeam2Button.getToggleState();
        scene.resized();
        if (connected)
            sendOscMessage("muteBeam2", (bool)mute[1]);
    }
    
}

void MainComponent::comboBoxChanged(ComboBox * comboBox){
    if (comboBox == &configCombo){
        config = configCombo.getSelectedItemIndex();
        resized();
        if (connected)
            sendOscMessage("config", static_cast<MicConfig>((int)config));
    }
}

//=====================================================================================
//OSC Methods

void MainComponent::oscConnect(){
    if (sender.connectToSocket(socket,serverIp.toString(),serverPort)){
        int localPort = 9001;
        while (socket.getBoundPort()==-1 && !socket.bindToPort(localPort) && (localPort<65535))
            localPort++;
        if (localPort==65535){
            std::ostringstream errMsg;
            errMsg << "Error: cannot find a free port to listen on";
            showConnectionErrorMessage (errMsg.str());
            return;
        }
        if (!receiver.connectToSocket(socket)){
            std::ostringstream errMsg;
            errMsg << "Error: cannot listen on port " << socket.getBoundPort();
            showConnectionErrorMessage (errMsg.str());
            return;
        }
        
        /* Connection successful */
        oscConnectButton.setButtonText("Disconnect");
        oscIp.setEnabled(false);
        oscPort.setEnabled(false);
        connected = true;
        oscStatus.setColours(Colours::green,Colours::grey);
        
        /* Determine local IP */
        auto ipArray = IPAddress::getAllAddresses();
        int mostLikelyIdx = 0;
        int mostLikelyScore = 0;
        for (auto idx = 0; idx < ipArray.size(); idx++){
            auto ip = ipArray[idx];
            int score = 0;
            while (ip.address[score] == serverIp.address[score])
                score ++;
            if (score > mostLikelyScore){
                mostLikelyScore = score;
                mostLikelyIdx = idx;
            }
        }
        localIp = ipArray[mostLikelyIdx];
        
    }else{
        std::ostringstream errMsg;
        errMsg << "Error: cannot connect to " << serverIp.toString() << " on " << serverPort;
        showConnectionErrorMessage (errMsg.str());
    }
}

void MainComponent::oscDisconnect(){
    if (sender.disconnect()){
        if (receiver.disconnect()){
            oscConnectButton.setButtonText("Connect");
            oscIp.setEnabled(true);
            oscPort.setEnabled(true);
            connected = false;
            oscStatus.setColours(Colours::red,Colours::grey);
        }else{
            showConnectionErrorMessage ("Error: could not disconnect receiver");
        }
    }else{
        showConnectionErrorMessage ("Error: could not disconnect sender");
    }
}


void MainComponent::oscMessageReceived (const OSCMessage& message){
    
    if ((message.size() == 1) && (message[0].isFloat32())){
        auto val = message[0].getFloat32();
        if (message.getAddressPattern() == "/ebeamer/steerBeamX1"){
            steerBeamX1Slider.setValue(val,dontSendNotification);
            steerX[0] = val;
        }else if (message.getAddressPattern() == "/ebeamer/steerBeamX2"){
            steerBeamX2Slider.setValue(val,dontSendNotification);
            steerX[1] = val;
        }else if (message.getAddressPattern() == "/ebeamer/steerBeamY1"){
            steerBeamY1Slider.setValue(val,dontSendNotification);
            steerY[0] = val;
        }else if (message.getAddressPattern() == "/ebeamer/steerBeamY2"){
            steerBeamY2Slider.setValue(val,dontSendNotification);
            steerY[1] = val;
        }else if (message.getAddressPattern() == "/ebeamer/widthBeam1"){
            widthBeam1Knob.setValue(val,dontSendNotification);
            width[0] = val;
        }else if (message.getAddressPattern() == "/ebeamer/widthBeam2"){
            widthBeam2Knob.setValue(val,dontSendNotification);
            width[1] = val;
        }else if (message.getAddressPattern() == "/ebeamer/panBeam1"){
            panBeam1Knob.setValue(val,dontSendNotification);
        }else if (message.getAddressPattern() == "/ebeamer/panBeam2"){
            panBeam2Knob.setValue(val,dontSendNotification);
        }else if (message.getAddressPattern() == "/ebeamer/levelBeam1"){
            levelBeam1Knob.setValue(val,dontSendNotification);
        }else if (message.getAddressPattern() == "/ebeamer/levelBeam2"){
            levelBeam2Knob.setValue(val,dontSendNotification);
        }else if (message.getAddressPattern() == "/ebeamer/gainMic"){
            gainSlider.setValue(val,dontSendNotification);
        }else if (message.getAddressPattern() == "/ebeamer/hpf"){
            hpfSlider.setValue(val,dontSendNotification);
        }else if (message.getAddressPattern() == "/ebeamer/cpuLoad"){
            cpuLoad.setLoad(val);
        }
    }else if ((message.size() == 1) && (message[0].isInt32())){
        auto val = message[0].getInt32();
        if (message.getAddressPattern() == "/ebeamer/muteBeam1"){
            muteBeam1Button.setToggleState(val,dontSendNotification);
            mute[0] = val;
        }else if (message.getAddressPattern() == "/ebeamer/muteBeam2"){
            muteBeam2Button.setToggleState(val,dontSendNotification);
            mute[1] = val;
        }else if (message.getAddressPattern() == "/ebeamer/frontFacing"){
            if (val != frontToggle.getToggleState()){
                frontToggle.setToggleState(val,dontSendNotification);
                frontFacing = val;
                scene.resized();
            }
        }else if (message.getAddressPattern() == "/ebeamer/config"){
            if (val != configCombo.getSelectedItemIndex()){
                configCombo.setSelectedItemIndex(val);
                config = val;
                resized();
            }
        }
    }else if ((message.size() == 1) && (message[0].isBlob())){
        auto val = message[0].getBlob();
        if (message.getAddressPattern() == "/ebeamer/inMeters"){
            std::vector<float> values((float*)val.begin(),(float*)val.end());
            inputMeter.setValues(values);
        } else if (message.getAddressPattern() == "/ebeamer/outMeters"){
            beam1Meter.setValue(((float*)val.getData())[0]);
            beam2Meter.setValue(((float*)val.getData())[1]);
        }
    }else if ((message.size() == 3) && (message[0].isInt32()) && (message[1].isInt32()) && (message[2].isBlob())){
        auto nRows = message[0].getInt32();
        auto nCols = message[1].getInt32();
        auto val = message[2].getBlob();
        if (message.getAddressPattern() == "/ebeamer/doaEnergy"){
            Eigen::Map<Eigen::MatrixXf> newEnergy((float*)val.getData(),nRows,nCols);
            energy = newEnergy;
        }
    }
}

void MainComponent::timerCallback(){
    if (connected){
        OSCMessage msg("/ebeamer/get");
        msg.addString(localIp.toString());
        msg.addInt32(socket.getBoundPort());
        sender.send(msg);
        oscStatus.toggle();
    }
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
    sendOscMessage(String("steerBeamX") + String(idx+1),newVal);
    
}

void MainComponent::setBeamSteerY(int idx, float newVal){
    steerY[idx] = newVal;
    if (idx==0){
        steerBeamY1Slider.setValue(newVal,dontSendNotification);
    }else{
        steerBeamY2Slider.setValue(newVal,dontSendNotification);
    }
    sendOscMessage(String("steerBeamY") + String(idx+1),newVal);
}

void MainComponent::sendOscMessage(const String& tag, float value){
    auto address = "/ebeamer/" + tag;
    if (connected){
        OSCMessage msg(address);
        msg.addFloat32(value);
        sender.send(msg);
    }
    // Toggle status even if not connect, to show that something should have happened
    oscStatus.toggle();
    
}

void MainComponent::sendOscMessage(const String& tag, bool value){
    auto address = "/ebeamer/" + tag;
    if (connected){
        OSCMessage msg(address);
        msg.addInt32(value);
        sender.send(msg);
    }
    // Toggle status even if not connect, to show that something should have happened
    oscStatus.toggle();
    
}

void MainComponent::sendOscMessage(const String& tag, MicConfig value){
    auto address = "/ebeamer/" + tag;
    if (connected){
        OSCMessage msg(address);
        msg.addInt32(value);
        sender.send(msg);
    }
    // Toggle status even if not connect, to show that something should have happened
    oscStatus.toggle();
    
}
