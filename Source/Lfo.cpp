/*
  ==============================================================================

    Lfo.cpp
    Created: 24 Nov 2016 1:53:39am
    Author:  WangRex

  ==============================================================================
*/

#include "Lfo.h"

StkFloat LFO::tick() {
    if (source != 0) {
        sinOsc.setFrequency(freq.getNextValue());
        sawOsc.setFrequency(freq.getNextValue());
        sqrOsc.setFrequency(freq.getNextValue());
        triOsc.setFrequency(freq.getNextValue());
        rndOsc.setFrequency(freq.getNextValue());
        return switchSource();
    } else {
        return 0;
    }
}
