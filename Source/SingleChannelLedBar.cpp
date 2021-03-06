/*
  ==============================================================================

    SingleChannelLedBar.cpp
    Created: 3 Mar 2021 8:17:46pm
    Author:  Luca Bondi

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SingleChannelLedBar.h"
#include "ebeamerDefs.h"

//==============================================================================
SingleChannelLedBar::SingleChannelLedBar(size_t numLeds, bool isHorizontal) {
    jassert(numLeds > 4);
    
    this->isHorizontal = isHorizontal;
    
    const float ledStep = 3; //dB
    
    leds.clear();
    th.clear();
    for (auto ledIdx = 0; ledIdx < numLeds; ++ledIdx) {
        leds.push_back(std::make_unique<RoundLed>());
        
        auto ledThDb = ledIdx == (numLeds - 1) ? RED_LT : -((numLeds - 1 - ledIdx) * ledStep);
        th.push_back(ledThDb);
        leds[ledIdx]->setColour(dbToColour(-100, ledThDb));
        
        addAndMakeVisible(leds[ledIdx].get());
    }
}

//void SingleChannelLedBar::setCallback(MeterDecay::Callback *pr, int metId, int ch) {
//    provider = pr;
//    meterId = metId;
//    channel = ch;
//}

void SingleChannelLedBar::paint(Graphics &) {
    
}

void SingleChannelLedBar::resized() {
    
    Rectangle<float> area = getLocalBounds().toFloat();
    auto num = leds.size();
    float step = isHorizontal ? area.getWidth() / num : area.getHeight() / num;
    for (auto ledIdx = 0; ledIdx < num; ++ledIdx) {
        Rectangle<float> ledArea = isHorizontal ? area.removeFromLeft(step) : area.removeFromBottom(step);
        leds[ledIdx]->setBounds(ledArea.toNearestInt());
    }
    
}

void SingleChannelLedBar::timerCallback() {
//    if (provider == nullptr)
//        return;
//
//    auto valueDb = Decibels::gainToDecibels(provider->getMeterValue(meterId, channel));
    float valueDb = 0;
    for (auto ledIdx = 0; ledIdx < leds.size(); ++ledIdx)
        leds[ledIdx]->setColour(dbToColour(valueDb, th[ledIdx]));
    
}

Colour SingleChannelLedBar::dbToColour(float valDb, float thDb) {
    const bool active = valDb >= thDb;
    Colour col;
    if (thDb >= RED_LT) {
        col = active ? Colours::red : Colours::darkred;
    } else if (thDb >= ORANGE_LT) {
        col = active ? Colours::orange : Colours::darkorange.darker();
    } else if (thDb >= YELLOW_LT) {
        col = active ? Colours::yellow : Colours::darkgoldenrod;
    } else {
        col = active ? Colours::lightgreen : Colours::darkgreen;
    }
    return col;
}
