/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
SimpleVerbAudioProcessorEditor::SimpleVerbAudioProcessorEditor(SimpleVerbAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p),
    dryWetSliderAttachement(audioProcessor.apvts, "Dry Wet", dryWetSlider),
    dampSliderAttachement(audioProcessor.apvts, "Damping", dampSlider),
    sizeSliderAttachement(audioProcessor.apvts, "Size", sizeSlider),
    widthSliderAttachement(audioProcessor.apvts, "Width", widthSlider),
    freezeButtonAttachement(audioProcessor.apvts, "Freeze", freezeButton)
{

    setSize (650, 200);

    setLookAndFeel(&customLNF);



    addAndMakeVisible(freezeButton);

    dryWetSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 70, 20);
    dryWetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(&dryWetSlider);

    dampSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 70, 20);
    dampSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(&dampSlider);

    sizeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 70, 20);
    sizeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(&sizeSlider);

    widthSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 70, 20);
    widthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(&widthSlider);

}

SimpleVerbAudioProcessorEditor::~SimpleVerbAudioProcessorEditor()
{
}

//==============================================================================
void SimpleVerbAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)

    g.fillAll(juce::Colour::fromRGB(30, 30, 30));

    g.setColour(juce::Colours::white);
    g.setFont(30.f);
    g.drawText("SimpleVerb", juce::Rectangle<float>(220, 20, 200, 20), juce::Justification::centred);

    g.setFont(15.f);
    g.drawText("Width", juce::Rectangle<float>(45, 60, 70, 20), juce::Justification::centred);
    g.drawText("Damping", juce::Rectangle<float>(175, 60, 70, 20), juce::Justification::centred);
    g.drawText("Size", juce::Rectangle<float>(405, 60, 70, 20), juce::Justification::centred);
    g.drawText("DryWet", juce::Rectangle<float>(535, 60, 70, 20), juce::Justification::centred);

   /* auto value = juce::String(audioProcessor.apvts.getRawParameterValue("Freeze")->load());
    g.drawText(value, juce::Rectangle<float>(280, 150, 70, 20), juce::Justification::centred);*/
}

void SimpleVerbAudioProcessorEditor::resized()
{
    freezeButton.setBounds(285, 100, 77.76, 30.72);

    widthSlider.setBounds(30, 80, 100, 100);
    dampSlider.setBounds(160, 80, 100, 100);
    sizeSlider.setBounds(390, 80, 100, 100);
    dryWetSlider.setBounds(520, 80, 100, 100);
}


void SimpleVerbAudioProcessorEditor::buttonClicked(juce::Button*) {

    repaint();
   
}