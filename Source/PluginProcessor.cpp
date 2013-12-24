/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

static const char *kEditorTextAttributeName = "EditorText";

ExtraNotesAudioProcessor::ExtraNotesAudioProcessor() {

}

void ExtraNotesAudioProcessor::processBlock(AudioSampleBuffer &buffer, MidiBuffer &midiMessages) {
    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for(int i = getNumInputChannels(); i < getNumOutputChannels(); ++i) {
        buffer.clear(i, 0, buffer.getNumSamples());
    }
}

AudioProcessorEditor *ExtraNotesAudioProcessor::createEditor() {
    ExtraNotesAudioProcessorEditor *editor = new ExtraNotesAudioProcessorEditor (this);
    editor->setEditorListener(this);
    editor->setEditorText(editorText);
    return editor;
}

void ExtraNotesAudioProcessor::textEditorTextChanged(TextEditor &textEditor) {
    editorText = textEditor.getText();
}

float ExtraNotesAudioProcessor::getParameter(int index) {
    return 0;
}

int ExtraNotesAudioProcessor::getNumParameters() {
    return 0;
}

void ExtraNotesAudioProcessor::setParameter(int index, float newValue) {

}

const String ExtraNotesAudioProcessor::getParameterName(int index) {
    return juce::String();
}

const String ExtraNotesAudioProcessor::getParameterText(int index) {
    return juce::String();
}

void ExtraNotesAudioProcessor::getStateInformation(MemoryBlock &destData) {
    XmlElement xml(getName());
    xml.setAttribute(kEditorTextAttributeName, editorText);
    copyXmlToBinary(xml, destData);
}

void ExtraNotesAudioProcessor::setStateInformation(const void *data, int sizeInBytes) {
    ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if(xmlState != 0 && xmlState->hasTagName(getName())) {
        if(xmlState->hasAttribute(kEditorTextAttributeName)) {
            editorText = xmlState->getStringAttribute(kEditorTextAttributeName);
        }
    }
}

AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
    return new ExtraNotesAudioProcessor();
}
