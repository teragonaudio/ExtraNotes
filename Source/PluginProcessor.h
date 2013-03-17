/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef __PLUGINPROCESSOR_H_FA874118__
#define __PLUGINPROCESSOR_H_FA874118__

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/**
*/
class ExtraNotesAudioProcessor : public AudioProcessor, public TextEditor::Listener
{
public:
    //==============================================================================
    ExtraNotesAudioProcessor() {}
    ~ExtraNotesAudioProcessor() {}

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) {}
    void releaseResources() {}

    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

    //==============================================================================
    AudioProcessorEditor* createEditor();
    bool hasEditor() const { return true; }
    virtual void textEditorTextChanged (TextEditor &textEditor) { editorText = textEditor.getText(); }

    //==============================================================================
    const String getName() const { return JucePlugin_Name; }

    int getNumParameters() { return 0; }
    float getParameter (int index) { return 0.0; }
    void setParameter (int index, float newValue) {}

    const String getParameterName (int index) { return String::empty; }
    const String getParameterText (int index) { return String::empty; }

    const String getInputChannelName (int channelIndex) const { return String(channelIndex + 1); }
    const String getOutputChannelName (int channelIndex) const { return String(channelIndex + 1); }
    bool isInputChannelStereoPair (int index) const { return true; }
    bool isOutputChannelStereoPair (int index) const { return true; }

    bool acceptsMidi() const { return false; }
    bool producesMidi() const { return false; }
    bool silenceInProducesSilenceOut() const { return true; }
    double getTailLengthSeconds() const { return 0.0; }

    //==============================================================================
    int getNumPrograms() { return 0; }
    int getCurrentProgram() { return 0; }
    void setCurrentProgram (int index) {}
    const String getProgramName (int index) { return String::empty; }
    void changeProgramName (int index, const String& newName) {}

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

private:
    String editorText;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ExtraNotesAudioProcessor)
};

#endif  // __PLUGINPROCESSOR_H_FA874118__
