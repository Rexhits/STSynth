/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "OscillatorMixer.h"


//==============================================================================
StsynthAudioProcessor::StsynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    
    synth.addSound(new SynthSound());
    synth.setNoteStealingEnabled(false);
    dacVol.setValue(0.5);
    mState = new AudioProcessorValueTreeState(*this, nullptr);
    mState->createAndAddParameter("dacLevel", "DacLevel", "", NormalisableRange<float>(0.0, 1.0), 0.5, nullptr, nullptr);
    mState->createAndAddParameter("lfoTarget", "LfoTarget", "", NormalisableRange<float>(0.0f, 3.0f, 1.0f), 0.0f, nullptr, nullptr);
    mState->createAndAddParameter("lfoSource", "LfoSource", "", NormalisableRange<float>(0.0f, 5.0f, 1.0f), 1.0f, nullptr, nullptr);
    mState->createAndAddParameter("filterType", "FilterType", "", NormalisableRange<float>(0.0f, 3.0f, 1.0f), 1.0f, nullptr, nullptr);
    mState->createAndAddParameter("trackKbd", "TrackKbd", "", NormalisableRange<float>(0.0f, 1.0f, 1.0f), 0.0f, nullptr, nullptr);
    mState->createAndAddParameter("cutoff", "Cutoff", "", NormalisableRange<float>(20, 20000, 0), 20000, nullptr, nullptr);
    mState->createAndAddParameter("q", "Q", "", NormalisableRange<float>(0.98, 99, 0), 0.98, nullptr, nullptr);
    mState->createAndAddParameter("lfoFreq", "LfoFreq", "", NormalisableRange<float>(0.5, 20, 0), 0.5, nullptr, nullptr);
    mState->createAndAddParameter("lfoAmp", "LfoAmp", "", NormalisableRange<float>(0, 1, 0), 1, nullptr, nullptr);
    mState->createAndAddParameter("sinAmp", "SinAmp", "", NormalisableRange<float>(0, 0.4, 0), 0.3, nullptr, nullptr);
    mState->createAndAddParameter("sawAmp", "SawAmp", "", NormalisableRange<float>(0, 0.4, 0), 0, nullptr, nullptr);
    mState->createAndAddParameter("sqrAmp", "SqrAmp", "", NormalisableRange<float>(0, 0.4, 0), 0, nullptr, nullptr);
    mState->createAndAddParameter("triAmp", "TriAmp", "", NormalisableRange<float>(0, 0.4, 0), 0, nullptr, nullptr);
    mState->createAndAddParameter("rndAmp", "RndAmp", "", NormalisableRange<float>(0, 0.4, 0), 0, nullptr, nullptr);
    mState->createAndAddParameter("attack", "Attack", "", NormalisableRange<float>(1, 2000, 0), 1, nullptr, nullptr);
    mState->createAndAddParameter("decay", "Decay", "", NormalisableRange<float>(1, 2000, 0), 1, nullptr, nullptr);
    mState->createAndAddParameter("sustain", "Sustain", "", NormalisableRange<float>(0, 1, 0), 1, nullptr, nullptr);
    mState->createAndAddParameter("release", "Release", "", NormalisableRange<float>(1, 2000, 0), 5, nullptr, nullptr);
    mState->createAndAddParameter("glide", "Glide", "", NormalisableRange<float>(0, 100, 0), 0, nullptr, nullptr);
    mState->createAndAddParameter("sinOctave", "SinOctave", "", NormalisableRange<float>(-2, 0, 1), 0, nullptr, nullptr);
    mState->createAndAddParameter("sqrBandWidth", "SqrBandWidth", "", NormalisableRange<float>(0.1, 0.9, 0), 0.5, nullptr, nullptr);
    
    mState->addParameterListener("dacLevel", this);
    mState->addParameterListener("lfoTarget", this);
    mState->addParameterListener("lfoSource", this);
    mState->addParameterListener("filterType", this);
    mState->addParameterListener("trackKbd", this);
    mState->addParameterListener("cutoff", this);
    mState->addParameterListener("q", this);
    mState->addParameterListener("lfoFreq", this);
    mState->addParameterListener("lfoAmp", this);
    mState->addParameterListener("sinAmp", this);
    mState->addParameterListener("sawAmp", this);
    mState->addParameterListener("sqrAmp", this);
    mState->addParameterListener("triAmp", this);
    mState->addParameterListener("rndAmp", this);
    mState->addParameterListener("attack", this);
    mState->addParameterListener("decay", this);
    mState->addParameterListener("sustain", this);
    mState->addParameterListener("release", this);
    mState->addParameterListener("glide", this);
    mState->addParameterListener("sinOctave", this);
    mState->addParameterListener("sqrBandWidth", this);
    
    mState->state = ValueTree("STSynth");
}

StsynthAudioProcessor::~StsynthAudioProcessor()
{
    mState = nullptr;
}

//==============================================================================
const String StsynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}


bool StsynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool StsynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double StsynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int StsynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int StsynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void StsynthAudioProcessor::setCurrentProgram (int index)
{
}

const String StsynthAudioProcessor::getProgramName (int index)
{
    return String();
}

void StsynthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void StsynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

//    synth.clearVoices();
    
    for (int i = 0; i < getTotalNumOutputChannels(); i ++) {
        filter.add(new IIRFilter());
    }
    sr = sampleRate;
    dacVol.reset(sr, 0.01);
    Stk::setSampleRate(sr);
    synth.setCurrentPlaybackSampleRate(sr);
    synth.clearVoices();
    for (int i = 0; i < voiceNum; ++i) {
        synth.addVoice(new OscillatorMixer);
    }
    mod.reset(sr, 0.005);
    dacVol.setValue(0.5);
    setCoefficients(cutoff, q);
}



void StsynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    filter.clear();
}


#ifndef JucePlugin_PreferredChannelConfigurations
bool StsynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void StsynthAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();
    const int numSamples = buffer.getNumSamples();
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
    MidiBuffer::Iterator iterator (midiMessages);
    MidiMessage msg;
    int sampleNum;
    while (iterator.getNextEvent(msg, sampleNum)) {
        if (msg.isNoteOn()) {
            if (trackKbd) {
                kbdTracking(msg.getNoteNumber());
            }
        }
        if (msg.isControllerOfType(7)) {
            setParameterNotifyingHost(0, map(msg.getControllerValue(), 0, 127, 0.0f, 1.0f));
        }
        if (msg.isControllerOfType(74)) {
            setParameterNotifyingHost(5, map(msg.getControllerValue(), 0, 127, 0.0f, 1.0f));
        }
        if (msg.isControllerOfType(71)) {
            setParameterNotifyingHost(6, map(msg.getControllerValue(), 0, 127, 0.0f, 1.0f));
        }
        if (msg.isControllerOfType(75)) {
            setParameterNotifyingHost(7, map(msg.getControllerValue(), 0, 127, 0.0f, 1.0f));
        }
        if (msg.isControllerOfType(76)) {
            setParameterNotifyingHost(8, map(msg.getControllerValue(), 0, 127, 0.0f, 1.0f));
        }
    }

    for (int c = 0; c < totalNumOutputChannels; c++) {
        float* const channelData = buffer.getWritePointer(c);
        filter[c]->processSamples(channelData, numSamples);
        for (int i = 0; i < numSamples; ++i) {
            updateLFOTarget();
            if (lfoTarget == 3) {
                mod.setValue(lfo.tick());
                if (lfo.tick() <= 0) {
                    mod.setValue(0);
                }
                channelData[i] *= mod.getNextValue();
                channelData[i] *= dacVol.getNextValue();
            } else {
                mod.setValue(0);
                channelData[i] *= dacVol.getNextValue();
            }
        }
    }

}

//==============================================================================
bool StsynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* StsynthAudioProcessor::createEditor()
{
    return new StsynthAudioProcessorEditor (*this);
}

//==============================================================================
void StsynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    ScopedPointer<XmlElement> xml (mState->state.createXml());
    copyXmlToBinary(*xml, destData);
    
}

void StsynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    ScopedPointer<XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    if (xml != nullptr) {
        if (xml->hasTagName(mState->state.getType())) {
            mState->state = ValueTree::fromXml(*xml);
        }
    }
}

//==============================================================================

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new StsynthAudioProcessor();
}
