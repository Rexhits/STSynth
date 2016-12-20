/*
  ==============================================================================

    Synth.h
    Created: 18 Nov 2016 4:40:34pm
    Author:  WangRex

  ==============================================================================
*/

#ifndef SYNTH_H_INCLUDED
#define SYNTH_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "TriWave.h"
#include "PulseWave.h"

using namespace stk;

class SynthSound : public SynthesiserSound
{
public:
    SynthSound() {}
    
    bool appliesToNote (int /*midiNoteNumber*/) override  { return true; }
    bool appliesToChannel (int /*midiChannel*/) override  { return true; }
};



class OscillatorMixer: public SynthesiserVoice {
public:
    OscillatorMixer();
    ~OscillatorMixer();
    
    LinearSmoothedValue<StkFloat> sinAmp;
    LinearSmoothedValue<StkFloat> sawAmp;
    LinearSmoothedValue<StkFloat> sqrAmp;
    LinearSmoothedValue<StkFloat> triAmp;
    LinearSmoothedValue<StkFloat> rndAmp;
    ADSR env;
    
    int sineOctave;
    
    bool canPlaySound (SynthesiserSound* sound) override {
        return dynamic_cast<SynthSound*> (sound) != nullptr;
    }
    
    void startNote(int midiNoteNumber, float velocity, SynthesiserSound * /*sound*/, int /*currentPitchWheelPosition*/) override {
        double cyclesPerSecond = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        currentNote = cyclesPerSecond;
        noteVol = velocity;
        setFrequency(cyclesPerSecond * pitchMod);
        env.keyOn();
    }
    
    void stopNote(float /*velocity*/, bool allowTailOff) override {
        env.keyOff();
    }
    void setSineOctave(int octave) {
        sineOctave = octave;
    }
    
    void setFrequency (StkFloat freq) {
        if (sineOctave == -1) {
            sinFreq.setValue(freq / 2.0f);
        } else if (sineOctave == -2) {
            sinFreq.setValue(freq / 4.0f);
        } else {
            sinFreq.setValue(freq);
        }
        sawFreq.setValue(freq);
        sqrFreq.setValue(freq);
        triFreq.setValue(freq);
    }
    void setGlide(StkFloat glide) {
        sinFreq.reset(Stk::sampleRate(), glide / 100);
        sawFreq.reset(Stk::sampleRate(), glide / 100);
        sqrFreq.reset(Stk::sampleRate(), glide / 100);
        triFreq.reset(Stk::sampleRate(), glide / 100);
    }
    
    void setBandWidth(StkFloat bandwidth) {
        bandWidth.setValue(bandwidth);
    }

    void directlySetFreq (StkFloat freq) {
        if (sineOctave == -1) {
            sinOsc.setFrequency(freq / 2.0f);
        } else if (sineOctave == -2) {
            sinOsc.setFrequency(freq / 4.0f);
        } else {
            sinOsc.setFrequency(freq);
        }
        sawOsc.setFrequency(freq);
        sqrOsc.setFrequency(freq);
        setFrequency(freq);
    }
    void renderNextBlock (AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
    
    void pitchWheelMoved (int newValue) override {
        int mod = pitchBendRange * 200 *(pitchBend - 8191.5) / 16383;
        pitchMod = pow(2.0, mod / 1200.0);
        setFrequency(currentNote * pitchMod);
        std::cout << sawFreq.getNextValue() * mod << std::endl;
    }
    void controllerMoved(int controller, int value) override {
        
    }
    
    void resetVoice() {
        sinAmp.reset(Stk::sampleRate(), 0.005);
        sawAmp.reset(Stk::sampleRate(), 0.005);
        sqrAmp.reset(Stk::sampleRate(), 0.005);
        triAmp.reset(Stk::sampleRate(), 0.005);
        rndAmp.reset(Stk::sampleRate(), 0.005);
        
        sinFreq.reset(Stk::sampleRate(), 0);
        sawFreq.reset(Stk::sampleRate(), 0);
        sqrFreq.reset(Stk::sampleRate(), 0);
        triFreq.reset(Stk::sampleRate(), 0);
        bandWidth.reset(Stk::sampleRate(), 0.01);
    }
        
    int pitchBend = 0;
private:
//    double tailOff;
    StkFloat getNextSample() noexcept;
    double currentNote;
    double pitchMod = 1;
    int pitchBendRange = 12;
    void updateFreq() {
        sinOsc.setFrequency(sinFreq.getNextValue());
        sawOsc.setFrequency(sawFreq.getNextValue());
        sqrOsc.setFrequency(sqrFreq.getNextValue());
        triOsc.setFrequency(triFreq.getNextValue());
    }
    
    
    LinearSmoothedValue<StkFloat> sinFreq;
    LinearSmoothedValue<StkFloat> sawFreq;
    LinearSmoothedValue<StkFloat> sqrFreq;
    LinearSmoothedValue<StkFloat> triFreq;
    LinearSmoothedValue<StkFloat> bandWidth;
    
    StkFloat noteVol;
    SineWave sinOsc;
    BlitSaw sawOsc;
    PulseWave sqrOsc;
    Triwave triOsc;
    Noise rndOsc;
        
    StkFloat map(int x, int in_min, int in_max, StkFloat out_min, StkFloat out_max)
    {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }
        
};


class Synth: public Synthesiser {
public:
    void setSinAmp(StkFloat newValue) {
        OscillatorMixer *voice;
        int numVoices = getNumVoices();
        for (int i = 0; i < numVoices; i++) {
            voice = dynamic_cast<OscillatorMixer *>(getVoice(i));
            if (voice)
                voice->sinAmp.setValue(newValue);
        }
    }
    void setSawAmp(StkFloat newValue) {
        OscillatorMixer *voice;
        int numVoices = getNumVoices();
        for (int i = 0; i < numVoices; i++) {
            voice = dynamic_cast<OscillatorMixer *>(getVoice(i));
            if (voice)
                voice->sawAmp.setValue(newValue);
        }
    }
    
    void setSqrAmp(StkFloat newValue) {
        OscillatorMixer *voice;
        int numVoices = getNumVoices();
        for (int i = 0; i < numVoices; i++) {
            voice = dynamic_cast<OscillatorMixer *>(getVoice(i));
            if (voice)
                voice->sqrAmp.setValue(newValue);
        }
    }
    
    void setTriAmp(StkFloat newValue) {
        OscillatorMixer *voice;
        int numVoices = getNumVoices();
        for (int i = 0; i < numVoices; i++) {
            voice = dynamic_cast<OscillatorMixer *>(getVoice(i));
            if (voice)
                voice->triAmp.setValue(newValue);
        }
    }
    
    void setRndAmp(StkFloat newValue) {
        OscillatorMixer *voice;
        int numVoices = getNumVoices();
        for (int i = 0; i < numVoices; i++) {
            voice = dynamic_cast<OscillatorMixer *>(getVoice(i));
            if (voice)
                voice->rndAmp.setValue(newValue);
        }
    }
    
    void setBandWidth(StkFloat newValue) {
        OscillatorMixer *voice;
        int numVoices = getNumVoices();
        for (int i = 0; i < numVoices; i++) {
            voice = dynamic_cast<OscillatorMixer *>(getVoice(i));
            if (voice)
                voice->setBandWidth(newValue);
        }
    }
    
    void setGlide(StkFloat newValue) {
        OscillatorMixer *voice;
        int numVoices = getNumVoices();
        for (int i = 0; i < numVoices; i++) {
            voice = dynamic_cast<OscillatorMixer *>(getVoice(i));
            if (voice)
                voice->setGlide(newValue);
        }
    }
    
    void setSineOctave(int newValue) {
        OscillatorMixer *voice;
        int numVoices = getNumVoices();
        for (int i = 0; i < numVoices; i++) {
            voice = dynamic_cast<OscillatorMixer *>(getVoice(i));
            if (voice)
                voice->setSineOctave(newValue);
        }
    }
    
    void setAttack(int newValue) {
        OscillatorMixer *voice;
        int numVoices = getNumVoices();
        for (int i = 0; i < numVoices; i++) {
            voice = dynamic_cast<OscillatorMixer *>(getVoice(i));
            if (voice)
                voice->env.setAttackRate(1.0 / ((newValue / 1000.0) * Stk::sampleRate()));
        }
    }
    
    void setDecay(int newValue) {
        OscillatorMixer *voice;
        int numVoices = getNumVoices();
        for (int i = 0; i < numVoices; i++) {
            voice = dynamic_cast<OscillatorMixer *>(getVoice(i));
            if (voice)
                voice->env.setDecayRate(1.0 / ((newValue / 1000.0) * Stk::sampleRate()));
        }
    }
    
    void setSustain(int newValue) {
        OscillatorMixer *voice;
        int numVoices = getNumVoices();
        for (int i = 0; i < numVoices; i++) {
            voice = dynamic_cast<OscillatorMixer *>(getVoice(i));
            if (voice)
                voice->env.setSustainLevel(newValue);
        }
    }
    
    void setRelease(int newValue) {
        OscillatorMixer *voice;
        int numVoices = getNumVoices();
        for (int i = 0; i < numVoices; i++) {
            voice = dynamic_cast<OscillatorMixer *>(getVoice(i));
            if (voice)
                voice->env.setReleaseRate(1.0 / ((newValue / 1000.0) * Stk::sampleRate()));
        }
    }
    
    void resetSynth() {
        OscillatorMixer *voice;
        int numVoices = getNumVoices();
        for (int i = 0; i < numVoices; i++) {
            voice = dynamic_cast<OscillatorMixer *>(getVoice(i));
            if (voice)
                voice->resetVoice();
        }
    }
    
    void handlePitchWheel (int midiChannel, int wheelValue) override{
        OscillatorMixer *voice;
        int numVoices = getNumVoices();
        for (int i = 0; i < numVoices; i++) {
            voice = dynamic_cast<OscillatorMixer *>(getVoice(i));
            if (voice) {
                voice->pitchBend = wheelValue;
                voice->pitchWheelMoved(wheelValue);
            }
            
        }
    }
    
private:
    
};


#endif  // SYNTH_H_INCLUDED
