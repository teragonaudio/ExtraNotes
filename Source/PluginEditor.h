/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  17 Mar 2013 5:26:25pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_EXTRANOTESAUDIOPROCESSOREDITOR_PLUGINEDITOR_7580BDA__
#define __JUCER_HEADER_EXTRANOTESAUDIOPROCESSOREDITOR_PLUGINEDITOR_7580BDA__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ExtraNotesAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    //==============================================================================
    ExtraNotesAudioProcessorEditor (ExtraNotesAudioProcessor *ownerFilter);
    ~ExtraNotesAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    String getEditorText() const { return textEditor->getText(); }
    void setEditorText(const String& text) { textEditor->setText(text); }
    void setEditorListener(TextEditor::Listener *listener) { textEditor->addListener(listener); }
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    TextEditor* textEditor;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ExtraNotesAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCER_HEADER_EXTRANOTESAUDIOPROCESSOREDITOR_PLUGINEDITOR_7580BDA__
