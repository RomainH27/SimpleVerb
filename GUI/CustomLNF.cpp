/*
  ==============================================================================

    CustomLNF.cpp
    Created: 13 Jun 2023 6:57:00pm
    Author:  romai

  ==============================================================================
*/

#include "CustomLNF.h"


void  CustomLNF::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
    const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider)
{

    auto sliderBounds = juce::Rectangle<int>(x, y, width, height).toFloat().reduced(10);

    auto bounds = juce::Rectangle<int>(x, y, width, height-15).toFloat().reduced(10);


    auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto lineW = 3.5f;
    auto arcRadius = radius - lineW * 0.5f;


    g.setColour(juce::Colour::fromRGB(37, 36, 39));
    juce::Path midCircle;
    int xCircle = x + bounds.getCentreX() - (radius)+lineW;
    int yCircle = x + bounds.getCentreY() - (radius)+lineW;
    int radiusCircle = (radius * 2) - (lineW * 2);
    midCircle.addRoundedRectangle(juce::Rectangle(xCircle, yCircle, radiusCircle + 1, radiusCircle + 1), 35);
    g.fillPath(midCircle);



    juce::Path backgroundArc;
    backgroundArc.addCentredArc(bounds.getCentreX(),
        bounds.getCentreY(),
        arcRadius,
        arcRadius,
        0.0f,
        rotaryStartAngle,
        rotaryEndAngle,
        true);

    g.setColour(juce::Colours::black);
    g.strokePath(backgroundArc, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

    if (slider.isEnabled())
    {
        juce::Path valueArc;
        valueArc.addCentredArc(bounds.getCentreX(),
            bounds.getCentreY(),
            arcRadius,
            arcRadius,
            0.0f,
            rotaryStartAngle,
            toAngle,
            true);

        g.setColour(juce::Colours::aqua);
        g.strokePath(valueArc, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    }

    auto thumbWidth = lineW * 2.0f;
    juce::Point<float> thumbPoint(bounds.getCentreX() + arcRadius * std::cos(toAngle - juce::MathConstants<float>::halfPi),
        bounds.getCentreY() + arcRadius * std::sin(toAngle - juce::MathConstants<float>::halfPi));

    g.setColour(juce::Colours::white);

    g.drawLine(thumbPoint.getX(), thumbPoint.getY(), bounds.getCentreX() + (arcRadius / 2) * std::cos(toAngle - juce::MathConstants<float>::halfPi),
        bounds.getCentreY() + (arcRadius / 2) * std::sin(toAngle - juce::MathConstants<float>::halfPi), 3.0f);

    juce::Rectangle<float> textRect;
    textRect.setBounds(10, height-25, width-20, 20);

    auto text = juce::String(slider.getValue());
    g.setFont(15.f);
    g.drawText(text, textRect, juce::Justification::centred);

}

void CustomLNF::drawToggleButton(juce::Graphics& g, juce::ToggleButton& toggleButton, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    
    auto bounds = toggleButton.getLocalBounds();
    //g.drawRect(bounds);

    if (toggleButton.getToggleState()) {
        g.drawImage(clickedImage, juce::Rectangle<float>(bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight()));

    }
    else {
        g.drawImage(normalImage, juce::Rectangle<float>(bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight()));

    }
}
