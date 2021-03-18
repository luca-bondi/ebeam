/*
  ==============================================================================

    ebeamerDefs.h
    Created: 3 Mar 2021 7:59:11pm
    Author:  Luca Bondi

  ==============================================================================
*/

#pragma once

#define NUM_BEAMS 2
#define NUM_DOAX 25
#define NUM_DOAY 9

#define GUI_WIDTH 540
#define GUI_HEIGHT 860

#define ULA_TILE_ROW_COUNT 7

#define SMALL_MARGIN 5
#define MEDIUM_MARGIN 10
#define LARGE_MARGIN 15

/** High of credits text plus a bit */
#define BOTTOM_MARGIN 16

#define HOR_SLIDER_HEIGHT 25
#define VER_SLIDER_WIDTH 70

#define LABEL_WIDTH 70
#define LABEL_HEIGHT 20

#define CENTRAL_LABEL_WIDTH 120
#define SMALL_LABEL_WIDTH 25

#define KNOB_SIZE 80
#define MUTE_SIZE 40

#define LED_SIZE 5

#define CPULOAD_WIDTH 120
#define CPULOAD_UPDATE_FREQ 10 //Hz

#define OSC_IP_LABEL_WIDTH 30
#define OSC_IP_WIDTH 100

#define OSC_PORT_LABEL_WIDTH 60
#define OSC_PORT_WIDTH 50

#define OSC_CONNECT_WIDTH 100
#define OSC_CONNECT_MARGIN_LEFT 15

#define OSC_LED_MARGIN_LEFT 10

#define FRONT_TOGGLE_LABEL_WIDTH 80
#define FRONT_TOGGLE_WIDTH 25

#define CONFIG_COMBO_LABEL_WIDTH 25
#define CONFIG_COMBO_WIDTH 105

#define CONTROLS_HEIGHT 20

/* Colors */

#define RED_LT -0.5f //dB
#define ORANGE_LT -3.0f //dB
#define YELLOW_LT -6.0f //dB
#define GREEN_LT -18.0f //dB

#include <JuceHeader.h>

/** Available eSticks configurations type */
typedef enum {
    ULA_1ESTICK,
    ULA_2ESTICK,
    ULA_3ESTICK,
    ULA_4ESTICK,
    URA_2ESTICK,
    URA_3ESTICK,
    URA_4ESTICK,
    URA_2x2ESTICK,
} MicConfig;

/** Available eSticks configurations labels */
const StringArray micConfigLabels({
                                          "Single",
                                          "Horiz 2",
                                          "Horiz 3",
                                          "Horiz 4",
                                          "Stack 2",
                                          "Stack 3",
                                          "Stack 4",
                                          "Stack 2x2",
                                  });

bool isLinearArray(MicConfig m);

