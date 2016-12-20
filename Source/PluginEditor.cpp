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

//[Headers] You can add your own extra header files here...
#include "PluginProcessor.h"
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
StsynthAudioProcessorEditor::StsynthAudioProcessorEditor (StsynthAudioProcessor&p)
    : AudioProcessorEditor (&p), processor(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    startTimerHz(30);
    //[/Constructor_pre]

    addAndMakeVisible (envGroup = new GroupComponent ("envGroup",
                                                      TRANS("Env")));
    envGroup->setTextLabelPosition (Justification::centred);
    envGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    envGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (oscSettingsGroup = new GroupComponent ("OSCSettings",
                                                              TRANS("OSC Settings")));
    oscSettingsGroup->setTextLabelPosition (Justification::centred);
    oscSettingsGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    oscSettingsGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (SinComponent = new GroupComponent ("SinComponent",
                                                          TRANS("Sin")));
    SinComponent->setTextLabelPosition (Justification::centred);
    SinComponent->setColour (GroupComponent::outlineColourId, Colour (0xaaffffff));
    SinComponent->setColour (GroupComponent::textColourId, Colour (0xdfffffff));

    addAndMakeVisible (attackSlider = new Slider ("attack Slider"));
    attackSlider->setRange (1, 2000, 0);
    attackSlider->setSliderStyle (Slider::Rotary);
    attackSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    attackSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fe1f3bf));
    attackSlider->setColour (Slider::rotarySliderOutlineColourId, Colours::white);
    attackSlider->addListener (this);

    addAndMakeVisible (decaySlider = new Slider ("decay Slider"));
    decaySlider->setRange (1, 2000, 0);
    decaySlider->setSliderStyle (Slider::Rotary);
    decaySlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    decaySlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fe1f3bf));
    decaySlider->setColour (Slider::rotarySliderOutlineColourId, Colours::white);
    decaySlider->addListener (this);

    addAndMakeVisible (sustainSlider = new Slider ("sustainSlider"));
    sustainSlider->setRange (0, 1, 0);
    sustainSlider->setSliderStyle (Slider::Rotary);
    sustainSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sustainSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fe1f3bf));
    sustainSlider->setColour (Slider::rotarySliderOutlineColourId, Colours::white);
    sustainSlider->addListener (this);

    addAndMakeVisible (releaseSlider = new Slider ("releaseSlider"));
    releaseSlider->setRange (1, 2000, 0);
    releaseSlider->setSliderStyle (Slider::Rotary);
    releaseSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    releaseSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fe1f3bf));
    releaseSlider->setColour (Slider::rotarySliderOutlineColourId, Colours::white);
    releaseSlider->addListener (this);

    addAndMakeVisible (attack = new Label ("attack",
                                           TRANS("Attack")));
    attack->setFont (Font (10.00f, Font::plain));
    attack->setJustificationType (Justification::centred);
    attack->setEditable (false, false, false);
    attack->setColour (Label::textColourId, Colours::white);
    attack->setColour (TextEditor::textColourId, Colours::black);
    attack->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (decay = new Label ("decay",
                                          TRANS("Decay")));
    decay->setFont (Font (10.00f, Font::plain));
    decay->setJustificationType (Justification::centred);
    decay->setEditable (false, false, false);
    decay->setColour (Label::textColourId, Colours::white);
    decay->setColour (TextEditor::textColourId, Colours::black);
    decay->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sustain = new Label ("sustain",
                                            TRANS("Sustain")));
    sustain->setFont (Font (10.00f, Font::plain));
    sustain->setJustificationType (Justification::centred);
    sustain->setEditable (false, false, false);
    sustain->setColour (Label::textColourId, Colours::white);
    sustain->setColour (TextEditor::textColourId, Colours::black);
    sustain->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (release = new Label ("release",
                                            TRANS("Release")));
    release->setFont (Font (10.00f, Font::plain));
    release->setJustificationType (Justification::centred);
    release->setEditable (false, false, false);
    release->setColour (Label::textColourId, Colours::white);
    release->setColour (TextEditor::textColourId, Colours::black);
    release->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (oscmixerGroup = new GroupComponent ("OSCmixer",
                                                           TRANS("OSC Mixer")));
    oscmixerGroup->setTextLabelPosition (Justification::centred);
    oscmixerGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    oscmixerGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (sineOSC = new Slider ("sineOSC"));
    sineOSC->setRange (0, 0.4, 0);
    sineOSC->setSliderStyle (Slider::LinearVertical);
    sineOSC->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sineOSC->addListener (this);

    addAndMakeVisible (sawOSC = new Slider ("sawOSC"));
    sawOSC->setRange (0, 0.4, 0);
    sawOSC->setSliderStyle (Slider::LinearVertical);
    sawOSC->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sawOSC->addListener (this);

    addAndMakeVisible (sqrOSC = new Slider ("oscMixer"));
    sqrOSC->setRange (0, 0.4, 0);
    sqrOSC->setSliderStyle (Slider::LinearVertical);
    sqrOSC->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sqrOSC->addListener (this);

    addAndMakeVisible (triOSC = new Slider ("triOSC"));
    triOSC->setRange (0, 0.4, 0);
    triOSC->setSliderStyle (Slider::LinearVertical);
    triOSC->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    triOSC->addListener (this);

    addAndMakeVisible (noiseOSC = new Slider ("noiseOSC"));
    noiseOSC->setRange (0, 0.4, 0);
    noiseOSC->setSliderStyle (Slider::LinearVertical);
    noiseOSC->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    noiseOSC->addListener (this);

    addAndMakeVisible (sineLabel = new Label ("sineLabel",
                                              TRANS("Sin")));
    sineLabel->setFont (Font (11.00f, Font::plain));
    sineLabel->setJustificationType (Justification::centred);
    sineLabel->setEditable (false, false, false);
    sineLabel->setColour (Label::textColourId, Colours::white);
    sineLabel->setColour (TextEditor::textColourId, Colours::black);
    sineLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sawLabel = new Label ("sawLabel",
                                             TRANS("Saw")));
    sawLabel->setFont (Font (11.00f, Font::plain));
    sawLabel->setJustificationType (Justification::centred);
    sawLabel->setEditable (false, false, false);
    sawLabel->setColour (Label::textColourId, Colours::white);
    sawLabel->setColour (TextEditor::textColourId, Colours::black);
    sawLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sqrLabel = new Label ("sqrLabel",
                                             TRANS("Sqr")));
    sqrLabel->setFont (Font (11.00f, Font::plain));
    sqrLabel->setJustificationType (Justification::centred);
    sqrLabel->setEditable (false, false, false);
    sqrLabel->setColour (Label::textColourId, Colours::white);
    sqrLabel->setColour (TextEditor::textColourId, Colours::black);
    sqrLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (triLabel = new Label ("triLabel",
                                             TRANS("Tri")));
    triLabel->setFont (Font (11.00f, Font::plain));
    triLabel->setJustificationType (Justification::centred);
    triLabel->setEditable (false, false, false);
    triLabel->setColour (Label::textColourId, Colours::white);
    triLabel->setColour (TextEditor::textColourId, Colours::black);
    triLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (noiseLabel = new Label ("noiseLabel",
                                               TRANS("Rnd")));
    noiseLabel->setFont (Font (11.00f, Font::plain));
    noiseLabel->setJustificationType (Justification::centred);
    noiseLabel->setEditable (false, false, false);
    noiseLabel->setColour (Label::textColourId, Colours::white);
    noiseLabel->setColour (TextEditor::textColourId, Colours::black);
    noiseLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sineOctaveLabel = new Label ("sineOctaveLabel",
                                                    TRANS("Octave")));
    sineOctaveLabel->setFont (Font (10.00f, Font::plain));
    sineOctaveLabel->setJustificationType (Justification::centred);
    sineOctaveLabel->setEditable (false, false, false);
    sineOctaveLabel->setColour (Label::textColourId, Colours::white);
    sineOctaveLabel->setColour (TextEditor::textColourId, Colours::black);
    sineOctaveLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sineOctaveSlider = new Slider ("sineOctaveSlider"));
    sineOctaveSlider->setRange (-2, 0, 1);
    sineOctaveSlider->setSliderStyle (Slider::RotaryHorizontalDrag);
    sineOctaveSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sineOctaveSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fe1f3bf));
    sineOctaveSlider->setColour (Slider::rotarySliderOutlineColourId, Colours::white);
    sineOctaveSlider->addListener (this);

    addAndMakeVisible (sineOctaveLabel1 = new Label ("sineOctaveLabel1",
                                                     TRANS("-2")));
    sineOctaveLabel1->setFont (Font (8.00f, Font::plain));
    sineOctaveLabel1->setJustificationType (Justification::centredLeft);
    sineOctaveLabel1->setEditable (false, false, false);
    sineOctaveLabel1->setColour (Label::textColourId, Colours::white);
    sineOctaveLabel1->setColour (TextEditor::textColourId, Colours::black);
    sineOctaveLabel1->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sineOctaveLabel2 = new Label ("sineOctaveLabel2",
                                                     TRANS("0")));
    sineOctaveLabel2->setFont (Font (8.00f, Font::plain));
    sineOctaveLabel2->setJustificationType (Justification::centredLeft);
    sineOctaveLabel2->setEditable (false, false, false);
    sineOctaveLabel2->setColour (Label::textColourId, Colours::white);
    sineOctaveLabel2->setColour (TextEditor::textColourId, Colours::black);
    sineOctaveLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sqrComponent = new GroupComponent ("sqrComponent",
                                                          TRANS("Sqr")));
    sqrComponent->setTextLabelPosition (Justification::centred);
    sqrComponent->setColour (GroupComponent::outlineColourId, Colour (0xaaffffff));
    sqrComponent->setColour (GroupComponent::textColourId, Colour (0xdfffffff));

    addAndMakeVisible (sqrBandwidthLabel = new Label ("sqrBandwidthLabel",
                                                      TRANS("BandWidth")));
    sqrBandwidthLabel->setFont (Font (10.00f, Font::plain));
    sqrBandwidthLabel->setJustificationType (Justification::centred);
    sqrBandwidthLabel->setEditable (false, false, false);
    sqrBandwidthLabel->setColour (Label::textColourId, Colours::white);
    sqrBandwidthLabel->setColour (TextEditor::textColourId, Colours::black);
    sqrBandwidthLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sqrBandwidthSlider = new Slider ("sqrBandwidthSlider"));
    sqrBandwidthSlider->setRange (0.1, 0.9, 0);
    sqrBandwidthSlider->setSliderStyle (Slider::Rotary);
    sqrBandwidthSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sqrBandwidthSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fe1f3bf));
    sqrBandwidthSlider->setColour (Slider::rotarySliderOutlineColourId, Colours::white);
    sqrBandwidthSlider->addListener (this);

    addAndMakeVisible (filterGroup = new GroupComponent ("filterGroup",
                                                         TRANS("OSC Settings")));
    filterGroup->setTextLabelPosition (Justification::centred);
    filterGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    filterGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (cutoffSlider = new Slider ("cutoffSlider"));
    cutoffSlider->setRange (20, 20000, 0);
    cutoffSlider->setSliderStyle (Slider::Rotary);
    cutoffSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    cutoffSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fe1f3bf));
    cutoffSlider->setColour (Slider::rotarySliderOutlineColourId, Colours::white);
    cutoffSlider->addListener (this);

    addAndMakeVisible (cutOffLabel = new Label ("curOffLabel",
                                                TRANS("Cutoff")));
    cutOffLabel->setFont (Font (10.00f, Font::plain));
    cutOffLabel->setJustificationType (Justification::centred);
    cutOffLabel->setEditable (false, false, false);
    cutOffLabel->setColour (Label::textColourId, Colours::white);
    cutOffLabel->setColour (TextEditor::textColourId, Colours::black);
    cutOffLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (resonanceSlider = new Slider ("resonanceSlider"));
    resonanceSlider->setRange (0.98, 99, 0);
    resonanceSlider->setSliderStyle (Slider::Rotary);
    resonanceSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    resonanceSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fe1f3bf));
    resonanceSlider->setColour (Slider::rotarySliderOutlineColourId, Colours::white);
    resonanceSlider->addListener (this);

    addAndMakeVisible (resonanceLabel = new Label ("resonanceLabel",
                                                   TRANS("Resonance")));
    resonanceLabel->setFont (Font (10.00f, Font::plain));
    resonanceLabel->setJustificationType (Justification::centred);
    resonanceLabel->setEditable (false, false, false);
    resonanceLabel->setColour (Label::textColourId, Colours::white);
    resonanceLabel->setColour (TextEditor::textColourId, Colours::black);
    resonanceLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lowpassToggle = new ToggleButton ("lowpassToggle"));
    lowpassToggle->setButtonText (TRANS("LP"));
    lowpassToggle->setRadioGroupId (1);
    lowpassToggle->addListener (this);
    lowpassToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (highpassToggle = new ToggleButton ("highpassToggle"));
    highpassToggle->setButtonText (TRANS("HP"));
    highpassToggle->setRadioGroupId (1);
    highpassToggle->addListener (this);
    highpassToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (bandpassToggle = new ToggleButton ("bandpassToggle"));
    bandpassToggle->setButtonText (TRANS("BP"));
    bandpassToggle->setRadioGroupId (1);
    bandpassToggle->addListener (this);
    bandpassToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (glideLabel = new Label ("glideLabel",
                                               TRANS("Glide")));
    glideLabel->setFont (Font (10.00f, Font::plain));
    glideLabel->setJustificationType (Justification::centred);
    glideLabel->setEditable (false, false, false);
    glideLabel->setColour (Label::textColourId, Colours::white);
    glideLabel->setColour (TextEditor::textColourId, Colours::black);
    glideLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (glideSlider = new Slider ("glideSlider"));
    glideSlider->setRange (0, 100, 0);
    glideSlider->setSliderStyle (Slider::Rotary);
    glideSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    glideSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fe1f3bf));
    glideSlider->setColour (Slider::rotarySliderOutlineColourId, Colours::white);
    glideSlider->addListener (this);

    addAndMakeVisible (lfoGroup = new GroupComponent ("lfoGroup",
                                                      TRANS("LFO")));
    lfoGroup->setTextLabelPosition (Justification::centred);
    lfoGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    lfoGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (lfoPitchSlider = new Slider ("lfoPitchSlider"));
    lfoPitchSlider->setRange (0.5, 20, 0);
    lfoPitchSlider->setSliderStyle (Slider::Rotary);
    lfoPitchSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    lfoPitchSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fe1f3bf));
    lfoPitchSlider->setColour (Slider::rotarySliderOutlineColourId, Colours::white);
    lfoPitchSlider->addListener (this);

    addAndMakeVisible (lfoAmpSlider = new Slider ("lfoAmpSlider"));
    lfoAmpSlider->setRange (0, 1, 0);
    lfoAmpSlider->setSliderStyle (Slider::Rotary);
    lfoAmpSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    lfoAmpSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fe1f3bf));
    lfoAmpSlider->setColour (Slider::rotarySliderOutlineColourId, Colours::white);
    lfoAmpSlider->addListener (this);

    addAndMakeVisible (lfoPitchLabel = new Label ("lfoPitchLabel",
                                                  TRANS("Freq")));
    lfoPitchLabel->setFont (Font (10.00f, Font::plain));
    lfoPitchLabel->setJustificationType (Justification::centred);
    lfoPitchLabel->setEditable (false, false, false);
    lfoPitchLabel->setColour (Label::textColourId, Colours::white);
    lfoPitchLabel->setColour (TextEditor::textColourId, Colours::black);
    lfoPitchLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lfoAmpLabel = new Label ("lfoAmpLabel",
                                                TRANS("Amp")));
    lfoAmpLabel->setFont (Font (10.00f, Font::plain));
    lfoAmpLabel->setJustificationType (Justification::centred);
    lfoAmpLabel->setEditable (false, false, false);
    lfoAmpLabel->setColour (Label::textColourId, Colours::white);
    lfoAmpLabel->setColour (TextEditor::textColourId, Colours::black);
    lfoAmpLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lfoSinToggle = new ToggleButton ("lfoSinToggle"));
    lfoSinToggle->setButtonText (TRANS("Sin"));
    lfoSinToggle->setRadioGroupId (2);
    lfoSinToggle->addListener (this);
    lfoSinToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (lfoTriToggle = new ToggleButton ("lfoTriToggle"));
    lfoTriToggle->setButtonText (TRANS("Tri"));
    lfoTriToggle->setRadioGroupId (2);
    lfoTriToggle->addListener (this);
    lfoTriToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (lfoSawToggle = new ToggleButton ("lfoSawToggle"));
    lfoSawToggle->setButtonText (TRANS("Saw"));
    lfoSawToggle->setRadioGroupId (2);
    lfoSawToggle->addListener (this);
    lfoSawToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (lfoSqrToggle = new ToggleButton ("lfoSqrToggle"));
    lfoSqrToggle->setButtonText (TRANS("Sqr"));
    lfoSqrToggle->setRadioGroupId (2);
    lfoSqrToggle->addListener (this);
    lfoSqrToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (lfoRndToggle = new ToggleButton ("lfoRndToggle"));
    lfoRndToggle->setButtonText (TRANS("Rnd"));
    lfoRndToggle->setRadioGroupId (2);
    lfoRndToggle->addListener (this);
    lfoRndToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (cutoffToggle = new ToggleButton ("cutoffToggle"));
    cutoffToggle->setButtonText (TRANS("Cutoff"));
    cutoffToggle->setRadioGroupId (3);
    cutoffToggle->addListener (this);
    cutoffToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (resonanceToggle = new ToggleButton ("resonanceToggle"));
    resonanceToggle->setButtonText (TRANS("Resonance"));
    resonanceToggle->setRadioGroupId (3);
    resonanceToggle->addListener (this);
    resonanceToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (volumeToggle = new ToggleButton ("volumeToggle"));
    volumeToggle->setButtonText (TRANS("DacVol"));
    volumeToggle->setRadioGroupId (3);
    volumeToggle->addListener (this);
    volumeToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (notchFilterToggle = new ToggleButton ("notchFilterToggle"));
    notchFilterToggle->setButtonText (TRANS("Notch"));
    notchFilterToggle->setRadioGroupId (1);
    notchFilterToggle->addListener (this);
    notchFilterToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (masterVolumeSlider = new Slider ("masterVolumeSlider"));
    masterVolumeSlider->setRange (0, 1, 0);
    masterVolumeSlider->setSliderStyle (Slider::Rotary);
    masterVolumeSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    masterVolumeSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fe1f3bf));
    masterVolumeSlider->setColour (Slider::rotarySliderOutlineColourId, Colours::white);
    masterVolumeSlider->addListener (this);

    addAndMakeVisible (masterVolumeLabel = new Label ("masterVolumeLabel",
                                                      TRANS("DAC Vol")));
    masterVolumeLabel->setFont (Font (10.00f, Font::plain));
    masterVolumeLabel->setJustificationType (Justification::centred);
    masterVolumeLabel->setEditable (false, false, false);
    masterVolumeLabel->setColour (Label::textColourId, Colours::white);
    masterVolumeLabel->setColour (TextEditor::textColourId, Colours::black);
    masterVolumeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lfoOffToggle = new ToggleButton ("lfoOffToggle"));
    lfoOffToggle->setButtonText (TRANS("OFF"));
    lfoOffToggle->setRadioGroupId (3);
    lfoOffToggle->addListener (this);
    lfoOffToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (kbdTrackingToggle = new ToggleButton ("kbdTrackingToggle"));
    kbdTrackingToggle->setButtonText (TRANS("KBD Tracking"));
    kbdTrackingToggle->addListener (this);
    kbdTrackingToggle->setColour (ToggleButton::textColourId, Colours::white);


    //[UserPreSize]

    //[/UserPreSize]

    setSize (350, 500);


    //[Constructor] You can add your own custom stuff here..
    sineOSC->setValue(0.3);
    attackSlider->setValue(1);
    decaySlider->setValue(1);
    releaseSlider->setValue(5);
    sustainSlider->setValue(1);
    cutoffSlider->setSkewFactorFromMidPoint(1200);
    cutoffSlider->setValue(20000);
    resonanceSlider->setSkewFactorFromMidPoint(8);
    resonanceSlider->setValue(0.98);
    sqrBandwidthSlider->setValue(0.5);
    lowpassToggle->setToggleState(true, NotificationType::sendNotification);
    lfoSinToggle->setToggleState(true, NotificationType::sendNotification);
    lfoOffToggle->setToggleState(true, NotificationType::sendNotification);
    sqrBandwidthSlider->setValue(0.5);
    sqrBandwidthSlider->setDoubleClickReturnValue(true, 0.5);
    lfoPitchSlider->setSkewFactorFromMidPoint(4);
    lfoAmpSlider->setValue(1);
    masterVolumeSlider->setValue(0.5);
    dacLevelAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), "dacLevel", *masterVolumeSlider);
    kbdTrackAttachment = new AudioProcessorValueTreeState::ButtonAttachment(p.getValueTreeState(), "trackKbd", *kbdTrackingToggle);
    cutoffAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), "cutoff", *cutoffSlider);
    qAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), "q", *resonanceSlider);
    lfoFreqAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), "lfoFreq", *lfoPitchSlider);
    lfoAmpAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), "lfoAmp", *lfoAmpSlider);
    sinAmpAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), "sinAmp", *sineOSC);
    sawAmpAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), "sawAmp", *sawOSC);
    sqrAmpAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), "sqrAmp", *sqrOSC);
    triAmpAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), "triAmp", *triOSC);
    rndAmpAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), "rndAmp", *noiseOSC);
    attackAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), "attack", *attackSlider);
    decayAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), "decay", *decaySlider);
    sustainAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), "sustain", *sustainSlider);
    releaseAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), "release", *releaseSlider);
    glideAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), "glide", *glideSlider);
    sinOctaveAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), "sinOctave", *sineOctaveSlider);
    sqrBandWidthAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), "sqrBandWidth", *sqrBandwidthSlider);
    //[/Constructor]
}

StsynthAudioProcessorEditor::~StsynthAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    envGroup = nullptr;
    oscSettingsGroup = nullptr;
    SinComponent = nullptr;
    attackSlider = nullptr;
    decaySlider = nullptr;
    sustainSlider = nullptr;
    releaseSlider = nullptr;
    attack = nullptr;
    decay = nullptr;
    sustain = nullptr;
    release = nullptr;
    oscmixerGroup = nullptr;
    sineOSC = nullptr;
    sawOSC = nullptr;
    sqrOSC = nullptr;
    triOSC = nullptr;
    noiseOSC = nullptr;
    sineLabel = nullptr;
    sawLabel = nullptr;
    sqrLabel = nullptr;
    triLabel = nullptr;
    noiseLabel = nullptr;
    sineOctaveLabel = nullptr;
    sineOctaveSlider = nullptr;
    sineOctaveLabel1 = nullptr;
    sineOctaveLabel2 = nullptr;
    sqrComponent = nullptr;
    sqrBandwidthLabel = nullptr;
    sqrBandwidthSlider = nullptr;
    filterGroup = nullptr;
    cutoffSlider = nullptr;
    cutOffLabel = nullptr;
    resonanceSlider = nullptr;
    resonanceLabel = nullptr;
    lowpassToggle = nullptr;
    highpassToggle = nullptr;
    bandpassToggle = nullptr;
    glideLabel = nullptr;
    glideSlider = nullptr;
    lfoGroup = nullptr;
    lfoPitchSlider = nullptr;
    lfoAmpSlider = nullptr;
    lfoPitchLabel = nullptr;
    lfoAmpLabel = nullptr;
    lfoSinToggle = nullptr;
    lfoTriToggle = nullptr;
    lfoSawToggle = nullptr;
    lfoSqrToggle = nullptr;
    lfoRndToggle = nullptr;
    cutoffToggle = nullptr;
    resonanceToggle = nullptr;
    volumeToggle = nullptr;
    notchFilterToggle = nullptr;
    masterVolumeSlider = nullptr;
    masterVolumeLabel = nullptr;
    lfoOffToggle = nullptr;
    kbdTrackingToggle = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void StsynthAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff666464));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void StsynthAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    envGroup->setBounds (200, 164, 110, 152);
    oscSettingsGroup->setBounds (24, 32, 168, 120);
    SinComponent->setBounds (71, 55, 56, 80);
    attackSlider->setBounds (213, 191, 32, 40);
    decaySlider->setBounds (261, 191, 32, 40);
    sustainSlider->setBounds (213, 239, 32, 40);
    releaseSlider->setBounds (261, 239, 32, 40);
    attack->setBounds (205, 227, 48, 16);
    decay->setBounds (253, 227, 48, 16);
    sustain->setBounds (205, 275, 48, 16);
    release->setBounds (253, 275, 48, 16);
    oscmixerGroup->setBounds (36, 164, 155, 152);
    sineOSC->setBounds (48, 180, 24, 112);
    sawOSC->setBounds (76, 180, 24, 112);
    sqrOSC->setBounds (103, 180, 24, 112);
    triOSC->setBounds (130, 180, 24, 112);
    noiseOSC->setBounds (158, 180, 24, 112);
    sineLabel->setBounds (48, 292, 24, 16);
    sawLabel->setBounds (76, 292, 24, 16);
    sqrLabel->setBounds (103, 292, 24, 16);
    triLabel->setBounds (130, 292, 24, 16);
    noiseLabel->setBounds (158, 292, 24, 16);
    sineOctaveLabel->setBounds (79, 109, 40, 16);
    sineOctaveSlider->setBounds (82, 76, 32, 32);
    sineOctaveLabel1->setBounds (74, 103, 16, 8);
    sineOctaveLabel2->setBounds (105, 103, 22, 8);
    sqrComponent->setBounds (130, 55, 56, 80);
    sqrBandwidthLabel->setBounds (126, 109, 64, 18);
    sqrBandwidthSlider->setBounds (141, 76, 32, 32);
    filterGroup->setBounds (200, 32, 120, 120);
    cutoffSlider->setBounds (214, 48, 32, 32);
    cutOffLabel->setBounds (210, 77, 40, 16);
    resonanceSlider->setBounds (267, 48, 32, 32);
    resonanceLabel->setBounds (258, 77, 52, 16);
    lowpassToggle->setBounds (216, 93, 40, 16);
    highpassToggle->setBounds (216, 109, 40, 16);
    bandpassToggle->setBounds (264, 93, 48, 16);
    glideLabel->setBounds (30, 109, 40, 16);
    glideSlider->setBounds (33, 76, 32, 32);
    lfoGroup->setBounds (32, 331, 185, 125);
    lfoPitchSlider->setBounds (94, 348, 32, 40);
    lfoAmpSlider->setBounds (94, 396, 32, 40);
    lfoPitchLabel->setBounds (86, 384, 48, 16);
    lfoAmpLabel->setBounds (86, 432, 48, 16);
    lfoSinToggle->setBounds (40, 352, 48, 16);
    lfoTriToggle->setBounds (40, 372, 48, 16);
    lfoSawToggle->setBounds (40, 390, 48, 16);
    lfoSqrToggle->setBounds (40, 409, 48, 16);
    lfoRndToggle->setBounds (40, 427, 48, 16);
    cutoffToggle->setBounds (137, 377, 56, 16);
    resonanceToggle->setBounds (137, 401, 72, 16);
    volumeToggle->setBounds (137, 425, 72, 16);
    notchFilterToggle->setBounds (264, 109, 48, 16);
    masterVolumeSlider->setBounds (256, 338, 40, 48);
    masterVolumeLabel->setBounds (252, 384, 48, 16);
    lfoOffToggle->setBounds (137, 353, 72, 16);
    kbdTrackingToggle->setBounds (216, 128, 88, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void StsynthAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == attackSlider)
    {
        //[UserSliderCode_attackSlider] -- add your slider handling code here..
        //[/UserSliderCode_attackSlider]
    }
    else if (sliderThatWasMoved == decaySlider)
    {
        //[UserSliderCode_decaySlider] -- add your slider handling code here..
        //[/UserSliderCode_decaySlider]
    }
    else if (sliderThatWasMoved == sustainSlider)
    {
        //[UserSliderCode_sustainSlider] -- add your slider handling code here..
        //[/UserSliderCode_sustainSlider]
    }
    else if (sliderThatWasMoved == releaseSlider)
    {
        //[UserSliderCode_releaseSlider] -- add your slider handling code here..
        //[/UserSliderCode_releaseSlider]
    }
    else if (sliderThatWasMoved == sineOSC)
    {
        //[UserSliderCode_sineOSC] -- add your slider handling code here..
        //[/UserSliderCode_sineOSC]
    }
    else if (sliderThatWasMoved == sawOSC)
    {
        //[UserSliderCode_sawOSC] -- add your slider handling code here..
        //[/UserSliderCode_sawOSC]
    }
    else if (sliderThatWasMoved == sqrOSC)
    {
        //[UserSliderCode_sqrOSC] -- add your slider handling code here..
        //[/UserSliderCode_sqrOSC]
    }
    else if (sliderThatWasMoved == triOSC)
    {
        //[UserSliderCode_triOSC] -- add your slider handling code here..
        //[/UserSliderCode_triOSC]
    }
    else if (sliderThatWasMoved == noiseOSC)
    {
        //[UserSliderCode_noiseOSC] -- add your slider handling code here..
        //[/UserSliderCode_noiseOSC]
    }
    else if (sliderThatWasMoved == sineOctaveSlider)
    {
        //[UserSliderCode_sineOctaveSlider] -- add your slider handling code here..
        //[/UserSliderCode_sineOctaveSlider]
    }
    else if (sliderThatWasMoved == sqrBandwidthSlider)
    {
        //[UserSliderCode_sqrBandwidthSlider] -- add your slider handling code here..
        //[/UserSliderCode_sqrBandwidthSlider]
    }
    else if (sliderThatWasMoved == cutoffSlider)
    {
        //[UserSliderCode_cutoffSlider] -- add your slider handling code here..
        //[/UserSliderCode_cutoffSlider]
    }
    else if (sliderThatWasMoved == resonanceSlider)
    {
        //[UserSliderCode_resonanceSlider] -- add your slider handling code here..
        //[/UserSliderCode_resonanceSlider]
    }
    else if (sliderThatWasMoved == glideSlider)
    {
        //[UserSliderCode_glideSlider] -- add your slider handling code here..
        //[/UserSliderCode_glideSlider]
    }
    else if (sliderThatWasMoved == lfoPitchSlider)
    {
        //[UserSliderCode_lfoPitchSlider] -- add your slider handling code here..
        //[/UserSliderCode_lfoPitchSlider]
    }
    else if (sliderThatWasMoved == lfoAmpSlider)
    {
        //[UserSliderCode_lfoAmpSlider] -- add your slider handling code here..
        //[/UserSliderCode_lfoAmpSlider]
    }
    else if (sliderThatWasMoved == masterVolumeSlider)
    {
        //[UserSliderCode_masterVolumeSlider] -- add your slider handling code here..
        //[/UserSliderCode_masterVolumeSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void StsynthAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == lowpassToggle)
    {
        //[UserButtonCode_lowpassToggle] -- add your button handler code here..
        processor.setParameterNotifyingHost(3, 0);
        //[/UserButtonCode_lowpassToggle]
    }
    else if (buttonThatWasClicked == highpassToggle)
    {
        //[UserButtonCode_highpassToggle] -- add your button handler code here..
        processor.setParameterNotifyingHost(3, 0.25);
        //[/UserButtonCode_highpassToggle]
    }
    else if (buttonThatWasClicked == bandpassToggle)
    {
        //[UserButtonCode_bandpassToggle] -- add your button handler code here..
        processor.setParameterNotifyingHost(3, 0.5);
        //[/UserButtonCode_bandpassToggle]
    }
    else if (buttonThatWasClicked == lfoSinToggle)
    {
        //[UserButtonCode_lfoSinToggle] -- add your button handler code here..
        processor.setParameterNotifyingHost(2, 0.2);
        //[/UserButtonCode_lfoSinToggle]
    }
    else if (buttonThatWasClicked == lfoTriToggle)
    {
        //[UserButtonCode_lfoTriToggle] -- add your button handler code here..
        processor.setParameterNotifyingHost(2, 0.4);
        //[/UserButtonCode_lfoTriToggle]
    }
    else if (buttonThatWasClicked == lfoSawToggle)
    {
        //[UserButtonCode_lfoSawToggle] -- add your button handler code here..
        processor.setParameterNotifyingHost(2, 0.6);
        //[/UserButtonCode_lfoSawToggle]
    }
    else if (buttonThatWasClicked == lfoSqrToggle)
    {
        //[UserButtonCode_lfoSqrToggle] -- add your button handler code here..
        processor.setParameterNotifyingHost(2, 0.8);
        //[/UserButtonCode_lfoSqrToggle]
    }
    else if (buttonThatWasClicked == lfoRndToggle)
    {
        //[UserButtonCode_lfoRndToggle] -- add your button handler code here..
        processor.setParameterNotifyingHost(2, 1);
        //[/UserButtonCode_lfoRndToggle]
    }
    else if (buttonThatWasClicked == cutoffToggle)
    {
        //[UserButtonCode_cutoffToggle] -- add your button handler code here..
        processor.setParameterNotifyingHost(1, 0.3);
        //[/UserButtonCode_cutoffToggle]
    }
    else if (buttonThatWasClicked == resonanceToggle)
    {
        //[UserButtonCode_resonanceToggle] -- add your button handler code here..
        processor.setParameterNotifyingHost(1, 0.6);
        //[/UserButtonCode_resonanceToggle]
    }
    else if (buttonThatWasClicked == volumeToggle)
    {
        //[UserButtonCode_volumeToggle] -- add your button handler code here..
        processor.setParameterNotifyingHost(1, 0.9);
        //[/UserButtonCode_volumeToggle]
    }
    else if (buttonThatWasClicked == notchFilterToggle)
    {
        //[UserButtonCode_notchFilterToggle] -- add your button handler code here..
        processor.setParameterNotifyingHost(3, 0.9);
        //[/UserButtonCode_notchFilterToggle]
    }
    else if (buttonThatWasClicked == lfoOffToggle)
    {
        //[UserButtonCode_lfoOffToggle] -- add your button handler code here..
        processor.setParameterNotifyingHost(1, 0);
        //[/UserButtonCode_lfoOffToggle]
    }
    else if (buttonThatWasClicked == kbdTrackingToggle)
    {
        //[UserButtonCode_kbdTrackingToggle] -- add your button handler code here..

    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="StsynthAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, private Timer"
                 constructorParams="StsynthAudioProcessor&amp;" variableInitialisers="AudioProcessorEditor (&amp;p), processor(p)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="350" initialHeight="500">
  <BACKGROUND backgroundColour="ff666464"/>
  <GROUPCOMPONENT name="envGroup" id="4088f0c29611e662" memberName="envGroup" virtualName="GroupComponent"
                  explicitFocusOrder="0" pos="200 164 110 152" outlinecol="ffffffff"
                  textcol="ffffffff" title="Env" textpos="36"/>
  <GROUPCOMPONENT name="OSCSettings" id="17a9e69ba2533fb" memberName="oscSettingsGroup"
                  virtualName="" explicitFocusOrder="0" pos="24 32 168 120" outlinecol="ffffffff"
                  textcol="ffffffff" title="OSC Settings" textpos="36"/>
  <GROUPCOMPONENT name="SinComponent" id="1dccf6fdd26f7805" memberName="SinComponent"
                  virtualName="" explicitFocusOrder="0" pos="71 55 56 80" outlinecol="aaffffff"
                  textcol="dfffffff" title="Sin" textpos="36"/>
  <SLIDER name="attack Slider" id="ad31dbd5baaf13d6" memberName="attackSlider"
          virtualName="" explicitFocusOrder="0" pos="213 191 32 40" rotarysliderfill="7fe1f3bf"
          rotaryslideroutline="ffffffff" min="1" max="2000" int="0" style="Rotary"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="decay Slider" id="cee6fa65397e679e" memberName="decaySlider"
          virtualName="" explicitFocusOrder="0" pos="261 191 32 40" rotarysliderfill="7fe1f3bf"
          rotaryslideroutline="ffffffff" min="1" max="2000" int="0" style="Rotary"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="sustainSlider" id="959fe0ff8d9f184" memberName="sustainSlider"
          virtualName="" explicitFocusOrder="0" pos="213 239 32 40" rotarysliderfill="7fe1f3bf"
          rotaryslideroutline="ffffffff" min="0" max="1" int="0" style="Rotary"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="releaseSlider" id="601800217da32f22" memberName="releaseSlider"
          virtualName="" explicitFocusOrder="0" pos="261 239 32 40" rotarysliderfill="7fe1f3bf"
          rotaryslideroutline="ffffffff" min="1" max="2000" int="0" style="Rotary"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="attack" id="cabfe2e5dc482f97" memberName="attack" virtualName=""
         explicitFocusOrder="0" pos="205 227 48 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Attack" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <LABEL name="decay" id="2c9c93444904768f" memberName="decay" virtualName=""
         explicitFocusOrder="0" pos="253 227 48 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Decay" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <LABEL name="sustain" id="dfe4db4d36afc6e2" memberName="sustain" virtualName=""
         explicitFocusOrder="0" pos="205 275 48 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Sustain" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <LABEL name="release" id="6aff0e5786824dde" memberName="release" virtualName=""
         explicitFocusOrder="0" pos="253 275 48 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Release" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <GROUPCOMPONENT name="OSCmixer" id="e2b2058607f5c5ac" memberName="oscmixerGroup"
                  virtualName="GroupComponent" explicitFocusOrder="0" pos="36 164 155 152"
                  outlinecol="ffffffff" textcol="ffffffff" title="OSC Mixer" textpos="36"/>
  <SLIDER name="sineOSC" id="c9ff2e8ada25988a" memberName="sineOSC" virtualName="Slider"
          explicitFocusOrder="0" pos="48 180 24 112" min="0" max="0.4000000000000000222"
          int="0" style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="sawOSC" id="420e8662963638cf" memberName="sawOSC" virtualName="Slider"
          explicitFocusOrder="0" pos="76 180 24 112" min="0" max="0.4000000000000000222"
          int="0" style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="oscMixer" id="2778f14a8362a1a1" memberName="sqrOSC" virtualName="Slider"
          explicitFocusOrder="0" pos="103 180 24 112" min="0" max="0.4000000000000000222"
          int="0" style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="triOSC" id="63bcd22c4d060bb7" memberName="triOSC" virtualName="Slider"
          explicitFocusOrder="0" pos="130 180 24 112" min="0" max="0.4000000000000000222"
          int="0" style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="noiseOSC" id="ffa520aa0bea7044" memberName="noiseOSC" virtualName="Slider"
          explicitFocusOrder="0" pos="158 180 24 112" min="0" max="0.4000000000000000222"
          int="0" style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="sineLabel" id="e957a185fca926" memberName="sineLabel" virtualName="Label"
         explicitFocusOrder="0" pos="48 292 24 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Sin" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="11" bold="0" italic="0" justification="36"/>
  <LABEL name="sawLabel" id="10934f6002f8b836" memberName="sawLabel" virtualName="Label"
         explicitFocusOrder="0" pos="76 292 24 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Saw" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="11" bold="0" italic="0" justification="36"/>
  <LABEL name="sqrLabel" id="2347daa1f56eeba3" memberName="sqrLabel" virtualName="Label"
         explicitFocusOrder="0" pos="103 292 24 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Sqr" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="11" bold="0" italic="0" justification="36"/>
  <LABEL name="triLabel" id="9372091839491680" memberName="triLabel" virtualName="Label"
         explicitFocusOrder="0" pos="130 292 24 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Tri" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="11" bold="0" italic="0" justification="36"/>
  <LABEL name="noiseLabel" id="e04f34c428020e5b" memberName="noiseLabel"
         virtualName="Label" explicitFocusOrder="0" pos="158 292 24 16"
         textCol="ffffffff" edTextCol="ff000000" edBkgCol="0" labelText="Rnd"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="11" bold="0" italic="0" justification="36"/>
  <LABEL name="sineOctaveLabel" id="56a07b1315e92a9" memberName="sineOctaveLabel"
         virtualName="" explicitFocusOrder="0" pos="79 109 40 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Octave" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="sineOctaveSlider" id="9bf94c8a5f1fee21" memberName="sineOctaveSlider"
          virtualName="" explicitFocusOrder="0" pos="82 76 32 32" rotarysliderfill="7fe1f3bf"
          rotaryslideroutline="ffffffff" min="-2" max="0" int="1" style="RotaryHorizontalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="sineOctaveLabel1" id="cbb339fb20b90cca" memberName="sineOctaveLabel1"
         virtualName="" explicitFocusOrder="0" pos="74 103 16 8" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="-2" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="8" bold="0" italic="0" justification="33"/>
  <LABEL name="sineOctaveLabel2" id="b0bce4678b975462" memberName="sineOctaveLabel2"
         virtualName="" explicitFocusOrder="0" pos="105 103 22 8" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="8" bold="0" italic="0" justification="33"/>
  <GROUPCOMPONENT name="sqrComponent" id="947ac6d3e1c1af97" memberName="sqrComponent"
                  virtualName="" explicitFocusOrder="0" pos="130 55 56 80" outlinecol="aaffffff"
                  textcol="dfffffff" title="Sqr" textpos="36"/>
  <LABEL name="sqrBandwidthLabel" id="f53aabd28ebf8024" memberName="sqrBandwidthLabel"
         virtualName="" explicitFocusOrder="0" pos="126 109 64 18" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="BandWidth" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="sqrBandwidthSlider" id="bb0c3319c1f90cb2" memberName="sqrBandwidthSlider"
          virtualName="" explicitFocusOrder="0" pos="141 76 32 32" rotarysliderfill="7fe1f3bf"
          rotaryslideroutline="ffffffff" min="0.10000000000000000555" max="0.9000000000000000222"
          int="0" style="Rotary" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <GROUPCOMPONENT name="filterGroup" id="c252ddafae836e94" memberName="filterGroup"
                  virtualName="" explicitFocusOrder="0" pos="200 32 120 120" outlinecol="ffffffff"
                  textcol="ffffffff" title="OSC Settings" textpos="36"/>
  <SLIDER name="cutoffSlider" id="b8e0661058b0148c" memberName="cutoffSlider"
          virtualName="" explicitFocusOrder="0" pos="214 48 32 32" rotarysliderfill="7fe1f3bf"
          rotaryslideroutline="ffffffff" min="20" max="20000" int="0" style="Rotary"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="curOffLabel" id="baab004441c0cbdd" memberName="cutOffLabel"
         virtualName="" explicitFocusOrder="0" pos="210 77 40 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Cutoff" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="resonanceSlider" id="e3008fe5b6ab4189" memberName="resonanceSlider"
          virtualName="" explicitFocusOrder="0" pos="267 48 32 32" rotarysliderfill="7fe1f3bf"
          rotaryslideroutline="ffffffff" min="0.97999999999999998224" max="99"
          int="0" style="Rotary" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="resonanceLabel" id="4ff348685dd566ac" memberName="resonanceLabel"
         virtualName="" explicitFocusOrder="0" pos="258 77 52 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Resonance" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <TOGGLEBUTTON name="lowpassToggle" id="25a2f2b17613d217" memberName="lowpassToggle"
                virtualName="" explicitFocusOrder="0" pos="216 93 40 16" txtcol="ffffffff"
                buttonText="LP" connectedEdges="0" needsCallback="1" radioGroupId="1"
                state="0"/>
  <TOGGLEBUTTON name="highpassToggle" id="7e5677583c98a4da" memberName="highpassToggle"
                virtualName="" explicitFocusOrder="0" pos="216 109 40 16" txtcol="ffffffff"
                buttonText="HP" connectedEdges="0" needsCallback="1" radioGroupId="1"
                state="0"/>
  <TOGGLEBUTTON name="bandpassToggle" id="645a5339dfbbfdad" memberName="bandpassToggle"
                virtualName="" explicitFocusOrder="0" pos="264 93 48 16" txtcol="ffffffff"
                buttonText="BP" connectedEdges="0" needsCallback="1" radioGroupId="1"
                state="0"/>
  <LABEL name="glideLabel" id="40b2a4de60132494" memberName="glideLabel"
         virtualName="" explicitFocusOrder="0" pos="30 109 40 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Glide" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="glideSlider" id="f7238a9ef9ed38d6" memberName="glideSlider"
          virtualName="" explicitFocusOrder="0" pos="33 76 32 32" rotarysliderfill="7fe1f3bf"
          rotaryslideroutline="ffffffff" min="0" max="100" int="0" style="Rotary"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <GROUPCOMPONENT name="lfoGroup" id="3acd1da802f701c8" memberName="lfoGroup" virtualName="GroupComponent"
                  explicitFocusOrder="0" pos="32 331 185 125" outlinecol="ffffffff"
                  textcol="ffffffff" title="LFO" textpos="36"/>
  <SLIDER name="lfoPitchSlider" id="c6a00ad2d0f29929" memberName="lfoPitchSlider"
          virtualName="" explicitFocusOrder="0" pos="94 348 32 40" rotarysliderfill="7fe1f3bf"
          rotaryslideroutline="ffffffff" min="0.5" max="20" int="0" style="Rotary"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="lfoAmpSlider" id="9eb45af18f30d096" memberName="lfoAmpSlider"
          virtualName="" explicitFocusOrder="0" pos="94 396 32 40" rotarysliderfill="7fe1f3bf"
          rotaryslideroutline="ffffffff" min="0" max="1" int="0" style="Rotary"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="lfoPitchLabel" id="cec5c0229c3f819f" memberName="lfoPitchLabel"
         virtualName="" explicitFocusOrder="0" pos="86 384 48 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Freq" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <LABEL name="lfoAmpLabel" id="fe45784ae5e34050" memberName="lfoAmpLabel"
         virtualName="" explicitFocusOrder="0" pos="86 432 48 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Amp" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <TOGGLEBUTTON name="lfoSinToggle" id="1383c22bad21eb6" memberName="lfoSinToggle"
                virtualName="" explicitFocusOrder="0" pos="40 352 48 16" txtcol="ffffffff"
                buttonText="Sin" connectedEdges="0" needsCallback="1" radioGroupId="2"
                state="0"/>
  <TOGGLEBUTTON name="lfoTriToggle" id="fd8594741645b008" memberName="lfoTriToggle"
                virtualName="" explicitFocusOrder="0" pos="40 372 48 16" txtcol="ffffffff"
                buttonText="Tri" connectedEdges="0" needsCallback="1" radioGroupId="2"
                state="0"/>
  <TOGGLEBUTTON name="lfoSawToggle" id="361b8b96fd58a4a1" memberName="lfoSawToggle"
                virtualName="" explicitFocusOrder="0" pos="40 390 48 16" txtcol="ffffffff"
                buttonText="Saw" connectedEdges="0" needsCallback="1" radioGroupId="2"
                state="0"/>
  <TOGGLEBUTTON name="lfoSqrToggle" id="3e2eb4f69efffaa" memberName="lfoSqrToggle"
                virtualName="" explicitFocusOrder="0" pos="40 409 48 16" txtcol="ffffffff"
                buttonText="Sqr" connectedEdges="0" needsCallback="1" radioGroupId="2"
                state="0"/>
  <TOGGLEBUTTON name="lfoRndToggle" id="9312e78e1fb8af77" memberName="lfoRndToggle"
                virtualName="" explicitFocusOrder="0" pos="40 427 48 16" txtcol="ffffffff"
                buttonText="Rnd" connectedEdges="0" needsCallback="1" radioGroupId="2"
                state="0"/>
  <TOGGLEBUTTON name="cutoffToggle" id="84e0afe70e5868e5" memberName="cutoffToggle"
                virtualName="" explicitFocusOrder="0" pos="137 377 56 16" txtcol="ffffffff"
                buttonText="Cutoff" connectedEdges="0" needsCallback="1" radioGroupId="3"
                state="0"/>
  <TOGGLEBUTTON name="resonanceToggle" id="90df508e073f805d" memberName="resonanceToggle"
                virtualName="" explicitFocusOrder="0" pos="137 401 72 16" txtcol="ffffffff"
                buttonText="Resonance" connectedEdges="0" needsCallback="1" radioGroupId="3"
                state="0"/>
  <TOGGLEBUTTON name="volumeToggle" id="47c152c5c2b91a90" memberName="volumeToggle"
                virtualName="" explicitFocusOrder="0" pos="137 425 72 16" txtcol="ffffffff"
                buttonText="DacVol" connectedEdges="0" needsCallback="1" radioGroupId="3"
                state="0"/>
  <TOGGLEBUTTON name="notchFilterToggle" id="4ba2579709d043c2" memberName="notchFilterToggle"
                virtualName="" explicitFocusOrder="0" pos="264 109 48 16" txtcol="ffffffff"
                buttonText="Notch" connectedEdges="0" needsCallback="1" radioGroupId="1"
                state="0"/>
  <SLIDER name="masterVolumeSlider" id="e586ced0676ad368" memberName="masterVolumeSlider"
          virtualName="" explicitFocusOrder="0" pos="256 338 40 48" rotarysliderfill="7fe1f3bf"
          rotaryslideroutline="ffffffff" min="0" max="1" int="0" style="Rotary"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="masterVolumeLabel" id="f4e9bc1751d7f74c" memberName="masterVolumeLabel"
         virtualName="" explicitFocusOrder="0" pos="252 384 48 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="DAC Vol" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <TOGGLEBUTTON name="lfoOffToggle" id="9b112f37d3a60be3" memberName="lfoOffToggle"
                virtualName="" explicitFocusOrder="0" pos="137 353 72 16" txtcol="ffffffff"
                buttonText="OFF" connectedEdges="0" needsCallback="1" radioGroupId="3"
                state="0"/>
  <TOGGLEBUTTON name="kbdTrackingToggle" id="12fd041de1d24c07" memberName="kbdTrackingToggle"
                virtualName="" explicitFocusOrder="0" pos="216 128 88 16" txtcol="ffffffff"
                buttonText="KBD Tracking" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
