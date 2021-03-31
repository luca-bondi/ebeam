#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    
    appVersion = JUCEApplication::getInstance()->getApplicationVersion();
    
    //==============================================================================
    /* ValueTree */
    statusFile = File::getSpecialLocation(File::userDocumentsDirectory).getChildFile("ebeamer-controller.xml");
    valueTree = ValueTree("ebeamer-controller");
    valueTreeFile.init(valueTree, statusFile, true);
    
    if (!valueTreeFile.load()){
        /** Initialize value tree if not loaded */
        valueTree.setProperty(serverIpIdentifier, "", nullptr);
        valueTree.setProperty(serverPortIdentifier, 9001, nullptr);
        valueTreeFile.save();
    }
    
    serverIp = valueTree.getPropertyAsValue(serverIpIdentifier,nullptr);
    serverPort = valueTree.getPropertyAsValue(serverPortIdentifier,nullptr);
    
    //==============================================================================
    /* Initialize parameters */
    // TODO: use ValueTree
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
    
    steerBeam1Label.setJustificationType(Justification::left);
    steerBeam1Label.attachToComponent(&steerBeamX1Slider, true);
    addAndMakeVisible(steerBeam1Label);
    
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
    widthLabel1.setText("WIDTH", NotificationType::dontSendNotification);
    widthLabel2.setText("WIDTH", NotificationType::dontSendNotification);
    widthLabel.setJustificationType(Justification::centred);
    widthLabel1.setJustificationType(Justification::left);
    widthLabel2.setJustificationType(Justification::left);
    widthLabel1.attachToComponent(&widthBeam1Knob, true);
    widthLabel2.attachToComponent(&widthBeam2Knob, true);
    addAndMakeVisible(widthLabel);
    addAndMakeVisible(widthLabel1);
    addAndMakeVisible(widthLabel2);
    
    widthBeam1Knob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    widthBeam1Knob.setTextBoxStyle(Slider::TextBoxRight, false, LABEL_WIDTH, LABEL_HEIGHT);
    widthBeam1Knob.setColour(Slider::thumbColourId, beamColours[0]);
    widthBeam1Knob.setRange(0,1,0.01);
    widthBeam1Knob.addListener(this);
    addAndMakeVisible(widthBeam1Knob);
    
    widthBeam2Knob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    widthBeam2Knob.setColour(Slider::thumbColourId, beamColours[1]);
    widthBeam2Knob.setRange(0,1,0.01);
    widthBeam2Knob.addListener(this);
    addAndMakeVisible(widthBeam2Knob);
    
    
    //==============================================================================
    panLabel.setText("PAN", NotificationType::dontSendNotification);
    panLabel1.setText("PAN", NotificationType::dontSendNotification);
    panLabel2.setText("PAN", NotificationType::dontSendNotification);
    panLabel.setJustificationType(Justification::centred);
    panLabel1.setJustificationType(Justification::left);
    panLabel2.setJustificationType(Justification::left);
    panLabel1.attachToComponent(&panBeam1Knob, true);
    panLabel2.attachToComponent(&panBeam2Knob, true);
    addAndMakeVisible(panLabel);
    addAndMakeVisible(panLabel1);
    addAndMakeVisible(panLabel2);
    
    panBeam1Knob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    panBeam1Knob.setTextBoxStyle(Slider::TextBoxRight, false, LABEL_WIDTH, LABEL_HEIGHT);
    panBeam1Knob.setColour(Slider::thumbColourId, beamColours[0]);
    panBeam1Knob.setRange(-1,1,0.01);
    panBeam1Knob.addListener(this);
    addAndMakeVisible(panBeam1Knob);
    
    panBeam2Knob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    panBeam2Knob.setColour(Slider::thumbColourId, beamColours[1]);
    panBeam2Knob.setRange(-1,1,0.01);
    panBeam2Knob.addListener(this);
    addAndMakeVisible(panBeam2Knob);
    
    //==============================================================================
    levelLabel.setText("LEVEL", NotificationType::dontSendNotification);
    levelLabel1.setText("LEVEL", NotificationType::dontSendNotification);
    levelLabel2.setText("LEVEL", NotificationType::dontSendNotification);
    levelLabel.setJustificationType(Justification::centred);
    levelLabel1.setJustificationType(Justification::left);
    levelLabel2.setJustificationType(Justification::left);
    levelLabel1.attachToComponent(&levelBeam1Knob, true);
    levelLabel2.attachToComponent(&levelBeam2Knob, true);
    addAndMakeVisible(levelLabel);
    addAndMakeVisible(levelLabel1);
    addAndMakeVisible(levelLabel2);
    
    levelBeam1Knob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    levelBeam1Knob.setTextBoxStyle(Slider::TextBoxRight, false, LABEL_WIDTH, LABEL_HEIGHT);
    levelBeam1Knob.setColour(Slider::thumbColourId, beamColours[0]);
    levelBeam1Knob.setRange(-10,10,0.1);
    levelBeam1Knob.addListener(this);
    addAndMakeVisible(levelBeam1Knob);
    
    levelBeam2Knob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    levelBeam2Knob.setColour(Slider::thumbColourId, beamColours[1]);
    levelBeam2Knob.setRange(-10,10,0.1);
    levelBeam2Knob.addListener(this);
    addAndMakeVisible(levelBeam2Knob);
    
    
    //==============================================================================
    muteLabel.setText("MUTE", NotificationType::dontSendNotification);
    muteLabel1.setText("MUTE", NotificationType::dontSendNotification);
    muteLabel2.setText("MUTE", NotificationType::dontSendNotification);
    muteLabel.setJustificationType(Justification::centred);
    muteLabel1.setJustificationType(Justification::centred);
    muteLabel2.setJustificationType(Justification::centred);
    addAndMakeVisible(muteLabel);
    addAndMakeVisible(muteLabel1);
    addAndMakeVisible(muteLabel2);
    
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
    
    /* Set this as a listener for OSC messages */
    receiver.addListener(this);
    
    /* Broadcast receiver */
    broadcastReceiver.addListener(this);
    broadcastReceiver.connect(OSC_BORADCAST_PORT);
    
    /* Set polling timer to fetch updates from VST */
    startTimerHz(OSC_POLLING_FREQ);
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
        widthLabel1.setVisible(false);
        panLabel1.setVisible(false);
        levelLabel1.setVisible(false);
        muteLabel1.setVisible(false);
        widthLabel2.setVisible(false);
        panLabel2.setVisible(false);
        levelLabel2.setVisible(false);
        muteLabel2.setVisible(false);
        
        /* Portrait-only labels */
        steerLabel.setVisible(true);
        widthLabel.setVisible(true);
        panLabel.setVisible(true);
        muteLabel.setVisible(true);
        levelLabel.setVisible(true);
        
        /* Scene, aspect ratio 2:1 */
        auto sceneArea = area.removeFromTop(area.getWidth()/2);
        
        if (isLinearArray(static_cast<MicConfig>((int)config))){
            steerBeamY1Slider.setVisible(false);
            steerBeamY2Slider.setVisible(false);
            scene.setBounds(sceneArea);
        }else{
            steerBeamY1Slider.setVisible(true);
            steerBeamY2Slider.setVisible(true);
            sceneArea.removeFromLeft(SMALL_MARGIN);
            sceneArea.removeFromRight(SMALL_MARGIN);
            steerBeamY1Slider.setBounds(sceneArea.removeFromLeft(VER_SLIDER_WIDTH).withTrimmedTop(LARGE_MARGIN+SMALL_MARGIN));
            steerBeamY2Slider.setBounds(sceneArea.removeFromRight(VER_SLIDER_WIDTH).withTrimmedTop(LARGE_MARGIN+SMALL_MARGIN));
            sceneArea.removeFromLeft(SMALL_MARGIN);
            sceneArea.removeFromRight(SMALL_MARGIN);
            scene.setBounds(sceneArea);
        }
        
        
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
        
        /* Allocate elements from top to bottom */
        
        /* Horizontal steering */
        steerLabel.setVisible(true);
        steerBeam1Label.setText("1", NotificationType::dontSendNotification);
        steerBeam2Label.setText("2", NotificationType::dontSendNotification);
        
        area.removeFromTop(mediumMargin);
        steerBeamX1Slider.setBounds(area.removeFromTop(horSliderHeight).withTrimmedLeft(SMALL_LABEL_WIDTH));
        area.removeFromTop(smallMargin);
        steerLabel.setBounds(area.removeFromTop(LABEL_HEIGHT));
        area.removeFromTop(smallMargin);
        steerBeamX2Slider.setBounds(area.removeFromTop(horSliderHeight).withTrimmedLeft(SMALL_LABEL_WIDTH));
        
        /* Width knobs */
        area.removeFromTop(mediumMargin);
        auto widthKnobsArea = area.removeFromTop(knobSize);
        widthBeam1Knob.setBounds(widthKnobsArea.removeFromLeft((area.getWidth()-CENTRAL_LABEL_WIDTH)/2));
        widthBeam2Knob.setTextBoxStyle(Slider::TextBoxLeft, false, LABEL_WIDTH, LABEL_HEIGHT);
        widthBeam2Knob.setBounds(widthKnobsArea.removeFromRight((area.getWidth()-CENTRAL_LABEL_WIDTH)/2));
        widthLabel.setBounds(widthKnobsArea);

        /* Pan knobs */
        area.removeFromTop(mediumMargin);
        auto panKnobsArea = area.removeFromTop(knobSize);
        panBeam1Knob.setBounds(panKnobsArea.removeFromLeft((area.getWidth()-CENTRAL_LABEL_WIDTH)/2));
        panBeam2Knob.setTextBoxStyle(Slider::TextBoxLeft, false, LABEL_WIDTH, LABEL_HEIGHT);
        panBeam2Knob.setBounds(panKnobsArea.removeFromRight((area.getWidth()-CENTRAL_LABEL_WIDTH)/2));
        panLabel.setBounds(panKnobsArea);
        
        /* Levels and meters */
        area.removeFromTop(mediumMargin);
        auto levelsArea = area.removeFromTop(knobSize);
        auto level1Area = levelsArea.removeFromLeft((area.getWidth()-CENTRAL_LABEL_WIDTH)/2);
        auto level2Area = levelsArea.removeFromRight((area.getWidth()-CENTRAL_LABEL_WIDTH)/2);
        levelBeam1Knob.setBounds(level1Area);
        levelBeam2Knob.setTextBoxStyle(Slider::TextBoxLeft, false, LABEL_WIDTH, LABEL_HEIGHT);
        levelBeam2Knob.setBounds(level2Area);
        level1Area.removeFromRight(LABEL_WIDTH+2*LARGE_MARGIN);
        level2Area.removeFromLeft(LABEL_WIDTH+2*LARGE_MARGIN);
        beam1Meter.setBounds(level1Area.removeFromRight(LED_SIZE));
        beam2Meter.setBounds(level2Area.removeFromLeft(LED_SIZE));
        levelLabel.setBounds(levelsArea);
        
        /* Mutes */
        area.removeFromTop(largeMargin);
        auto mutesArea = area.removeFromTop(muteSize);
        muteBeam1Button.setBounds(mutesArea.removeFromLeft((area.getWidth()-CENTRAL_LABEL_WIDTH)/2).withTrimmedRight(LABEL_WIDTH).withSizeKeepingCentre(muteSize, muteSize));
        muteBeam2Button.setBounds(mutesArea.removeFromRight((area.getWidth()-CENTRAL_LABEL_WIDTH)/2).withTrimmedLeft(LABEL_WIDTH).withSizeKeepingCentre(muteSize, muteSize));
        muteLabel.setBounds(mutesArea);
        
        /* HPF slider */
        area.removeFromTop(largeMargin);
        hpfSlider.setBounds(area.removeFromTop(horSliderHeight).withTrimmedLeft(LABEL_WIDTH));

        /* Input LED */
        inputMeter.setBounds(area.removeFromTop(LED_SIZE).withTrimmedLeft(LABEL_WIDTH).withTrimmedRight(LABEL_WIDTH));
        
        /* Gain slider */
        gainSlider.setBounds(area.removeFromTop(horSliderHeight).withTrimmedLeft(LABEL_WIDTH));
        

    }else{
        
        /* Landscape-only labels */
        widthLabel1.setVisible(true);
        panLabel1.setVisible(true);
        levelLabel1.setVisible(true);
        muteLabel1.setVisible(true);
        widthLabel2.setVisible(true);
        panLabel2.setVisible(true);
        levelLabel2.setVisible(true);
        muteLabel2.setVisible(true);
        
        /* Portrait-only labels */
        steerLabel.setVisible(false);
        widthLabel.setVisible(false);
        panLabel.setVisible(false);
        muteLabel.setVisible(false);
        levelLabel.setVisible(false);
        
        auto sceneArea = area.removeFromTop(area.getHeight()/2);
        
        if (isLinearArray(static_cast<MicConfig>((int)config))){
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
        scene.setBounds(sceneArea);
        
        /* Input section */
        
        /* Input LED */
        area.removeFromBottom(BOTTOM_MARGIN);
        inputMeter.setBounds(area.removeFromBottom(LED_SIZE).withTrimmedLeft(LABEL_WIDTH).withTrimmedRight(LABEL_WIDTH));
        
        /* HPF slider */
        area.removeFromBottom(MEDIUM_MARGIN);
        auto inputSlidersArea = area.removeFromBottom(HOR_SLIDER_HEIGHT);
        hpfSlider.setBounds(inputSlidersArea.removeFromLeft(inputSlidersArea.getWidth()/2).withTrimmedLeft(LABEL_WIDTH).withTrimmedRight(MEDIUM_MARGIN));
        
        /* Gain slider */
        gainSlider.setBounds(inputSlidersArea.withTrimmedLeft(LABEL_WIDTH).withTrimmedRight(MEDIUM_MARGIN));
        
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
        steerBeam1Label.setText("STEER 1", NotificationType::dontSendNotification);
        steerBeamX1Slider.setBounds(beam1Area.removeFromTop(horSliderHeight).withTrimmedLeft(LABEL_WIDTH));
        
        beam1Area.removeFromTop(smallMargin);
        auto widthPanArea1 = beam1Area.removeFromTop(knobSize);
        widthBeam1Knob.setBounds(widthPanArea1.removeFromLeft(beam1Area.getWidth()/2).withTrimmedLeft(LABEL_WIDTH));
        panBeam1Knob.setBounds(widthPanArea1.withTrimmedLeft(LABEL_WIDTH));
        
        beam1Area.removeFromTop(smallMargin);
        auto levelMuteArea1 = beam1Area.removeFromTop(knobSize);
        muteLabel1.setBounds(levelMuteArea1.removeFromLeft(LABEL_WIDTH));
        
        muteBeam1Button.setBounds(levelMuteArea1.removeFromLeft(beam1Area.getWidth()/2-LABEL_WIDTH-2*LARGE_MARGIN+LED_SIZE).withSizeKeepingCentre(muteSize, muteSize));
        
        levelMuteArea1.removeFromLeft(LARGE_MARGIN);
        beam1Meter.setBounds(levelMuteArea1.removeFromLeft(LED_SIZE));
        levelMuteArea1.removeFromLeft(LARGE_MARGIN);
        
        levelBeam1Knob.setBounds(levelMuteArea1.withTrimmedLeft(LABEL_WIDTH));
        
        /* Beam 2 */
        
        beam2Area.removeFromTop(smallMargin);
        steerBeam2Label.setText("STEER 2", NotificationType::dontSendNotification);
        steerBeamX2Slider.setBounds(beam2Area.removeFromTop(horSliderHeight).withTrimmedLeft(LABEL_WIDTH));
        
        beam2Area.removeFromTop(smallMargin);
        auto widthPanArea2 = beam2Area.removeFromTop(knobSize);
        widthBeam2Knob.setTextBoxStyle(Slider::TextBoxRight, false, LABEL_WIDTH, LABEL_HEIGHT);
        widthBeam2Knob.setBounds(widthPanArea2.removeFromLeft(beam2Area.getWidth()/2).withTrimmedLeft(LABEL_WIDTH));
        panBeam2Knob.setTextBoxStyle(Slider::TextBoxRight, false, LABEL_WIDTH, LABEL_HEIGHT);
        panBeam2Knob.setBounds(widthPanArea2.withTrimmedLeft(LABEL_WIDTH));
        
        beam2Area.removeFromTop(smallMargin);
        auto levelMuteArea2 = beam2Area.removeFromTop(knobSize);
        muteLabel2.setBounds(levelMuteArea2.removeFromLeft(LABEL_WIDTH));
        
        muteBeam2Button.setBounds(levelMuteArea2.removeFromLeft(beam2Area.getWidth()/2-LABEL_WIDTH-2*LARGE_MARGIN+LED_SIZE).withSizeKeepingCentre(muteSize, muteSize));
        
        levelMuteArea2.removeFromLeft(LARGE_MARGIN);
        beam2Meter.setBounds(levelMuteArea2.removeFromLeft(LED_SIZE));
        levelMuteArea2.removeFromLeft(LARGE_MARGIN);
        
        levelBeam2Knob.setTextBoxStyle(Slider::TextBoxRight, false, LABEL_WIDTH, LABEL_HEIGHT);
        levelBeam2Knob.setBounds(levelMuteArea2.withTrimmedLeft(LABEL_WIDTH));
        
        
    }


}

void MainComponent::layoutConfigOsc(Rectangle<int>& area){
    
    Rectangle<int> oscArea,setupArea;
    const int oscWidth = OSC_IP_LABEL_WIDTH+OSC_IP_WIDTH+OSC_PORT_LABEL_WIDTH+OSC_PORT_WIDTH+OSC_CONNECT_MARGIN_LEFT+OSC_CONNECT_WIDTH+OSC_LED_MARGIN_LEFT+LED_SIZE;
    const int configWidth = CPULOAD_WIDTH+CONFIG_COMBO_LABEL_WIDTH+CONFIG_COMBO_WIDTH+FRONT_TOGGLE_LABEL_WIDTH+FRONT_TOGGLE_WIDTH;
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
    cpuLoad.setBounds(setupArea.removeFromLeft(CPULOAD_WIDTH));
    
    /* Set area for config combo */
    setupArea.removeFromLeft(CONFIG_COMBO_LABEL_WIDTH);
    configCombo.setBounds(setupArea.removeFromLeft(CONFIG_COMBO_WIDTH));

    /* Set area for front toggle */
    setupArea.removeFromLeft(FRONT_TOGGLE_LABEL_WIDTH);
    frontToggle.setBounds(setupArea.removeFromLeft(FRONT_TOGGLE_WIDTH));
}

//====================================================================
/* Callbacks and listeners */

void MainComponent::sliderValueChanged(Slider * slider){
    if (slider == &steerBeamX1Slider){
        steerX[0] = slider->getValue();
        setBeamSteerX(0,slider->getValue());
        scene.repaint();
    }else if(slider == &steerBeamX2Slider){
        steerX[1] = slider->getValue();
        setBeamSteerX(1,slider->getValue());
        scene.repaint();
    }else if (slider == &steerBeamY1Slider){
        steerY[0] = slider->getValue();
        setBeamSteerY(0,slider->getValue());
        scene.repaint();
    }else if(slider == &steerBeamY2Slider){
        steerY[1] = slider->getValue();
        setBeamSteerY(1,slider->getValue());
        scene.repaint();
    }else if(slider == &widthBeam1Knob){
        width[0] = slider->getValue();
        scene.repaint();
        if (connected) sendOscMessage("widthBeam1", width[0]);
    }else if(slider == &widthBeam2Knob){
        width[1] = slider->getValue();
        scene.repaint();
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
    }else if (comboBox == &oscIp){
        auto selectedId = oscIp.getSelectedId();
        if (selectedId > 0){
            auto selectedServer = serversComboMap[selectedId];
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
    
    if (sender.connectToSocket(socket,serverIp.toString(),serverPort.getValue())){
        int localPort = 9002;
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
        IPAddress serverIpAddr = IPAddress(serverIp.toString());
        auto ipArray = IPAddress::getAllAddresses();
        int mostLikelyIdx = 0;
        int mostLikelyScore = 0;
        for (auto idx = 0; idx < ipArray.size(); idx++){
            auto ip = ipArray[idx];
            int score = 0;
            while (ip.address[score] == serverIpAddr.address[score])
                score ++;
            if (score > mostLikelyScore){
                mostLikelyScore = score;
                mostLikelyIdx = idx;
            }
        }
        localIp = ipArray[mostLikelyIdx];
        
        /* Reset auto disconnect timer */
        lastOscRequestSent = Time::getCurrentTime();
        lastOscMsgReceived = Time::getCurrentTime();
        
    }else{
        std::ostringstream errMsg;
        errMsg << "Error: cannot connect to " << serverIp.toString() << " on " << serverPort.toString();
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
            /* Reset graphic components */
            inputMeter.reset();
            beam1Meter.reset();
            beam2Meter.reset();
            energy.setConstant(-100);
            cpuLoad.setLoad(0);
        }else{
            showConnectionErrorMessage ("Error: could not disconnect receiver");
        }
    }else{
        showConnectionErrorMessage ("Error: could not disconnect sender");
    }
}


void MainComponent::oscMessageReceived (const OSCMessage& message){
    
    if (connected){
        lastOscMsgReceived = Time::getCurrentTime();
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
                    configCombo.setSelectedItemIndex(val,dontSendNotification);
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
        
    if ((message.size()==2) && (message[0].isString()) && (message[1].isInt32()) && message.getAddressPattern() == "/ebeamer/announce"){
        ServerSpec server = {message[0].getString(),message[1].getInt32()};
        auto timestamp = Time::getCurrentTime();
        {
            GenericScopedLock<SpinLock> lock(serversMapLock);
            if (serversMap.count(server)==0){
                lastServerId += 1;
                oscIp.addItem(server.toString(), lastServerId);
                serversComboMap[lastServerId] = server;
            }
            /** Update timestamp */
            serversMap[server] = timestamp;
        }
    }
}

void MainComponent::timerCallback(){
    if (connected){
        if ((lastOscRequestSent - lastOscMsgReceived).inSeconds() > OSC_TIMEOUT){
            oscDisconnect();
            return;
        }
        OSCMessage msg("/ebeamer/get");
        msg.addString(localIp.toString());
        msg.addInt32(socket.getBoundPort());
        sender.send(msg);
        oscStatus.toggle();
        lastOscRequestSent = Time::getCurrentTime();
    }
    
    {
        GenericScopedLock<SpinLock> lock(serversMapLock);
        /* Check expired announces */
        auto now = Time::getCurrentTime();
        std::list<ServerSpec> toBeRemoved;
        for (auto server : serversMap)
            if ((now - server.second).inSeconds() > OSC_TIMEOUT)
                toBeRemoved.push_back(server.first);
        if (toBeRemoved.size()){
            oscIp.clear();
            for (auto server : toBeRemoved){
                serversMap.erase(server);
            }
            for (auto server : serversMap){
                lastServerId += 1;
                oscIp.addItem(server.first.toString(), lastServerId);
                serversComboMap[lastServerId] = server.first;
            }
        }
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
