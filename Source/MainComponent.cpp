#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    
    appVersion = JUCEApplication::getInstance()->getApplicationVersion();
    
    //==============================================================================
    /* Value Tree for persistent parameters */
    statusFile = File::getSpecialLocation(File::userDocumentsDirectory).getChildFile("EbeaMote.xml");
    valueTreePersistent = ValueTree("EbeaMote");
    valueTreeFile.init(valueTreePersistent, statusFile, true);
    
    if (!valueTreeFile.load()){
        /** Initialize value tree if not loaded */
        valueTreePersistent.setProperty(serverIpIdentifier, "", nullptr);
        valueTreePersistent.setProperty(serverPortIdentifier, 9001, nullptr);
        valueTreeFile.save();
    }
    
    serverIp = valueTreePersistent.getPropertyAsValue(serverIpIdentifier,nullptr);
    serverPort = valueTreePersistent.getPropertyAsValue(serverPortIdentifier,nullptr);
    
    /* Value tree for session parameters */
    valueTreeSession = ValueTree("EbeaMoteTmp");
    valueTreeSession.addListener(this);
    
    //==============================================================================
    /* OSC controller */
    oscController.init(valueTreeSession);
    oscController.initBroadcastReceiver(serversIdentifier);
    
    //==============================================================================
    /* Value Tree for session parameters */
    
    valueTreeSession.setProperty(configIdentifier,ULA_1ESTICK,nullptr);
    oscController.registerIdentifier(configIdentifier);
    
    valueTreeSession.setProperty(frontIdentifier,false,nullptr);
    oscController.registerIdentifier(frontIdentifier);
    
    valueTreeSession.setProperty(cpuIdentifier,0,nullptr);
    oscController.registerIdentifier(cpuIdentifier);
    
    valueTreeSession.setProperty(hpfIdentifier,20,nullptr);
    oscController.registerIdentifier(hpfIdentifier);
    
    valueTreeSession.setProperty(gainIdentifier,20,nullptr);
    oscController.registerIdentifier(gainIdentifier);
    
    valueTreeSession.setProperty(steerX1Identifier,-0.2,nullptr);
    oscController.registerIdentifier(steerX1Identifier);
    
    valueTreeSession.setProperty(steerX2Identifier,0.2,nullptr);
    oscController.registerIdentifier(steerX2Identifier);
    
    valueTreeSession.setProperty(steerY1Identifier,-0.2,nullptr);
    oscController.registerIdentifier(steerY1Identifier);
    
    valueTreeSession.setProperty(steerY2Identifier,0.2,nullptr);
    oscController.registerIdentifier(steerY2Identifier);
    
    valueTreeSession.setProperty(width1Identifier,0.2,nullptr);
    oscController.registerIdentifier(width1Identifier);
    
    valueTreeSession.setProperty(width2Identifier,0.4,nullptr);
    oscController.registerIdentifier(width2Identifier);
    
    valueTreeSession.setProperty(pan1Identifier,-0.5,nullptr);
    oscController.registerIdentifier(pan1Identifier);
    
    valueTreeSession.setProperty(pan2Identifier,0.5,nullptr);
    oscController.registerIdentifier(pan2Identifier);
    
    valueTreeSession.setProperty(level1Identifier,-4,nullptr);
    oscController.registerIdentifier(level1Identifier);
    
    valueTreeSession.setProperty(level2Identifier,4,nullptr);
    oscController.registerIdentifier(level2Identifier);
    
    valueTreeSession.setProperty(mute1Identifier,false,nullptr);
    oscController.registerIdentifier(mute1Identifier);
    
    valueTreeSession.setProperty(mute2Identifier,true,nullptr);
    oscController.registerIdentifier(mute2Identifier);
    
    Array<var> zeros(0,0,0,0);
    valueTreeSession.setProperty(inMetersIdentifier,zeros,nullptr);
    oscController.registerIdentifier(inMetersIdentifier);
    
    valueTreeSession.setProperty(outMeter1Identifier,0,nullptr);
    oscController.registerIdentifier(outMeter1Identifier);
    
    valueTreeSession.setProperty(outMeter2Identifier,0,nullptr);
    oscController.registerIdentifier(outMeter2Identifier);
    
//    valueTreeSession.setProperty(energyIdentifier,Array<double>(0,0,0,0,0,0,0,0),nullptr);
    oscController.registerIdentifier(energyIdentifier);
    
    
    //==============================================================================
    setSize(GUI_WIDTH, GUI_HEIGHT);
    
    //==============================================================================
//    scene.setCallback(this);
//    scene.setBeamColors(beamColours);
//    addAndMakeVisible(scene);
    
    //==============================================================================
    steerLabel.setText("STEER", NotificationType::dontSendNotification);
    steerLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(steerLabel);
    
    steerBeamX1Slider.init(valueTreeSession.getPropertyAsValue(steerX1Identifier, nullptr),beamColours[0],controlTextBoxEditable,false);
    steerBeamX2Slider.init(valueTreeSession.getPropertyAsValue(steerX2Identifier, nullptr),beamColours[1],controlTextBoxEditable,false);
    addAndMakeVisible(steerBeamX1Slider);
    addAndMakeVisible(steerBeamX2Slider);
    
    steerBeamY1Slider.init(valueTreeSession.getPropertyAsValue(steerY1Identifier, nullptr),beamColours[0],controlTextBoxEditable,true);
    steerBeamY2Slider.init(valueTreeSession.getPropertyAsValue(steerY2Identifier, nullptr),beamColours[1],controlTextBoxEditable,true);
    steerBeamY1Slider.setLabelVisible(false);
    steerBeamY2Slider.setLabelVisible(false);
    addAndMakeVisible(steerBeamY1Slider);
    addAndMakeVisible(steerBeamY2Slider);
    
    //==============================================================================
    widthLabel.setText("WIDTH", NotificationType::dontSendNotification);
    widthLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(widthLabel);

    widthBeam1Knob.init(valueTreeSession.getPropertyAsValue(width1Identifier, nullptr),beamColours[0],controlTextBoxEditable);
    widthBeam2Knob.init(valueTreeSession.getPropertyAsValue(width2Identifier, nullptr),beamColours[1],controlTextBoxEditable);
    addAndMakeVisible(widthBeam1Knob);
    addAndMakeVisible(widthBeam2Knob);
    
    //==============================================================================
    panLabel.setText("PAN", NotificationType::dontSendNotification);
    panLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(panLabel);

    panBeam1Knob.init(valueTreeSession.getPropertyAsValue(pan1Identifier, nullptr),beamColours[0],controlTextBoxEditable);
    panBeam2Knob.init(valueTreeSession.getPropertyAsValue(pan2Identifier, nullptr),beamColours[1],controlTextBoxEditable);
    
    addAndMakeVisible(panBeam1Knob);
    addAndMakeVisible(panBeam2Knob);
    
    //==============================================================================
    levelLabel.setText("LEVEL", NotificationType::dontSendNotification);
    levelLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(levelLabel);
    
    levelBeam1Knob.init(valueTreeSession.getPropertyAsValue(level1Identifier, nullptr),beamColours[0],controlTextBoxEditable);
    levelBeam2Knob.init(valueTreeSession.getPropertyAsValue(level2Identifier, nullptr),beamColours[1],controlTextBoxEditable);
    
    addAndMakeVisible(levelBeam1Knob);
    addAndMakeVisible(levelBeam2Knob);
    
    //==============================================================================
    muteLabel.setText("MUTE", NotificationType::dontSendNotification);
    muteLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(muteLabel);
    
    muteBeam1Button.init(valueTreeSession.getPropertyAsValue(mute1Identifier, nullptr),"1");
    muteBeam2Button.init(valueTreeSession.getPropertyAsValue(mute2Identifier, nullptr),"2");
    
    addAndMakeVisible(muteBeam1Button);
    addAndMakeVisible(muteBeam2Button);
    
    //==============================================================================
    
    beam1Meter.init(valueTreeSession.getPropertyAsValue(outMeter1Identifier, nullptr));
    beam2Meter.init(valueTreeSession.getPropertyAsValue(outMeter2Identifier, nullptr));
    addAndMakeVisible(beam1Meter);
    addAndMakeVisible(beam2Meter);
    
    //==============================================================================
    
    hpfSlider.init(valueTreeSession.getPropertyAsValue(hpfIdentifier, nullptr));
    addAndMakeVisible(hpfSlider);
    
    //==============================================================================

    inputMeter.init(valueTreeSession.getPropertyAsValue(inMetersIdentifier, nullptr));
    addAndMakeVisible(inputMeter);
    
    //==============================================================================
    // Gain
    gainSlider.init(valueTreeSession.getPropertyAsValue(gainIdentifier, nullptr));
    addAndMakeVisible(gainSlider);
    
    //=====================================================
    // Add CPU Load
    cpuLoad.init(valueTreeSession.getPropertyAsValue(cpuIdentifier, nullptr));
    addAndMakeVisible(cpuLoad);
    
    //=====================================================
    // Add front facing toggle
    frontToggle.init(valueTreeSession.getPropertyAsValue(frontIdentifier, nullptr));
    addAndMakeVisible(frontToggle);
    
    //=====================================================
    // Configuration selection combo
    configComboBox.init(valueTreeSession.getPropertyAsValue(configIdentifier, nullptr));
    addAndMakeVisible(configComboBox);
    
    /* Initialize OSC */
    oscIpLabel.setText("IP", NotificationType::dontSendNotification);
    oscIpLabel.attachToComponent(&oscIp, true);
    oscIp.setJustificationType(Justification::centred);
    oscIp.setEditableText(true);
    oscIp.setText(serverIp.toString(),dontSendNotification);
    oscIp.addListener(this);
    addAndMakeVisible(oscIp);
    
    oscPortLabel.setText("PORT", NotificationType::dontSendNotification);
    oscPortLabel.attachToComponent(&oscPort, true);
    oscPort.setText(serverPort.toString(),dontSendNotification);
    oscPort.setJustification(Justification::centred);
    oscPort.setKeyboardType(TextInputTarget::numericKeyboard);
    oscPort.onReturnKey = [this]{oscConnect();};
    addAndMakeVisible(oscPort);
    
    oscConnectButton.setButtonText("Connect");
    oscConnectButton.addListener(this);
    addAndMakeVisible(oscConnectButton);
    
    oscStatus.setColours(Colours::red,Colours::grey);
    addAndMakeVisible(oscStatus);
    
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
    g.drawText(String("Eventide - EbeaMote v") + appVersion, versionArea, Justification::centredBottom, false);
}

void MainComponent::resized()
{
    auto area = getLocalBounds();
    const bool portrait = area.getHeight() > area.getWidth();
    
    /* Overall minimum margin */
    const int screenMargin = jmin(5,(int)(0.03*area.getWidth()));
    area.removeFromLeft(screenMargin+SMALL_MARGIN);
    area.removeFromRight(screenMargin+SMALL_MARGIN);
    area.removeFromTop(screenMargin);
    area.removeFromBottom(screenMargin);
    
    /* Controls area */
    layoutConfigOsc(area);
    
    if (portrait){
        
        /* Landscape-only labels */
        steerBeamX1Slider.setLabelText("1");
        steerBeamX2Slider.setLabelText("2");
        widthBeam1Knob.setLabelVisible(false);
        widthBeam1Knob.setTextBoxPosition(Slider::TextEntryBoxPosition::TextBoxRight);
        panBeam1Knob.setLabelVisible(false);
        panBeam1Knob.setTextBoxPosition(Slider::TextEntryBoxPosition::TextBoxRight);
        levelBeam1Knob.setLabelVisible(false);
        levelBeam1Knob.setTextBoxPosition(Slider::TextEntryBoxPosition::TextBoxRight);
        muteBeam1Button.setLabelVisible(false);
        
        widthBeam2Knob.setLabelVisible(false);
        widthBeam2Knob.setTextBoxPosition(Slider::TextEntryBoxPosition::TextBoxLeft);
        panBeam2Knob.setLabelVisible(false);
        panBeam2Knob.setTextBoxPosition(Slider::TextEntryBoxPosition::TextBoxLeft);
        levelBeam2Knob.setLabelVisible(false);
        levelBeam2Knob.setTextBoxPosition(Slider::TextEntryBoxPosition::TextBoxLeft);
        muteBeam2Button.setLabelVisible(false);
        
        /* Portrait-only labels */
        steerLabel.setVisible(true);
        widthLabel.setVisible(true);
        panLabel.setVisible(true);
        muteLabel.setVisible(true);
        levelLabel.setVisible(true);
        
        /* Scene, aspect ratio 2:1 */
        auto sceneArea = area.removeFromTop(area.getWidth()/2);
        
        if (isLinearArray(valueTreeSession[configIdentifier])){
            steerBeamY1Slider.setVisible(false);
            steerBeamY2Slider.setVisible(false);
//            scene.setBounds(sceneArea);
        }else{
            steerBeamY1Slider.setVisible(true);
            steerBeamY2Slider.setVisible(true);
            sceneArea.removeFromLeft(SMALL_MARGIN);
            sceneArea.removeFromRight(SMALL_MARGIN);
            steerBeamY1Slider.setBounds(sceneArea.removeFromLeft(VER_SLIDER_WIDTH).withTrimmedTop(LARGE_MARGIN+SMALL_MARGIN));
            steerBeamY2Slider.setBounds(sceneArea.removeFromRight(VER_SLIDER_WIDTH).withTrimmedTop(LARGE_MARGIN+SMALL_MARGIN));
            sceneArea.removeFromLeft(SMALL_MARGIN);
            sceneArea.removeFromRight(SMALL_MARGIN);
//            scene.setBounds(sceneArea);
        }
        
        /* Gain slider */
        area.removeFromBottom(MEDIUM_MARGIN);
        gainSlider.setBounds(area.removeFromBottom(HOR_SLIDER_HEIGHT));
        
        /* Input LED */
        inputMeter.setBounds(area.removeFromBottom(LED_SIZE).withTrimmedLeft(LABEL_WIDTH).withTrimmedRight(LABEL_WIDTH));
        
        /* HPF slider */
        hpfSlider.setBounds(area.removeFromBottom(HOR_SLIDER_HEIGHT));
        area.removeFromBottom(LARGE_MARGIN);
        
        /* Derive margins and sizes based on remaninig space */
        const int availableHeight = area.getHeight();
        const int usedHeight = MEDIUM_MARGIN+HOR_SLIDER_HEIGHT+SMALL_MARGIN+LABEL_HEIGHT+SMALL_MARGIN+HOR_SLIDER_HEIGHT+3*(MEDIUM_MARGIN+KNOB_SIZE)+LARGE_MARGIN+MUTE_SIZE+LARGE_MARGIN+HOR_SLIDER_HEIGHT+LED_SIZE+HOR_SLIDER_HEIGHT;
        const int residualHeight = jmax(availableHeight - usedHeight,0);
        
        const int smallMargin = SMALL_MARGIN;
        const int mediumMargin = MEDIUM_MARGIN;
        const int largeMargin = LARGE_MARGIN;
        
        const int knobMuteTotalIncrease = residualHeight/2;
        const int horSliderTotalIncrease = residualHeight - knobMuteTotalIncrease;
        
        const int knobSize = KNOB_SIZE + knobMuteTotalIncrease/4;
        const int muteSize = MUTE_SIZE + knobMuteTotalIncrease/4;
        const int horSliderHeight = HOR_SLIDER_HEIGHT + horSliderTotalIncrease/4;
        
        const int controlsSideMargin = area.getWidth()*0.03;
        
        /* Allocate elements from top to bottom */
        
        /* Horizontal steering */
        steerLabel.setVisible(true);
        
        area.removeFromTop(mediumMargin);
        steerBeamX1Slider.setBounds(area.removeFromTop(horSliderHeight).withTrimmedLeft(SMALL_LABEL_WIDTH));
        area.removeFromTop(smallMargin);
        steerLabel.setBounds(area.removeFromTop(LABEL_HEIGHT));
        area.removeFromTop(smallMargin);
        steerBeamX2Slider.setBounds(area.removeFromTop(horSliderHeight).withTrimmedLeft(SMALL_LABEL_WIDTH));
        
        /* Width knobs */
        area.removeFromTop(mediumMargin);
        auto widthKnobsArea = area.removeFromTop(knobSize).withTrimmedLeft(controlsSideMargin).withTrimmedRight(controlsSideMargin);
        widthLabel.setBounds(widthKnobsArea.withSizeKeepingCentre(CENTRAL_LABEL_WIDTH, LABEL_HEIGHT));
        auto width1Area = widthKnobsArea.removeFromLeft((area.getWidth()-CENTRAL_LABEL_WIDTH)/2);
        auto width2Area = widthKnobsArea.removeFromRight((area.getWidth()-CENTRAL_LABEL_WIDTH)/2);
        widthBeam1Knob.setBounds(width1Area.removeFromLeft(widthBeam1Knob.getMinWidth()));
        widthBeam2Knob.setBounds(width2Area.removeFromRight(widthBeam2Knob.getMinWidth()));
        
        /* Pan knobs */
        area.removeFromTop(mediumMargin);
        auto panKnobsArea = area.removeFromTop(knobSize).withTrimmedLeft(controlsSideMargin).withTrimmedRight(controlsSideMargin);
        panLabel.setBounds(panKnobsArea.withSizeKeepingCentre(CENTRAL_LABEL_WIDTH, LABEL_HEIGHT));
        auto pan1Area = panKnobsArea.removeFromLeft((area.getWidth()-CENTRAL_LABEL_WIDTH)/2);
        auto pan2Area = panKnobsArea.removeFromRight((area.getWidth()-CENTRAL_LABEL_WIDTH)/2);
        panBeam1Knob.setBounds(pan1Area.removeFromLeft(panBeam1Knob.getMinWidth()));
        panBeam2Knob.setBounds(pan2Area.removeFromRight(panBeam2Knob.getMinWidth()));
        
        /* Levels and meters */
        area.removeFromTop(mediumMargin);
        auto levelsArea = area.removeFromTop(knobSize).withTrimmedLeft(controlsSideMargin).withTrimmedRight(controlsSideMargin);
        levelLabel.setBounds(levelsArea.withSizeKeepingCentre(CENTRAL_LABEL_WIDTH, LABEL_HEIGHT));
        auto level1Area = levelsArea.removeFromLeft((area.getWidth()-CENTRAL_LABEL_WIDTH)/2);
        auto level2Area = levelsArea.removeFromRight((area.getWidth()-CENTRAL_LABEL_WIDTH)/2);
        levelBeam1Knob.setBounds(level1Area.removeFromLeft(levelBeam1Knob.getMinWidth()));
        levelBeam2Knob.setBounds(level2Area.removeFromRight(levelBeam2Knob.getMinWidth()));
        beam1Meter.setBounds(level1Area.withSizeKeepingCentre(LED_SIZE, level1Area.getHeight()));
        beam2Meter.setBounds(level2Area.withSizeKeepingCentre(LED_SIZE, level2Area.getHeight()));
        
        
        /* Mutes */
        area.removeFromTop(largeMargin);
        auto mutesArea = area.removeFromTop(muteSize).withTrimmedLeft(controlsSideMargin).withTrimmedRight(controlsSideMargin);
        muteLabel.setBounds(mutesArea.withSizeKeepingCentre(CENTRAL_LABEL_WIDTH, LABEL_HEIGHT));
        auto mute1Area = mutesArea.removeFromLeft((area.getWidth()-CENTRAL_LABEL_WIDTH)/2);
        auto mute2Area = mutesArea.removeFromRight((area.getWidth()-CENTRAL_LABEL_WIDTH)/2);
        muteBeam1Button.setBounds(mute1Area.removeFromLeft(muteSize));
        muteBeam2Button.setBounds(mute2Area.removeFromRight(muteSize));
        

    }else{
        
        /* Landscape-only labels */
        steerBeamX1Slider.setLabelText("STEER 1");
        steerBeamX2Slider.setLabelText("STEER 2");
        widthBeam1Knob.setLabelVisible(true);
        widthBeam1Knob.setTextBoxPosition(Slider::TextEntryBoxPosition::TextBoxRight);
        panBeam1Knob.setLabelVisible(true);
        panBeam1Knob.setTextBoxPosition(Slider::TextEntryBoxPosition::TextBoxRight);
        levelBeam1Knob.setLabelVisible(true);
        levelBeam1Knob.setTextBoxPosition(Slider::TextEntryBoxPosition::TextBoxRight);
        muteBeam1Button.setLabelVisible(true);
        
        widthBeam2Knob.setLabelVisible(true);
        widthBeam2Knob.setTextBoxPosition(Slider::TextEntryBoxPosition::TextBoxRight);
        panBeam2Knob.setLabelVisible(true);
        panBeam2Knob.setTextBoxPosition(Slider::TextEntryBoxPosition::TextBoxRight);
        levelBeam2Knob.setLabelVisible(true);
        levelBeam2Knob.setTextBoxPosition(Slider::TextEntryBoxPosition::TextBoxRight);
        muteBeam2Button.setLabelVisible(true);
        
        /* Portrait-only labels */
        steerLabel.setVisible(false);
        widthLabel.setVisible(false);
        panLabel.setVisible(false);
        muteLabel.setVisible(false);
        levelLabel.setVisible(false);
        
        auto sceneArea = area.removeFromTop(area.getHeight()/2);
        
        if (isLinearArray(valueTreeSession[configIdentifier])){
            steerBeamY1Slider.setVisible(false);
            steerBeamY2Slider.setVisible(false);
        }else{
            steerBeamY1Slider.setVisible(true);
            steerBeamY2Slider.setVisible(true);
            sceneArea.removeFromLeft(SMALL_MARGIN);
            sceneArea.removeFromRight(SMALL_MARGIN);
            steerBeamY1Slider.setBounds(sceneArea.removeFromLeft(VER_SLIDER_WIDTH).withTrimmedTop(LARGE_MARGIN+SMALL_MARGIN));
            steerBeamY2Slider.setBounds(sceneArea.removeFromRight(VER_SLIDER_WIDTH).withTrimmedTop(LARGE_MARGIN+SMALL_MARGIN));
            sceneArea.removeFromLeft(SMALL_MARGIN);
            sceneArea.removeFromRight(SMALL_MARGIN);
        }
        
        /* Scene, aspect ratio 2:1 */
//        scene.setBounds(sceneArea);
        
        /* Input section */
        
        /* Input LED */
        area.removeFromBottom(BOTTOM_MARGIN);
        inputMeter.setBounds(area.removeFromBottom(LED_SIZE).withTrimmedLeft(LABEL_WIDTH).withTrimmedRight(LABEL_WIDTH));
        
        /* HPF slider */
        area.removeFromBottom(MEDIUM_MARGIN);
        auto inputSlidersArea = area.removeFromBottom(HOR_SLIDER_HEIGHT);
        hpfSlider.setBounds(inputSlidersArea.removeFromLeft(inputSlidersArea.getWidth()/2).withTrimmedRight(MEDIUM_MARGIN));
        
        /* Gain slider */
        gainSlider.setBounds(inputSlidersArea.withTrimmedRight(MEDIUM_MARGIN));
        
        /* Dynamic geometry section */
        const int availableHeight = area.getHeight();
        const int usedHeight = SMALL_MARGIN+HOR_SLIDER_HEIGHT+SMALL_MARGIN+KNOB_SIZE+SMALL_MARGIN+KNOB_SIZE;
        const int residualHeight = jmax(availableHeight - usedHeight,0);
        
        const int knobMuteTotalIncrease = residualHeight/3;
        const int horSliderTotalIncrease = residualHeight/3;
        const int marginIncrease = residualHeight - knobMuteTotalIncrease - horSliderTotalIncrease;
        
        const int smallMargin = SMALL_MARGIN + marginIncrease/3;
        
        const int knobSize = KNOB_SIZE + knobMuteTotalIncrease/2;
        const int muteSize = MUTE_SIZE + knobMuteTotalIncrease/2;
        const int horSliderHeight = HOR_SLIDER_HEIGHT + horSliderTotalIncrease;
        
        /* Beams section */
        
        auto beam1Area = area.removeFromLeft(area.getWidth()/2).withTrimmedRight(MEDIUM_MARGIN);
        auto beam2Area = area.withTrimmedLeft(MEDIUM_MARGIN);
        
        /* Beam 1 */
        
        beam1Area.removeFromTop(smallMargin);
        steerBeamX1Slider.setBounds(beam1Area.removeFromTop(horSliderHeight));
        
        beam1Area.removeFromTop(smallMargin);
        auto widthPanArea1 = beam1Area.removeFromTop(knobSize);
        widthBeam1Knob.setBounds(widthPanArea1.removeFromLeft(beam1Area.getWidth()/2));
        panBeam1Knob.setBounds(widthPanArea1);
        
        beam1Area.removeFromTop(smallMargin);
        auto levelMuteArea1 = beam1Area.removeFromTop(knobSize);
        
        muteBeam1Button.setBounds(levelMuteArea1.removeFromLeft(beam1Area.getWidth()/2-LABEL_WIDTH-2*LARGE_MARGIN+LED_SIZE));
        
        levelMuteArea1.removeFromLeft(LARGE_MARGIN);
        beam1Meter.setBounds(levelMuteArea1.removeFromLeft(LED_SIZE));
        levelMuteArea1.removeFromLeft(LARGE_MARGIN);
        
        levelBeam1Knob.setBounds(levelMuteArea1);
        
        /* Beam 2 */
        
        beam2Area.removeFromTop(smallMargin);
        steerBeamX2Slider.setBounds(beam2Area.removeFromTop(horSliderHeight));
        
        beam2Area.removeFromTop(smallMargin);
        auto widthPanArea2 = beam2Area.removeFromTop(knobSize);
        widthBeam2Knob.setBounds(widthPanArea2.removeFromLeft(beam2Area.getWidth()/2));
        panBeam2Knob.setBounds(widthPanArea2);
        
        beam2Area.removeFromTop(smallMargin);
        auto levelMuteArea2 = beam2Area.removeFromTop(knobSize);
        
        muteBeam2Button.setBounds(levelMuteArea2.removeFromLeft(beam2Area.getWidth()/2-LABEL_WIDTH-2*LARGE_MARGIN+LED_SIZE));
        
        levelMuteArea2.removeFromLeft(LARGE_MARGIN);
        beam2Meter.setBounds(levelMuteArea2.removeFromLeft(LED_SIZE));
        levelMuteArea2.removeFromLeft(LARGE_MARGIN);
        
        levelBeam2Knob.setBounds(levelMuteArea2);
        
        
    }


}

void MainComponent::layoutConfigOsc(Rectangle<int>& area){
    
    Rectangle<int> oscArea,setupArea;
    const int oscWidth = OSC_IP_LABEL_WIDTH+OSC_IP_WIDTH+OSC_PORT_LABEL_WIDTH+OSC_PORT_WIDTH+OSC_CONNECT_MARGIN_LEFT+OSC_CONNECT_WIDTH+OSC_LED_MARGIN_LEFT+LED_SIZE;
    const int configWidth = cpuLoad.getMinWidth()+MEDIUM_MARGIN+configComboBox.getMinWidth()+MEDIUM_MARGIN+frontToggle.getMinWidth();
    auto remainingWidth = area.getWidth() - (oscWidth+configWidth+SMALL_MARGIN);
    if (remainingWidth >= 0){
        auto oscControlArea = area.removeFromTop(CONTROLS_HEIGHT);
        oscControlArea.removeFromLeft(remainingWidth/3);
        setupArea = oscControlArea.removeFromLeft(configWidth);
        oscControlArea.removeFromLeft(remainingWidth/3);
        oscArea = oscControlArea.removeFromLeft(oscWidth);
    }else{
        oscArea = area.removeFromTop(CONTROLS_HEIGHT).withSizeKeepingCentre(oscWidth, CONTROLS_HEIGHT);
        area.removeFromTop(MEDIUM_MARGIN);
        setupArea = area.removeFromTop(CONTROLS_HEIGHT).withSizeKeepingCentre(configWidth, CONTROLS_HEIGHT);
    }
    area.removeFromTop(SMALL_MARGIN);
    
    
    /* OSC controls */
    oscArea.removeFromLeft(OSC_IP_LABEL_WIDTH);
    oscIp.setBounds(oscArea.removeFromLeft(OSC_IP_WIDTH));
    oscArea.removeFromLeft(OSC_PORT_LABEL_WIDTH);
    oscPort.setBounds(oscArea.removeFromLeft(OSC_PORT_WIDTH));
    oscArea.removeFromLeft(OSC_CONNECT_MARGIN_LEFT);
    oscConnectButton.setBounds(oscArea.removeFromLeft(OSC_CONNECT_WIDTH));
    oscArea.removeFromLeft(OSC_LED_MARGIN_LEFT);
    oscStatus.setBounds(oscArea.removeFromLeft(LED_SIZE));
    
    /* Set area for CPU Load */
    cpuLoad.setBounds(setupArea.removeFromLeft(cpuLoad.getMinWidth()));
    
    /* Set area for config combo */
    setupArea.removeFromLeft(MEDIUM_MARGIN);
    configComboBox.setBounds(setupArea.removeFromLeft(configComboBox.getMinWidth()));

    /* Set area for front toggle */
    setupArea.removeFromLeft(MEDIUM_MARGIN);
    frontToggle.setBounds(setupArea.removeFromLeft(frontToggle.getMinWidth()));
}

//====================================================================
/* Callbacks and listeners */

//void MainComponent::sliderValueChanged(Slider * slider){
//    if (slider == &steerBeamX1Slider){
//        steerX[0] = slider->getValue();
////        setBeamSteerX(0,slider->getValue());
////        scene.repaint();
//    }else if(slider == &steerBeamX2Slider){
//        steerX[1] = slider->getValue();
////        setBeamSteerX(1,slider->getValue());
////        scene.repaint();
//    }else if (slider == &steerBeamY1Slider){
//        steerY[0] = slider->getValue();
////        setBeamSteerY(0,slider->getValue());
////        scene.repaint();
//    }else if(slider == &steerBeamY2Slider){
//        steerY[1] = slider->getValue();
////        setBeamSteerY(1,slider->getValue());
////        scene.repaint();
//    }else if(slider == &widthBeam1Knob){
//        width[0] = slider->getValue();
////        scene.repaint();
//        if (connected) sendOscMessage("widthBeam1", width[0]);
//    }else if(slider == &widthBeam2Knob){
//        width[1] = slider->getValue();
////        scene.repaint();
//        if (connected) sendOscMessage("widthBeam2", width[1]);
//    }else if(slider == &panBeam1Knob){
//        if (connected) sendOscMessage("panBeam1", (float)panBeam1Knob.getValue());
//    }else if(slider == &panBeam2Knob){
//        if (connected) sendOscMessage("panBeam2", (float)panBeam2Knob.getValue());
//    }else if(slider == &levelBeam1Knob){
//        if (connected) sendOscMessage("levelBeam1", (float)levelBeam1Knob.getValue());
//    }else if(slider == &levelBeam2Knob){
//        if (connected) sendOscMessage("levelBeam2", (float)levelBeam2Knob.getValue());
//    }else if(slider == &hpfSlider){
//        if (connected) sendOscMessage("hpf", (float)hpfSlider.getValue());
//    }else if(slider == &gainSlider){
//        if (connected) sendOscMessage("gainMic", (float)gainSlider.getValue());
//    }
//}

void MainComponent::buttonClicked (Button* button){
    if (button == &oscConnectButton){
        if (connected){
            oscDisconnect();
        }else{
            oscConnect();
        }
    }
}

void MainComponent::comboBoxChanged(ComboBox * comboBox){
    if (comboBox == &oscIp){
        auto selectedId = oscIp.getSelectedId();
        if (selectedId > 0){
            auto selectedServer = servers[selectedId];
            oscIp.setText(selectedServer.ip,dontSendNotification);
            oscPort.setText(String(selectedServer.port),dontSendNotification);
        }
    }
}

//=====================================================================================
//OSC Methods

void MainComponent::oscConnect(){
    
    serverIp.setValue(oscIp.getText());
    serverPort.setValue(jmin(oscPort.getTextValue().toString().getIntValue(),65535));
    
    const Server srv = {serverIp.toString(), int(serverPort.getValue())};
    if (oscController.addSender(srv)){
        
        if(!oscController.startReceiver())
            return;
        
        /* Connection successful */
        oscConnectButton.setButtonText("Disconnect");
        oscIp.setEnabled(false);
        oscPort.setEnabled(false);
        connected = true;
        oscStatus.setColours(Colours::green,Colours::grey);
        
        /* Start polling */
        oscController.startPolling(srv, oscPollingFreq);

    }else{
        std::ostringstream errMsg;
        errMsg << "Error: cannot connect to " << serverIp.toString() << " on " << serverPort.toString();
        showConnectionErrorMessage (errMsg.str());
    }
}

void MainComponent::oscDisconnect(){
    if (oscController.stopPolling()){
        if (oscController.stopReceiver()){
            if (oscController.removeSender({serverIp.toString(),serverPort.getValue()})){
                oscConnectButton.setButtonText("Connect");
                oscIp.setEnabled(true);
                oscPort.setEnabled(true);
                connected = false;
                oscStatus.setColours(Colours::red,Colours::grey);
                /* Reset graphic components */
                inputMeter.reset();
                beam1Meter.reset();
                beam2Meter.reset();
//                energy.setConstant(-100);
                valueTreeSession.setProperty(cpuIdentifier, 0, nullptr);
            }else{
                showConnectionErrorMessage ("Error: could not remove sender");
            }
        }else{
            showConnectionErrorMessage ("Error: could not disconnect receiver");
        }
    }else{
        showConnectionErrorMessage ("Error: could not stop polling");
    }
}


//void MainComponent::oscMessageReceived (const OSCMessage& message){
//    
//    if (connected){
//        if ((message.size() == 1) && (message[0].isFloat32())){
//            auto val = message[0].getFloat32();
//            if (message.getAddressPattern() == "/ebeamer/steerBeamX1"){
//                steerBeamX1Slider.setValue(val,dontSendNotification);
//                steerX[0] = val;
//            }else if (message.getAddressPattern() == "/ebeamer/steerBeamX2"){
//                steerBeamX2Slider.setValue(val,dontSendNotification);
//                steerX[1] = val;
//            }else if (message.getAddressPattern() == "/ebeamer/steerBeamY1"){
//                steerBeamY1Slider.setValue(val,dontSendNotification);
//                steerY[0] = val;
//            }else if (message.getAddressPattern() == "/ebeamer/steerBeamY2"){
//                steerBeamY2Slider.setValue(val,dontSendNotification);
//                steerY[1] = val;
//            }else if (message.getAddressPattern() == "/ebeamer/widthBeam1"){
//                widthBeam1Knob.setValue(val,dontSendNotification);
//                width[0] = val;
//            }else if (message.getAddressPattern() == "/ebeamer/widthBeam2"){
//                widthBeam2Knob.setValue(val,dontSendNotification);
//                width[1] = val;
//            }else if (message.getAddressPattern() == "/ebeamer/panBeam1"){
//                panBeam1Knob.setValue(val,dontSendNotification);
//            }else if (message.getAddressPattern() == "/ebeamer/panBeam2"){
//                panBeam2Knob.setValue(val,dontSendNotification);
//            }else if (message.getAddressPattern() == "/ebeamer/levelBeam1"){
//                levelBeam1Knob.setValue(val,dontSendNotification);
//            }else if (message.getAddressPattern() == "/ebeamer/levelBeam2"){
//                levelBeam2Knob.setValue(val,dontSendNotification);
//            }else if (message.getAddressPattern() == "/ebeamer/gainMic"){
//                gainSlider.setValue(val,dontSendNotification);
//            }else if (message.getAddressPattern() == "/ebeamer/hpf"){
//                hpfSlider.setValue(val,dontSendNotification);
//            }else if (message.getAddressPattern() == "/ebeamer/cpuLoad"){
//                cpuLoad.setLoad(val);
//            }
//        }else if ((message.size() == 1) && (message[0].isInt32())){
//            auto val = message[0].getInt32();
//            if (message.getAddressPattern() == "/ebeamer/muteBeam1"){
//                muteBeam1Button.setToggleState(val,dontSendNotification);
//                mute[0] = val;
//            }else if (message.getAddressPattern() == "/ebeamer/muteBeam2"){
//                muteBeam2Button.setToggleState(val,dontSendNotification);
//                mute[1] = val;
//            }else if (message.getAddressPattern() == "/ebeamer/frontFacing"){
//                if (val != frontToggle.getToggleState()){
//                    frontToggle.setToggleState(val,dontSendNotification);
//                    frontFacing = val;
////                    scene.resized();
//                }
//            }else if (message.getAddressPattern() == "/ebeamer/config"){
//                // TODO: migrate
////                if (val != configCombo.getSelectedItemIndex()){
////                    configCombo.setSelectedItemIndex(val,dontSendNotification);
////                    config = val;
////                    resized();
////                }
//            }
//        }else if ((message.size() == 1) && (message[0].isBlob())){
//            auto val = message[0].getBlob();
//            if (message.getAddressPattern() == "/ebeamer/inMeters"){
//                std::vector<float> values((float*)val.begin(),(float*)val.end());
//                inputMeter.setValues(values);
//            } else if (message.getAddressPattern() == "/ebeamer/outMeters"){
//                beam1Meter.setValue(((float*)val.getData())[0]);
//                beam2Meter.setValue(((float*)val.getData())[1]);
//            }
//        }else if ((message.size() == 3) && (message[0].isInt32()) && (message[1].isInt32()) && (message[2].isBlob())){
//            auto nRows = message[0].getInt32();
//            auto nCols = message[1].getInt32();
//            auto val = message[2].getBlob();
//            if (message.getAddressPattern() == "/ebeamer/doaEnergy"){
//                Eigen::Map<Eigen::MatrixXf> newEnergy((float*)val.getData(),nRows,nCols);
//                energy = newEnergy;
//            }
//        }
//    }
//        
//}

void MainComponent::showConnectionErrorMessage (const String& messageText){
    juce::AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                            "OSC error",
                                            messageText,
                                            "OK");
}
//
//void MainComponent::setBeamSteerX(int idx, float newVal){
//    steerX[idx] = newVal;
//    if (idx==0){
//        steerBeamX1Slider.setValue(newVal,dontSendNotification);
//    }else{
//        steerBeamX2Slider.setValue(newVal,dontSendNotification);
//    }
//    sendOscMessage(String("steerBeamX") + String(idx+1),newVal);
//
//}
//
//void MainComponent::setBeamSteerY(int idx, float newVal){
//    steerY[idx] = newVal;
//    if (idx==0){
//        steerBeamY1Slider.setValue(newVal,dontSendNotification);
//    }else{
//        steerBeamY2Slider.setValue(newVal,dontSendNotification);
//    }
//    sendOscMessage(String("steerBeamY") + String(idx+1),newVal);
//}

//void MainComponent::sendOscMessage(const String& tag, float value){
//    auto address = "/ebeamer/" + tag;
//    if (connected){
//        OSCMessage msg(address);
//        msg.addFloat32(value);
//        sender.send(msg);
//    }
//    // Toggle status even if not connect, to show that something should have happened
//    oscStatus.toggle();
//
//}
//
//void MainComponent::sendOscMessage(const String& tag, bool value){
//    auto address = "/ebeamer/" + tag;
//    if (connected){
//        OSCMessage msg(address);
//        msg.addInt32(value);
//        sender.send(msg);
//    }
//    // Toggle status even if not connect, to show that something should have happened
//    oscStatus.toggle();
//
//}
//
//void MainComponent::sendOscMessage(const String& tag, MicConfig value){
//    auto address = "/ebeamer/" + tag;
//    if (connected){
//        OSCMessage msg(address);
//        msg.addInt32(value);
//        sender.send(msg);
//    }
//    // Toggle status even if not connect, to show that something should have happened
//    oscStatus.toggle();
//
//}

void MainComponent::valueTreePropertyChanged (ValueTree& vt,
                               const Identifier& property){
    if (property == serversIdentifier){
        oscIp.clear();
        servers.clear();
        const Time now = Time::getCurrentTime();
        for (auto srvArr : *vt.getProperty(property).getArray()){
            String ip = srvArr[0].toString();
            int32 port = int(srvArr[1]);
            int32 id = int(srvArr[2]);
            servers[id] = Server({ip,port,now});
            oscIp.addItem(servers[id].toString(), id);
        }
    }
}
