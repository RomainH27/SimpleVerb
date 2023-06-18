/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "../GUI/CustomLNF.h"

//==============================================================================
/**
*/
class SimpleVerbAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Button::Listener
{
public:
    SimpleVerbAudioProcessorEditor (SimpleVerbAudioProcessor&);
    ~SimpleVerbAudioProcessorEditor() override;

    void buttonClicked(juce::Button*) override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    SimpleVerbAudioProcessor& audioProcessor;

    juce::ToggleButton freezeButton;

    juce::Slider dampSlider;
    juce::Slider dryWetSlider;
    juce::Slider sizeSlider;
    juce::Slider widthSlider;

    using Attachement = juce::AudioProcessorValueTreeState::SliderAttachment;

    Attachement dryWetSliderAttachement,
                dampSliderAttachement,
                widthSliderAttachement,
                sizeSliderAttachement;

    juce::AudioProcessorValueTreeState::ButtonAttachment freezeButtonAttachement;

    CustomLNF customLNF;

    juce::Image normalImage = juce::ImageCache::getFromMemory(BinaryData::Normal_png, BinaryData::Normal_pngSize);
    juce::Image clickedImage = juce::ImageCache::getFromMemory(BinaryData::Freeze_png, BinaryData::Freeze_pngSize);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleVerbAudioProcessorEditor)
};
