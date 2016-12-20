/*
  ==============================================================================

    Lfo.h
    Created: 24 Nov 2016 1:53:39am
    Author:  WangRex

  ==============================================================================
*/

#ifndef LFO_H_INCLUDED
#define LFO_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "TriWave.h"

using namespace stk;

class SinLFO {
public:
    SinLFO() {
        
    }
    ~SinLFO() {
        
    }
    
    StkFloat tick() {
        phase += rate;
        if (phase > 2.0)
            phase -= 4.0;
        return phase * (2.0 - fabs(phase));
    }
    void setFrequency(StkFloat newValue) {
        freq = newValue;
        rate = 4.0 * freq / sr;
    }
    void setSampleRate (StkFloat newValue) {
        sr = newValue;
        rate = 4.0 * freq / sr;
    }
private:
    StkFloat sr;
    StkFloat freq;
    StkFloat rate;
    StkFloat cos;
    StkFloat phase;
};

class SawLFO {
public:
    SawLFO() {
        
    }
    ~SawLFO() {
        
    }
    
    StkFloat tick() {
        if (phase > 1.0)
            phase -= 1.0;
        phase += rate;
        return 2.0 * phase - 1.0;
    }
    void setFrequency(StkFloat newValue) {
        freq = newValue;
        rate = freq / sr;
    }
    void setSampleRate (StkFloat newValue) {
        sr = newValue;
        rate = freq / sr;
    }
private:
    StkFloat sr;
    StkFloat freq;
    StkFloat rate;
    StkFloat phase;
};

class SqrLFO {
public:
    SqrLFO() {
        
    }
    ~SqrLFO() {
        
    }
    
    StkFloat tick() {
        
        if (phase > 1.0)
            phase -= 1.0;
        phase += rate;
        StkFloat output = phase > 0.5 ? -1.0 : +1.0;
        return output;
    }
    void setFrequency(StkFloat newValue) {
        freq = newValue;
        rate = freq / sr;
    }
    void setSampleRate (StkFloat newValue) {
        sr = newValue;
        rate = freq / sr;
    }
private:
    StkFloat sr;
    StkFloat freq;
    StkFloat rate;
    StkFloat phase;
};

class RndLFO {
public:
    RndLFO() {
        
    }
    ~RndLFO() {
        
    }
    
    StkFloat tick() {
        phase += rate;
        if (phase > 0.5) {
            output = (StkFloat) ( 2.0 * rand() / (RAND_MAX + 1.0) - 1.0 );
            phase -= 0.5;
        }
        return output;
    }
    void setFrequency(StkFloat newValue) {
        rate = freq / sr;
        freq = newValue;
        
    }
    void setSampleRate (StkFloat newValue) {
        sr = newValue;
        rate = freq / sr;
    }
private:
    StkFloat output = (StkFloat) ( 2.0 * rand() / (RAND_MAX + 1.0) - 1.0 );
    StkFloat rate;
    StkFloat sr;
    StkFloat freq;
    StkFloat cos;
    StkFloat phase;
};

class LFO {
public:
    
    int source = 0;
    
    LFO(){
        sinOsc.setSampleRate(Stk::sampleRate());
        sawOsc.setSampleRate(Stk::sampleRate());
        sqrOsc.setSampleRate(Stk::sampleRate());
        rndOsc.setSampleRate(Stk::sampleRate());
        amp.reset(Stk::sampleRate(), 0.001);
        freq.reset(Stk::sampleRate(), 0.001);
        amp.setValue(1);
        freq.setValue(2);
    }
    ~LFO(){
        
    }
    
    void setAmp(StkFloat amp_) {
        amp.setValue(amp_);
    }
    
    void setFrequency (StkFloat freq_) {
        freq.setValue(freq_);
    }
    
    StkFloat getFrequency() {return freq.getTargetValue();}
    
    StkFloat getAmp() {return amp.getTargetValue();}
    
    StkFloat switchSource() {
        switch (source) {
            case 1:
                return sinOsc.tick() * amp.getNextValue();
                break;
            case 2:
                return triOsc.tick() * amp.getNextValue();
                break;
            case 3:
                return sawOsc.tick() * amp.getNextValue();
                break;
            case 4:
                return sqrOsc.tick() * amp.getNextValue();
                break;
            case 5:
                return rndOsc.tick() * amp.getNextValue();
                break;
            default:
                return 0;
                break;
        }
    }
    
    StkFloat tick();
private:
    //    double tailOff;
    StkFloat getNextSample() noexcept;
    
    LinearSmoothedValue<StkFloat> amp;
    
    LinearSmoothedValue<StkFloat> freq;
    SinLFO sinOsc;
    SawLFO sawOsc;
    SqrLFO sqrOsc;
    Triwave triOsc;
    RndLFO rndOsc;
};


#endif  // LFO_H_INCLUDED
