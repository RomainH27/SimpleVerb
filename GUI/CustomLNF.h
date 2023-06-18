/*
  ==============================================================================

    CustomLNF.h
    Created: 13 Jun 2023 6:57:00pm
    Author:  romai

  ==============================================================================
*/

#include <JuceHeader.h>
#pragma once

//==============================================================================

class CustomLNF : public juce::LookAndFeel_V4 {

public:
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override;

    void drawToggleButton(juce::Graphics& g, juce::ToggleButton& toggleButton,
        bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

    juce::Image normalImage = juce::ImageCache::getFromMemory(BinaryData::Normal_png, BinaryData::Normal_pngSize);
    juce::Image clickedImage = juce::ImageCache::getFromMemory(BinaryData::Freeze_png, BinaryData::Freeze_pngSize);

private:

    

};