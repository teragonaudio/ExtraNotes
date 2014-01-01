/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef __PLUGINPROCESSOR_H_FA874118__
#define __PLUGINPROCESSOR_H_FA874118__

#include "../JuceLibraryCode/JuceHeader.h"
#include "TeragonPluginBase.h"
#include "PluginParameters.h"

using namespace teragon;

class ExtraNotesAudioProcessor : public TeragonPluginBase, public ParameterObserver {
public:
    ExtraNotesAudioProcessor();
    ~ExtraNotesAudioProcessor() {}

    AudioProcessorEditor *createEditor();
    const String getName() const { return JucePlugin_Name; }

    // PluginParameterObserver methods
    virtual bool isRealtimePriority() const { return true; }
    virtual void onParameterUpdated(const Parameter *parameter);

private:
    const String getDefaultText();

private:
    StringParameter *editorText;
    BlobParameter *editorImage;
    BooleanParameter *editText;
    BooleanParameter *editImage;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ExtraNotesAudioProcessor)
};

#endif  // __PLUGINPROCESSOR_H_FA874118__
