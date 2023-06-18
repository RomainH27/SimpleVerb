/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleVerbAudioProcessor::SimpleVerbAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ),
#endif
    apvts(*this, nullptr, ProjectInfo::projectName, createParameterLayout())
{
}

SimpleVerbAudioProcessor::~SimpleVerbAudioProcessor()
{
}

//==============================================================================
const juce::String SimpleVerbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SimpleVerbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SimpleVerbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SimpleVerbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SimpleVerbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SimpleVerbAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SimpleVerbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SimpleVerbAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SimpleVerbAudioProcessor::getProgramName (int index)
{
    return {};
}

void SimpleVerbAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SimpleVerbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    spec.numChannels = getTotalNumOutputChannels();
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;

    reverbDSP.reset();
    reverbDSP.prepare(spec);

}

void SimpleVerbAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SimpleVerbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void SimpleVerbAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    //===========================REVERB PARAMS================================
    dspParameters.damping = apvts.getRawParameterValue("Damping")->load() * 0.01f;
    dspParameters.roomSize = apvts.getRawParameterValue("Size")->load() * 0.01f;
    dspParameters.dryLevel = 1.0f - (apvts.getRawParameterValue("Dry Wet")->load() * 0.01f);
    dspParameters.wetLevel = apvts.getRawParameterValue("Dry Wet")->load() * 0.01f;
    dspParameters.freezeMode = apvts.getRawParameterValue("Freeze")->load();
    dspParameters.width = apvts.getRawParameterValue("Width")->load() * 0.01f;
        
    reverbDSP.setParameters(dspParameters);

    //==============================PROCESS================================
    juce::dsp::AudioBlock<float> block(buffer);
    
    reverbDSP.process(juce::dsp::ProcessContextReplacing<float>(block));
    block.multiplyBy(0.8);
}

//==============================================================================
bool SimpleVerbAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SimpleVerbAudioProcessor::createEditor()
{
    return new SimpleVerbAudioProcessorEditor (*this);
}

//==============================================================================
void SimpleVerbAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SimpleVerbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}



juce::AudioProcessorValueTreeState::ParameterLayout
SimpleVerbAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add(std::make_unique<juce::AudioParameterFloat>("Dry Wet",
                                                            "Dry Wet",
                                                            juce::NormalisableRange<float>(0.f, 100.f, 0.01f, 1.f),
                                                            50.f));

    layout.add(std::make_unique<juce::AudioParameterFloat>("Size",
                                                            "Size",
                                                            juce::NormalisableRange<float>(0.f, 100.f, 0.01f, 1.f),
                                                            50.f));
    
    layout.add(std::make_unique<juce::AudioParameterFloat>("Damping",
                                                            "Damping",
                                                            juce::NormalisableRange<float>(0.f, 100.f, 0.01f, 1.f),
                                                            50.f));

    layout.add(std::make_unique<juce::AudioParameterFloat>("Width",
                                                            "Width",
                                                            juce::NormalisableRange<float>(0.f, 100.f, 0.01f, 1.f),
                                                            50.f));

    layout.add(std::make_unique<juce::AudioParameterBool>("Freeze",
                                                         "Freeze", 
                                                            0.f));

    return layout;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleVerbAudioProcessor();
}
