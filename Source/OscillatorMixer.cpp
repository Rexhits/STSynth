/*
  ==============================================================================

    Synth.cpp
    Created: 18 Nov 2016 4:40:34pm
    Author:  WangRex

  ==============================================================================
*/

#include "OscillatorMixer.h"
OscillatorMixer::OscillatorMixer() {
    setFrequency(440);
    
    bandWidth.setValue(0.5);
    sinAmp.setValue(0.3);
}

OscillatorMixer::~OscillatorMixer() {
    
}

StkFloat OscillatorMixer::getNextSample() noexcept {
    updateFreq();
    sqrOsc.setBandwidth(bandWidth.getNextValue());
    StkFloat output = (sinOsc.tick() * sinAmp.getNextValue()) + (sawOsc.tick() * sawAmp.getNextValue()) + (sqrOsc.tick() * sqrAmp.getNextValue()) + (triOsc.tick() * triAmp.getNextValue()) + (rndOsc.tick() * rndAmp.getNextValue());
    output *= noteVol;
    return output *= env.tick();
}

void OscillatorMixer::renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples) {
    
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    if (env.getState() == ADSR::IDLE) {
        clearCurrentNote();
    } else {
        while (--numSamples >=0) {
            const StkFloat currentSampe = getNextSample();
            for (int i = outputBuffer.getNumChannels(); --i >=0;)
                outputBuffer.addSample(i, startSample, currentSampe);
            ++startSample;
        }
    }
    
}




