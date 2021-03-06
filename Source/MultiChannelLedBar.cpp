/*
  ==============================================================================

    MultiChannelLedBar.cpp
    Created: 3 Mar 2021 8:17:37pm
    Author:  Luca Bondi

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MultiChannelLedBar.h"
#include "ebeamerDefs.h"

//==============================================================================
MultiChannelLedBar::MultiChannelLedBar(){
    //TOOD: real implementation
    makeLayout();
}

void MultiChannelLedBar::makeLayout() {
    removeAllChildren();
    leds.clear();
//    if (callback == nullptr) {
//        return;
//    }
//    callback->getMeterValues(values, meterId);
    //TODO: real implementation
    values.resize(16);
    auto num = values.size();
    for (auto ledIdx = 0; ledIdx < num; ++ledIdx) {
        leds.push_back(std::make_unique<RoundLed>());
        leds[ledIdx]->setColour(Colours::grey);
        addAndMakeVisible(leds[ledIdx].get());
    }
    resized();
}

void MultiChannelLedBar::paint(Graphics &) {
    
}

void MultiChannelLedBar::resized() {
    
//    if (callback == nullptr) {
//        return;
//    }
//    callback->getMeterValues(values, meterId);
    //TODO: real implementation
    values.resize(16);
    auto num = values.size();
    Rectangle<int> area = getLocalBounds();
    
    float step = isHorizontal ? floor(area.getWidth() / num) : floor(area.getHeight() / num);
    float otherDim = isHorizontal ? area.getHeight() : area.getWidth();
    otherDim = jmin(otherDim, step - 1);
    
    const auto areaCtr = area.getCentre();
    
    // Re-center the area
    if (isHorizontal) {
        area.setWidth(step * num);
        area.setHeight(otherDim);
    } else {
        area.setHeight(step * num);
        area.setWidth(otherDim);
    }
    area.setCentre(areaCtr);
    
    for (auto ledIdx = 0; ledIdx < num; ++ledIdx) {
        Rectangle<int> ledArea = isHorizontal ? area.removeFromLeft(step) : area.removeFromTop(step);
        leds[ledIdx]->setBounds(ledArea);
    }
    
}

Colour MultiChannelLedBar::dbToColor(float valDb){
    Colour col;
    if (valDb > RED_LT) {
        col = Colours::red;
    } else if (valDb > ORANGE_LT) {
        col = Colours::orange;
    } else if (valDb > YELLOW_LT) {
        col = Colours::yellow;
    } else if (valDb > GREEN_LT) {
        col = Colours::lightgreen;
    } else {
        col = Colours::darkgreen;
    }
    return col;
}

void MultiChannelLedBar::timerCallback() {
    
//    if (callback == nullptr)
//        return;
//
//    callback->getMeterValues(values, meterId);
    //TODO: real implementation
    values.resize(16);
    if (values.size() != leds.size())
        makeLayout();
    
    for (auto ledIdx = 0; ledIdx < leds.size(); ++ledIdx)
        leds[ledIdx]->setColour(dbToColor(Decibels::gainToDecibels(values.at(ledIdx))));
    
}

//void MultiChannelLedBar::setCallback(MeterDecay::Callback *cb, int metId) {
//    callback = cb;
//    meterId = metId;
//    callback->getMeterValues(values, meterId);
//    if (values.size() > 0) {
//        makeLayout();
//    }
//}
