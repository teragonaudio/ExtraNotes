/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef __PLUGINPROCESSOR_H_FA874118__
#define __PLUGINPROCESSOR_H_FA874118__

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginParameters.h"

using namespace teragon;

class ExtraNotesAudioProcessor : public AudioProcessor, public PluginParameterObserver {
public:
    ExtraNotesAudioProcessor();
    ~ExtraNotesAudioProcessor() {}

    // Playback
    void prepareToPlay(double sampleRate, int samplesPerBlock) {}
    void releaseResources() {}
    void processBlock(AudioSampleBuffer &buffer, MidiBuffer &midiMessages);

    // Editor
    AudioProcessorEditor *createEditor();
    bool hasEditor() const { return true; }

    // Plugin configuration and information
    const String getName() const { return JucePlugin_Name; }
    const String getInputChannelName(int channelIndex) const { return String(channelIndex + 1); }
    const String getOutputChannelName(int channelIndex) const { return String(channelIndex + 1); }
    bool isInputChannelStereoPair(int index) const { return true; }
    bool isOutputChannelStereoPair(int index) const { return true; }
    bool acceptsMidi() const { return false; }
    bool producesMidi() const { return false; }
    bool silenceInProducesSilenceOut() const { return true; }
    double getTailLengthSeconds() const { return 0.0; }

    // Parameter handling
    float getParameter(int index);
    int getNumParameters();
    void setParameter(int index, float newValue);
    const String getParameterName(int index);
    const String getParameterText(int index);

    // Program handling (not used by this plugin)
    int getNumPrograms() { return 0; }
    int getCurrentProgram() { return 0; }
    void setCurrentProgram(int index) {}
    const String getProgramName(int index) { return String::empty; }
    void changeProgramName(int index, const String &newName) {}

    // State save/restore
    void getStateInformation(MemoryBlock &destData);
    void setStateInformation(const void *data, int sizeInBytes);

    // PluginParameterObserver methods
    virtual bool isRealtimePriority() const { return true; }
    virtual void onParameterUpdated(const PluginParameter *parameter);

private:
    ThreadsafePluginParameterSet parameters;
    StringParameter *editorText;
    BooleanParameter *editText;
    BooleanParameter *editImage;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ExtraNotesAudioProcessor)
};

#endif  // __PLUGINPROCESSOR_H_FA874118__
