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
AudioProcessor(), ParameterObserver() {
    editorText = new TextEditorParameter("Text", getDefaultText().toStdString().c_str());
    editorText->addObserver(this);
    parameters.add(editorText);

    editorImage = new BlobParameter("Image");
    parameters.add(editorImage);

    File defaultBrowseLocation = File::getSpecialLocation(File::userHomeDirectory);
    parameters.add(new StringParameter("Last Browse Location", defaultBrowseLocation.getFullPathName().toStdString()));

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
    // Start paused (should be done by default in PluginParameters?)
    parameters.pause();
}

const String ExtraNotesAudioProcessor::getDefaultText() {
    String result = "Click here to start a new note";
    PluginHostType hostType;
    bool testedHost = false;
    bool supportedOs = false;
    bool testedOs = false;
    bool knownProblemHost = false;

    switch(SystemStats::getOperatingSystemType()) {
        case SystemStats::OperatingSystemType::Linux:
            supportedOs = true;
            testedHost = false;
            testedOs = true;
            break;

        case SystemStats::OperatingSystemType::MacOSX_10_4:
        case SystemStats::OperatingSystemType::MacOSX_10_5:
        case SystemStats::OperatingSystemType::MacOSX_10_6:
            supportedOs = false;
            break;
        case SystemStats::OperatingSystemType::MacOSX_10_7:
            supportedOs = true;
            testedOs = false;
            break;
        case SystemStats::OperatingSystemType::MacOSX_10_8:
            supportedOs = true;
            testedOs = true;
            switch(hostType.type) {
                case PluginHostType::HostType::AbletonLiveGeneric:
                    testedHost = true;
                    break;
                default:
                    testedHost = false;
                    break;
            }
            break;

        case SystemStats::OperatingSystemType::Win2000:
        case SystemStats::OperatingSystemType::WinXP:
        case SystemStats::OperatingSystemType::WinVista:
            supportedOs = false;
            break;
        case SystemStats::OperatingSystemType::Windows7:
            supportedOs = true;
            switch(hostType.type) {
                case PluginHostType::HostType::AbletonLiveGeneric:
                    testedHost = true;
                    break;
                default:
                    testedHost = false;
                    break;
            }
            break;
        case SystemStats::OperatingSystemType::Windows8:
            supportedOs = true;
            testedOs = false;
            break;
        default:
            supportedOs = false;
            break;
    }

    if(knownProblemHost) {
        result += "\n\nSorry! This host is known to not work with ExtraNotes. :( We're working on a solution.";
    }
    else if(!supportedOs) {
        result += "\n\nThis operating system is not supported! You might experience problems with text input.";
    }
    else if(!testedHost) {
        result += "\n\nThis host is untested! Please email support@teragonaudio.com with your system stats to report success or failure with text input.";
    }
    else if(!testedOs) {
        result += "\n\nThis operating system is untested! Please email support@teragonaudio.com with your system stats to report success or failure with text input.";
    }

    return result;
}

void ExtraNotesAudioProcessor::prepareToPlay(double, int) {
    parameters.resume();
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

void ExtraNotesAudioProcessor::releaseResources() {
    parameters.pause();
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

void ExtraNotesAudioProcessor::onParameterUpdated(const Parameter *parameter) {
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
            parameters.setData(editorText, value.toStdString().c_str(), (const size_t)value.length());
            parameters.processRealtimeEvents();
        }
    }
}

AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
    return new ExtraNotesAudioProcessor();
}
