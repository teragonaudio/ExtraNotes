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
#include "Base64.h"

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
                case PluginHostType::HostType::AppleLogic:
                case PluginHostType::HostType::AbletonLiveGeneric:
                    testedHost = true;
                    break;
                case PluginHostType::HostType::Reaper:
                    knownProblemHost = true;
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
        result += "\n\nSorry! This host is known to have problems with ExtraNotes. :( We're working on a solution.";
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
    parameters.setScaled((const size_t)index, newValue);
}

const String ExtraNotesAudioProcessor::getParameterName(int index) {
    return parameters[index]->getName();
}

const String ExtraNotesAudioProcessor::getParameterText(int index) {
    return parameters[index]->getDisplayText();
}

void ExtraNotesAudioProcessor::onParameterUpdated(const Parameter *parameter) {
    // Switch tabs
    if(parameter->getName() == "Edit Text") {
        parameters.set("Edit Image", !parameter->getValue(), this);
    }
    else if(parameter->getName() == "Edit Image") {
        parameters.set("Edit Text", !parameter->getValue(), this);
    }
}

void ExtraNotesAudioProcessor::getStateInformation(MemoryBlock &destData) {
    XmlElement xml(getName());
    for(size_t i = 0; i < parameters.size(); ++i) {
        Parameter *parameter = parameters[i];
        const String attributeName = parameter->getSafeName();
        // Do not serialize the version parameter, it must be set by the plugin and not overridden
        if(attributeName == "Version") {
            continue;
        }

        if(dynamic_cast<StringParameter *>(parameter) != nullptr) {
            const String value = parameter->getDisplayText();
            xml.setAttribute(attributeName, value);
        }
        else if(dynamic_cast<BlobParameter *>(parameter) != nullptr) {
            BlobParameter *blobParameter = dynamic_cast<BlobParameter *>(parameter);
            size_t blobSize = blobParameter->getDataSize();
            char *encodedBlob = new char[base64_enc_len(blobSize)];
            base64_encode(encodedBlob, (char*)blobParameter->getData(), blobSize);
            xml.setAttribute(attributeName, encodedBlob);
            delete [] encodedBlob;
        }
        else if(dynamic_cast<IntegerParameter *>(parameter) != nullptr) {
            xml.setAttribute(attributeName, (int)parameter->getValue());
        }
        else {
            xml.setAttribute(attributeName, (double)parameter->getValue());
        }
    }

    copyXmlToBinary(xml, destData);
}

void ExtraNotesAudioProcessor::setStateInformation(const void *data, int sizeInBytes) {
    ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if(xmlState != 0 && xmlState->hasTagName(getName())) {
        for(size_t i = 0; i < parameters.size(); i++) {
            Parameter *parameter = parameters[i];
            const String attributeName = parameter->getSafeName();
            if(xmlState->hasAttribute(attributeName)) {
                if(dynamic_cast<StringParameter *>(parameter) != nullptr) {
                    juce::String value = xmlState->getStringAttribute(attributeName);
                    parameters.setData(parameter, value.toStdString().c_str(), (const size_t)value.length());
                }
                else if(dynamic_cast<BlobParameter *>(parameter) != nullptr) {
                    juce::String value = xmlState->getStringAttribute(attributeName);
                    char *rawValue = const_cast<char *>(value.toRawUTF8());
                    char *blob = new char[base64_dec_len(rawValue, value.length())];
                    int blobSize = base64_decode(blob, rawValue, value.length());
                    parameters.setData(parameter, blob, (const size_t)blobSize);
                    delete [] blob;
                }
                else if(dynamic_cast<IntegerParameter *>(parameter) != nullptr) {
                    parameters.set(parameter, xmlState->getIntAttribute(attributeName));
                }
                else {
                    parameters.set(parameter, xmlState->getDoubleAttribute(attributeName));
                }
            }
        }
        parameters.processRealtimeEvents();
    }
}

AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
    return new ExtraNotesAudioProcessor();
}
