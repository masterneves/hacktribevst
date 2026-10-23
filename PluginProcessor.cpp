#include "PluginProcessor.h"
#include "PluginEditor.h"

HacktribeAudioProcessor::HacktribeAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
#endif
{
}

HacktribeAudioProcessor::~HacktribeAudioProcessor()
{
}

void HacktribeAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synthEngine.setCurrentPlaybackSampleRate (sampleRate);
}

void HacktribeAudioProcessor::releaseResources()
{
}

bool HacktribeAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    return true;
}

void HacktribeAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    buffer.clear();

    // Processa o motor de sintetizador e amostragem do Hacktribe
    synthEngine.renderNextBlock (buffer, midiMessages, 0, buffer.getNumSamples());
}

juce::AudioProcessorEditor* HacktribeAudioProcessor::createEditor()
{
    return new HacktribeAudioProcessorEditor (*this);
}

void HacktribeAudioProcessor::getStateInformation (juce::MemoryBlock& destData) {}
void HacktribeAudioProcessor::setStateInformation (const void* data, int sizeInBytes) {}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HacktribeAudioProcessor();
}
