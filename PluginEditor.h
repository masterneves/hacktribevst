#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class HacktribeAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                        private juce::Timer
{
public:
    HacktribeAudioProcessorEditor (HacktribeAudioProcessor&);
    ~HacktribeAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void timerCallback() override;

    HacktribeAudioProcessor& audioProcessor;

    // Componentes Visuais estilo Electribe 2
    juce::Label titleLabel;
    juce::TextButton pads[16];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HacktribeAudioProcessorEditor)
};
