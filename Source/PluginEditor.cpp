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

    setSize (669, 203);

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
    g.drawImage( image,0,0,669,203,0,0,669,203);

    g.setFont(myCustomTypeface);
    g.setColour(juce::Colours::white);
    g.setFont(30.f);
    g.drawText("simple", juce::Rectangle<float>(180, 20, 200, 20), juce::Justification::centred);

    g.setColour(juce::Colour::fromRGB(0,111,251));
    g.drawText("Verb", juce::Rectangle<float>(343, 20, 100, 20), juce::Justification::centred);

    g.setColour(juce::Colours::white);
    g.setFont(10.f);
    g.drawText("Width", juce::Rectangle<float>(73, 160, 50, 20), juce::Justification::centred);
    g.drawText("dAmpinG", juce::Rectangle<float>(185, 160, 60, 20), juce::Justification::centred);
    g.drawText("fReeze", juce::Rectangle<float>(315, 160, 50, 20), juce::Justification::centred);
    g.drawText("siZe", juce::Rectangle<float>(445, 160, 50, 20), juce::Justification::centred);
    g.drawText("dry/Wet", juce::Rectangle<float>(560, 160, 60, 20), juce::Justification::centred);


}

void SimpleVerbAudioProcessorEditor::resized()
{
    freezeButton.setBounds(308, 100, 65, 30);

    widthSlider.setBounds(51, 72, 94, 94);
    dampSlider.setBounds(168, 72, 94, 94);
    sizeSlider.setBounds(423, 72, 94, 94);
    dryWetSlider.setBounds(540, 72, 94, 94);
}


void SimpleVerbAudioProcessorEditor::buttonClicked(juce::Button*) {

    repaint();
   
}