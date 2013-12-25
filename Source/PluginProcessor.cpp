/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Resources.h"
#include "TextEditorParameter.h"

static const char *kEditorTextAttributeName = "EditorText";

ExtraNotesAudioProcessor::ExtraNotesAudioProcessor() :
AudioProcessor(), PluginParameterObserver() {
    editorText = new TextEditorParameter("Text", "Click here to start a new note");
    editorText->addObserver(this);
    parameters.add(editorText);

    // TODO: Remove this parameter
    parameters.add(new BooleanParameter("Modified"));

    editText = new BooleanParameter("Edit Text", true);
    editText->addObserver(this);
    parameters.add(editText);

    editImage = new BooleanParameter("Edit Image", false);
    editImage->addObserver(this);
    parameters.add(editImage);

    parameters.add(new VoidParameter("Load Item"));
    parameters.add(new VoidParameter("Clear Item"));
    parameters.add(new VoidParameter("Clear Cancelled"));
    parameters.add(new VoidParameter("Clear Confirmed"));

    ParameterString version = ProjectInfo::projectName;
    version.append(" version ").append(ProjectInfo::versionString);
    parameters.add(new StringParameter("Version", version));
}

void ExtraNotesAudioProcessor::processBlock(AudioSampleBuffer &buffer, MidiBuffer &midiMessages) {
    parameters.processRealtimeEvents();

    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for(int i = getNumInputChannels(); i < getNumOutputChannels(); ++i) {
        buffer.clear(i, 0, buffer.getNumSamples());
    }
}

AudioProcessorEditor *ExtraNotesAudioProcessor::createEditor() {
    return new ExtraNotesAudioProcessorEditor(this, parameters, Resources::getCache());
}

float ExtraNotesAudioProcessor::getParameter(int index) {
    return (float)parameters[index]->getScaledValue();
}

int ExtraNotesAudioProcessor::getNumParameters() {
    return parameters.size();
}

void ExtraNotesAudioProcessor::setParameter(int index, float newValue) {
    parameters.setScaled(index, newValue);
}

const String ExtraNotesAudioProcessor::getParameterName(int index) {
    return parameters[index]->getName();
}

const String ExtraNotesAudioProcessor::getParameterText(int index) {
    return parameters[index]->getDisplayText();
}

void ExtraNotesAudioProcessor::onParameterUpdated(const PluginParameter *parameter) {
    if(parameter->getName() == "Text") {
        printf("Text updated! %s\n", parameter->getDisplayText().c_str());
    }

    if(parameter->getName() == "Edit Text") {
        parameters.set("Edit Image", !parameter->getValue(), this);
    }
    else if(parameter->getName() == "Edit Image") {
        parameters.set("Edit Text", !parameter->getValue(), this);
    }
}

void ExtraNotesAudioProcessor::getStateInformation(MemoryBlock &destData) {
    XmlElement xml(getName());
    xml.setAttribute(kEditorTextAttributeName, editorText->getDisplayText());
    copyXmlToBinary(xml, destData);
}

void ExtraNotesAudioProcessor::setStateInformation(const void *data, int sizeInBytes) {
    ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if(xmlState != 0 && xmlState->hasTagName(getName())) {
        if(xmlState->hasAttribute(kEditorTextAttributeName)) {
            juce::String value = xmlState->getStringAttribute(kEditorTextAttributeName);
            parameters.set(editorText, value.toStdString());
            parameters.processRealtimeEvents();
        }
    }
}

AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
    return new ExtraNotesAudioProcessor();
}
