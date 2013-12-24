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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ExtraNotesAudioProcessorEditor::ExtraNotesAudioProcessorEditor (AudioProcessor *ownerFilter, teragon::ThreadsafePluginParameterSet &p, teragon::ResourceCache *r)
    : AudioProcessorEditor(ownerFilter), parameters(p), resources(r)
{
    addAndMakeVisible (textEditor = new TextEditor ("Text Editor"));
    textEditor->setMultiLine (true);
    textEditor->setReturnKeyStartsNewLine (true);
    textEditor->setReadOnly (false);
    textEditor->setScrollbarsShown (true);
    textEditor->setCaretVisible (true);
    textEditor->setPopupMenuEnabled (true);
    textEditor->setColour (TextEditor::backgroundColourId, Colours::white);
    textEditor->setColour (TextEditor::highlightColourId, Colour (0x40e66363));
    textEditor->setColour (TextEditor::shadowColourId, Colour (0x38cb0d0d));
    textEditor->setText (String::empty);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..

    // Disable that godawful light blue/purple color that Juce draws on this component's border
    textEditor->setColour(TextEditor::outlineColourId, Colours::transparentBlack);
    textEditor->setColour(TextEditor::focusedOutlineColourId, Colours::transparentBlack);
    textEditor->setColour(TextEditor::shadowColourId, Colours::transparentBlack);
    //[/Constructor]
}

ExtraNotesAudioProcessorEditor::~ExtraNotesAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    textEditor = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    delete resources;
    //[/Destructor]
}

//==============================================================================
void ExtraNotesAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xfdffffff));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ExtraNotesAudioProcessorEditor::resized()
{
    textEditor->setBounds (24, 16, proportionOfWidth (0.9200f), proportionOfHeight (0.9200f));
    //[UserResized] Add your own custom resize handling here..
    textEditor.get()->grabKeyboardFocus();
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ExtraNotesAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor"
                 constructorParams="AudioProcessor *ownerFilter, teragon::ThreadsafePluginParameterSet &amp;p, teragon::ResourceCache *r"
                 variableInitialisers="AudioProcessorEditor(ownerFilter), parameters(p), resources(r)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="fdffffff"/>
  <TEXTEDITOR name="Text Editor" id="ad4098c5c892dabd" memberName="textEditor"
              virtualName="" explicitFocusOrder="0" pos="24 16 92% 92%" bkgcol="ffffffff"
              hilitecol="40e66363" shadowcol="38cb0d0d" initialText="" multiline="1"
              retKeyStartsLine="1" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
