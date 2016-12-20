/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "OscillatorMixer.h"
#include "Lfo.h"

using namespace stk;

//==============================================================================
/**
*/
class StsynthAudioProcessor  : public AudioProcessor, public AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    StsynthAudioProcessor();
    ~StsynthAudioProcessor();

    //==============================================================================
    
    
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif
    
    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    AudioProcessorValueTreeState& getValueTreeState() {
        return *mState;
    };
    
    
private:
    //==============================================================================
    Synth synth;
    ScopedPointer<AudioProcessorValueTreeState> mState;
    LinearSmoothedValue<StkFloat> dacVol;
    bool trackKbd = false;
    int lfoTarget = 0;
    int filterType = 0;
    int voiceNum = 15;
    double cutoff = 20000;
    double q = 0.98;
    double sr;
    LinearSmoothedValue<StkFloat> mod;
    LFO lfo;
//    IIRFilter filter[2];
    OwnedArray<IIRFilter> filter;
    
    StkFloat map(int x, int in_min, int in_max, StkFloat out_min, StkFloat out_max)
    {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }
    
    void setLfoSource(int index) {
        lfo.source = index;
    }
    
    void setLFOFreq(StkFloat value) {
        lfo.setFrequency(value);
    }
    
    void setLFOAmp(StkFloat value) {
        lfo.setAmp(value);
    }
    
    void setCoefficients(double cutoff_, double q_) {
        switch (filterType) {
            case 0:
                for (int i = 0; i < getTotalNumOutputChannels(); i ++) {
                    filter[i]->setCoefficients(IIRCoefficients::makeLowPass(sr, cutoff_, q_));
                }
                break;
            case 1:
                for (int i = 0; i < getTotalNumOutputChannels(); i ++) {
                    filter[i]->setCoefficients(IIRCoefficients::makeHighPass(sr, cutoff_, q_));
                }
                
                break;
            case 2:
                for (int i = 0; i < getTotalNumOutputChannels(); i ++) {
                    filter[i]->setCoefficients(IIRCoefficients::makeBandPass(sr, cutoff_, q_));
                }
                
                break;
            case 3:
                for (int i = 0; i < getTotalNumOutputChannels(); i ++) {
                    filter[i]->setCoefficients(IIRCoefficients::makeNotchFilter(sr, cutoff_, q_));
                }
                
                break;
            case 4:
                for (int i = 0; i < getTotalNumOutputChannels(); i ++) {
                    filter[i]->setCoefficients(IIRCoefficients::makeAllPass(sr, cutoff_, q_));
                }
                
                break;
            default:
                break;
        }
    }
    void updateLFOTarget() {
        float cutoff_ = cutoff;
        float q_ = q;
        switch (lfoTarget) {
            case 1:
                cutoff_ = cutoff + cutoff * lfo.tick();
                if (cutoff_ < 30) {
                    cutoff_ = 30;
                } else if (cutoff_ > 20000) {
                    cutoff_ = 20000;
                }
                setCoefficients(cutoff_, q);
                break;
            case 2:
                q_ = q + q * lfo.tick();
                if (q_ < 0.98) {
                    q_ = 0.98;
                } else if (q > 15) {
                    q_ = 15;
                }
                setCoefficients(cutoff, q_);
                break;
            default:
                setCoefficients(cutoff, q);
                break;
        }
    }
    
    
    
    
    void kbdTracking(int key) {
        cutoff = MidiMessage::getMidiNoteInHertz(key);
    }
    
    
    
    void parameterChanged (const String &parameterID, float newValue) override {
        if (parameterID == "dacLevel") {
            dacVol.setValue(newValue);
        }
        if (parameterID == "lfoTarget") {
            lfoTarget = newValue;
        }
        if (parameterID == "lfoSource") {
            setLfoSource(newValue);
        }
        if (parameterID == "filterType") {
            filterType = newValue;
        }
        if (parameterID == "trackKbd") {
            trackKbd = newValue;
        }
        if (parameterID == "cutoff") {
            cutoff = newValue;
        }
        if (parameterID == "q") {
            q = newValue;
        }
        if (parameterID == "lfoFreq") {
            setLFOFreq(newValue);
        }
        if (parameterID == "lfoAmp") {
            setLFOAmp(newValue);
        }
        if (parameterID == "sinAmp") {
            synth.setSinAmp(newValue);
        }
        if (parameterID == "sawAmp") {
            synth.setSawAmp(newValue);
        }
        if (parameterID == "sqrAmp") {
            synth.setSqrAmp(newValue);
        }
        if (parameterID == "triAmp") {
            synth.setTriAmp(newValue);
        }
        if (parameterID == "rndAmp") {
            synth.setRndAmp(newValue);
        }
        if (parameterID == "attack") {
            synth.setAttack(newValue);
        }
        if (parameterID == "decay") {
            synth.setDecay(newValue);
        }
        if (parameterID == "sustain") {
            synth.setSustain(newValue);
        }
        if (parameterID == "release") {
            synth.setRelease(newValue);
        }
        if (parameterID == "glide") {
            synth.setGlide(newValue);
        }
        if (parameterID == "sinOctave") {
            synth.setSineOctave(newValue);
        }
        if (parameterID == "sqrBandWidth") {
            synth.setBandWidth(newValue);
        }
    }
    
    StkFloat getLFOFreq () {return lfo.getFrequency();}
    
    StkFloat getLFOAmp() {return lfo.getAmp();}
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StsynthAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
