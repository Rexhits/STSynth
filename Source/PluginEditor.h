/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.3.0

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_1CD4FE3AD3723184__
#define __JUCE_HEADER_1CD4FE3AD3723184__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class StsynthAudioProcessorEditor  : public AudioProcessorEditor,
                                     private Timer,
                                     public SliderListener,
                                     public ButtonListener
{
public:
    //==============================================================================
    StsynthAudioProcessorEditor (StsynthAudioProcessor&);
    ~StsynthAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.


    void timerCallback() override {
        const AudioProcessorValueTreeState& state = processor.getValueTreeState();
        const int lfoSource = *state.getRawParameterValue("lfoSource");
        const int lfoTarget = *state.getRawParameterValue("lfoTarget");
        const int filterType = *state.getRawParameterValue("filterType");
        switch (lfoSource) {
            case 1:
                lfoSinToggle->setToggleState(true, NotificationType::sendNotification);
                break;
            case 2:
                lfoTriToggle->setToggleState(true, NotificationType::sendNotification);
                break;
            case 3:
                lfoSawToggle->setToggleState(true, NotificationType::sendNotification);
                break;
            case 4:
                lfoSqrToggle->setToggleState(true, NotificationType::sendNotification);
                break;
            default:
                lfoRndToggle->setToggleState(true, NotificationType::sendNotification);
                break;
        }

        switch (lfoTarget) {
            case 0:
                lfoOffToggle->setToggleState(true, NotificationType::sendNotification);
                break;
            case 1:
                cutoffToggle->setToggleState(true, NotificationType::sendNotification);
                break;
            case 2:
                resonanceToggle->setToggleState(true, NotificationType::sendNotification);
                break;
            default:
                volumeToggle->setToggleState(true, NotificationType::sendNotification);
                break;
        }

        switch (filterType) {
            case 0:
                lowpassToggle->setToggleState(true, NotificationType::sendNotification);
                break;
            case 1:
                highpassToggle->setToggleState(true, NotificationType::sendNotification);
                break;
            case 2:
                bandpassToggle->setToggleState(true, NotificationType::sendNotification);
                break;
            default:
                notchFilterToggle->setToggleState(true, NotificationType::sendNotification);
                break;
        }
    }
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    StsynthAudioProcessor& processor;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> dacLevelAttachment;
    ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> kbdTrackAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> cutoffAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> qAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> lfoFreqAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> lfoAmpAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sinAmpAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sawAmpAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sqrAmpAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> triAmpAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> rndAmpAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> attackAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> decayAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> glideAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sinOctaveAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sqrBandWidthAttachment;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> envGroup;
    ScopedPointer<GroupComponent> oscSettingsGroup;
    ScopedPointer<GroupComponent> SinComponent;
    ScopedPointer<Slider> attackSlider;
    ScopedPointer<Slider> decaySlider;
    ScopedPointer<Slider> sustainSlider;
    ScopedPointer<Slider> releaseSlider;
    ScopedPointer<Label> attack;
    ScopedPointer<Label> decay;
    ScopedPointer<Label> sustain;
    ScopedPointer<Label> release;
    ScopedPointer<GroupComponent> oscmixerGroup;
    ScopedPointer<Slider> sineOSC;
    ScopedPointer<Slider> sawOSC;
    ScopedPointer<Slider> sqrOSC;
    ScopedPointer<Slider> triOSC;
    ScopedPointer<Slider> noiseOSC;
    ScopedPointer<Label> sineLabel;
    ScopedPointer<Label> sawLabel;
    ScopedPointer<Label> sqrLabel;
    ScopedPointer<Label> triLabel;
    ScopedPointer<Label> noiseLabel;
    ScopedPointer<Label> sineOctaveLabel;
    ScopedPointer<Slider> sineOctaveSlider;
    ScopedPointer<Label> sineOctaveLabel1;
    ScopedPointer<Label> sineOctaveLabel2;
    ScopedPointer<GroupComponent> sqrComponent;
    ScopedPointer<Label> sqrBandwidthLabel;
    ScopedPointer<Slider> sqrBandwidthSlider;
    ScopedPointer<GroupComponent> filterGroup;
    ScopedPointer<Slider> cutoffSlider;
    ScopedPointer<Label> cutOffLabel;
    ScopedPointer<Slider> resonanceSlider;
    ScopedPointer<Label> resonanceLabel;
    ScopedPointer<ToggleButton> lowpassToggle;
    ScopedPointer<ToggleButton> highpassToggle;
    ScopedPointer<ToggleButton> bandpassToggle;
    ScopedPointer<Label> glideLabel;
    ScopedPointer<Slider> glideSlider;
    ScopedPointer<GroupComponent> lfoGroup;
    ScopedPointer<Slider> lfoPitchSlider;
    ScopedPointer<Slider> lfoAmpSlider;
    ScopedPointer<Label> lfoPitchLabel;
    ScopedPointer<Label> lfoAmpLabel;
    ScopedPointer<ToggleButton> lfoSinToggle;
    ScopedPointer<ToggleButton> lfoTriToggle;
    ScopedPointer<ToggleButton> lfoSawToggle;
    ScopedPointer<ToggleButton> lfoSqrToggle;
    ScopedPointer<ToggleButton> lfoRndToggle;
    ScopedPointer<ToggleButton> cutoffToggle;
    ScopedPointer<ToggleButton> resonanceToggle;
    ScopedPointer<ToggleButton> volumeToggle;
    ScopedPointer<ToggleButton> notchFilterToggle;
    ScopedPointer<Slider> masterVolumeSlider;
    ScopedPointer<Label> masterVolumeLabel;
    ScopedPointer<ToggleButton> lfoOffToggle;
    ScopedPointer<ToggleButton> kbdTrackingToggle;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StsynthAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_1CD4FE3AD3723184__
