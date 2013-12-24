/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_173BA1F56A32FA20__
#define __JUCE_HEADER_173BA1F56A32FA20__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "TeragonGuiComponents.h"
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
    ExtraNotesAudioProcessorEditor (AudioProcessor *ownerFilter, teragon::ThreadsafePluginParameterSet &p, teragon::ResourceCache *r);
    ~ExtraNotesAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    String getEditorText() const { return textEditor->getText(); }
    void setEditorText(const String& text) { textEditor->setText(text); }
    void setEditorListener(TextEditor::Listener *listener) { textEditor->addListener(listener); }
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();

    // Binary resources:
    static const char* background_png;
    static const int background_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    teragon::ThreadsafePluginParameterSet &parameters;
    teragon::ResourceCache *resources;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextEditor> textEditor;
    ScopedPointer<teragon::IndicatorLight> modifiedLight;
    ScopedPointer<teragon::PushButton> editTextButton;
    ScopedPointer<teragon::PushButton> editImageButton;
    ScopedPointer<teragon::ToggleButton> loadImageButton;
    ScopedPointer<teragon::ToggleButton> clearImageButton;
    ScopedPointer<teragon::StatusBar> statusBar;
    ScopedPointer<teragon::ParameterLabel> versionLabel;
    Image cachedImage_background_png;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ExtraNotesAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_173BA1F56A32FA20__
