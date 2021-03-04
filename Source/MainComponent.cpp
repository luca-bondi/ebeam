#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    //==============================================================================
    setSize(GUI_WIDTH, GUI_HEIGHT);
    
    //==============================================================================
    //    TODO
    //    scene.setCallback(&p);
    //    scene.setBeamColors(beamColours);
    //    addAndMakeVisible(scene);
    
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
    steerBeamX1Slider.setPopupMenuEnabled(true);
    //    steerBeamX1Slider.setCallback(&processor, "steerBeamX1");
    addAndMakeVisible(steerBeamX1Slider);
    
    steerBeamX2Slider.setSliderStyle(Slider::LinearHorizontal);
    steerBeamX2Slider.setTextBoxStyle(Slider::TextBoxRight, false, LABEL_WIDTH, LABEL_HEIGHT);
    steerBeamX2Slider.setColour(Slider::thumbColourId, beamColours[1]);
    steerBeamX2Slider.setPopupMenuEnabled(true);
    //    steerBeamX2Slider.setCallback(&processor, "steerBeamX2");
    addAndMakeVisible(steerBeamX2Slider);
    
    steerBeamY1Slider.setSliderStyle(Slider::LinearVertical);
    steerBeamY1Slider.setTextBoxStyle(Slider::TextBoxAbove, false, LABEL_WIDTH, LABEL_HEIGHT);
    steerBeamY1Slider.setColour(Slider::thumbColourId, beamColours[0]);
    steerBeamY1Slider.setPopupMenuEnabled(true);
    //    steerBeamY1Slider.setCallback(&processor, "steerBeamY1");
    addAndMakeVisible(steerBeamY1Slider);
    
    steerBeamY2Slider.setSliderStyle(Slider::LinearVertical);
    steerBeamY2Slider.setTextBoxStyle(Slider::TextBoxAbove, false, LABEL_WIDTH, LABEL_HEIGHT);
    steerBeamY2Slider.setColour(Slider::thumbColourId, beamColours[1]);
    steerBeamY2Slider.setPopupMenuEnabled(true);
    //    steerBeamY2Slider.setCallback(&processor, "steerBeamY2");
    addAndMakeVisible(steerBeamY2Slider);
    
    //    steerBeamX1SliderAttachment.reset(new SliderAttachment(valueTreeState, "steerBeamX1", steerBeamX1Slider));
    //    steerBeamX2SliderAttachment.reset(new SliderAttachment(valueTreeState, "steerBeamX2", steerBeamX2Slider));
    //    steerBeamY1SliderAttachment.reset(new SliderAttachment(valueTreeState, "steerBeamY1", steerBeamY1Slider));
    //    steerBeamY2SliderAttachment.reset(new SliderAttachment(valueTreeState, "steerBeamY2", steerBeamY2Slider));
    
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
    
    auto sceneArea = area.removeFromTop(SCENE_HEIGHT);
    
    if (isLinearArray(config)){
        steerBeamY1Slider.setVisible(false);
        steerBeamY2Slider.setVisible(false);
        sceneArea.removeFromRight((area.getWidth() - SCENE_WIDTH) / 2);
        sceneArea.removeFromLeft((area.getWidth() - SCENE_WIDTH) / 2);
//        scene.setBounds(sceneArea);
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
//        scene.setBounds(sceneArea);
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
