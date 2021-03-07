/*
  ==============================================================================

    CpuLoadComp.cpp
    Created: 3 Mar 2021 8:15:30pm
    Author:  Luca Bondi

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CpuLoadComp.h"

//==============================================================================
CpuLoadComp::CpuLoadComp() {

    text.setText("0 %", NotificationType::dontSendNotification);
    label.setText("CPU", NotificationType::dontSendNotification);
    label.setJustificationType(Justification::left);
    label.attachToComponent(&text, true);
    addAndMakeVisible(text);
}

CpuLoadComp::~CpuLoadComp() {
}

void CpuLoadComp::paint(Graphics &g) {
}

void CpuLoadComp::resized() {
    auto area = getLocalBounds();
    area.removeFromLeft(labelWidth);
    text.setBounds(area);
}

void CpuLoadComp::setLoad(float load) {
    text.setText(String(int(load * 100)) + "%", NotificationType::dontSendNotification);
}
