#include "PluginProcessor.h"
#include "PluginEditor.h"

HacktribeAudioProcessorEditor::HacktribeAudioProcessorEditor (HacktribeAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (800, 450);

    // Título
    titleLabel.setText ("HACKTRIBE E2 VST", juce::dontSendNotification);
    titleLabel.setFont (juce::Font (22.0f, juce::Font::bold));
    titleLabel.setJustificationType (juce::Justification::centredLeft);
    titleLabel.setColour (juce::Label::textColourId, juce::Colour (0xffe63946));
    addAndMakeVisible (titleLabel);

    // Criar os 16 Pads da Electribe
    for (int i = 0; i < 16; ++i)
    {
        pads[i].setButtonText (juce::String (i + 1));
        pads[i].setColour (juce::TextButton::buttonColourId, juce::Colour (0xff2b2d42));
        pads[i].setColour (juce::TextButton::buttonOnColourId, juce::Colour (0xffe63946));

        int stepIndex = i;
        pads[i].onClick = [this, stepIndex]()
        {
            audioProcessor.stepState[stepIndex] = !audioProcessor.stepState[stepIndex];
            pads[stepIndex].setToggleState (audioProcessor.stepState[stepIndex], juce::dontSendNotification);
        };

        addAndMakeVisible (pads[i]);
    }

    startTimerHz (30);
}

HacktribeAudioProcessorEditor::~HacktribeAudioProcessorEditor()
{
    stopTimer();
}

void HacktribeAudioProcessorEditor::paint (juce::Graphics& g)
{
    // Fundo metálico escuro da Electribe 2
    juce::ColourGradient bgGradient (juce::Colour (0xff1d3557), 0, 0,
                                     juce::Colour (0xff0f172a), 0, (float) getHeight(), false);
    g.setGradientFill (bgGradient);
    g.fillAll();

    // Moldura do painel
    g.setColour (juce::Colour (0xffe63946).withAlpha (0.4f));
    g.drawRect (getLocalBounds(), 2);

    // Área do Touchpad X/Y
    juce::Rectangle<float> xyArea (40.0f, 80.0f, 180.0f, 180.0f);
    g.setColour (juce::Colour (0xff111827));
    g.fillRoundedRectangle (xyArea, 8.0f);
    g.setColour (juce::Colour (0xff38bdf8));
    g.drawRoundedRectangle (xyArea, 8.0f, 1.5f);
}

void HacktribeAudioProcessorEditor::resized()
{
    titleLabel.setBounds (40, 20, 300, 30);

    int padWidth = 40;
    int padHeight = 45;
    int startX = 260;
    int startY = 280;
    int gap = 8;

    for (int i = 0; i < 16; ++i)
    {
        int row = i / 8;
        int col = i % 8;
        pads[i].setBounds (startX + col * (padWidth + gap), startY + row * (padHeight + gap), padWidth, padHeight);
    }
}

void HacktribeAudioProcessorEditor::timerCallback()
{
}
