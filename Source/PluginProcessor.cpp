/*
 * Copyright (c) 2013 - Teragon Audio LLC
 *
 * Permission is granted to use this software under the terms of either:
 * a) the GPL v2 (or any later version)
 * b) the Affero GPL v3
 *
 * Details of these licenses can be found at: www.gnu.org/licenses
 *
 * This software is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * ------------------------------------------------------------------------------
 *
 * This software uses the JUCE library.
 *
 * To release a closed-source product which uses JUCE, commercial licenses are
 * available: visit www.juce.com for more information.
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Resources.h"
#include "TextEditorParameter.h"

ExtraNotesAudioProcessor::ExtraNotesAudioProcessor() :
TeragonPluginBase(), ParameterObserver() {
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
    bool supportedHost = true;
    bool supportedOs = false;
    bool testedOs = false;
    bool knownProblemHost = false;

    switch(SystemStats::getOperatingSystemType()) {
        case SystemStats::OperatingSystemType::Linux:
            supportedOs = true;
            testedOs = true;

            if(hostType.getHostPath().endsWith("renoise")) {
                testedHost = true;
            }
            else {
                testedHost = false;
            }
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
                case PluginHostType::HostType::AbletonLive6:
                case PluginHostType::HostType::AbletonLive7:
                    supportedHost = false;
                    break;
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
                case PluginHostType::HostType::AbletonLive6:
                case PluginHostType::HostType::AbletonLive7:
                    supportedHost = false;
                    break;
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
    else if(!supportedHost) {
        result += "\n\nThis host is not supported! You might experience problems with text input.";
    }
    else if(!testedHost) {
        result += "\n\nThis host is untested! Please email support@teragonaudio.com with your system stats to report success or failure with text input.";
    }
    else if(!testedOs) {
        result += "\n\nThis operating system is untested! Please email support@teragonaudio.com with your system stats to report success or failure with text input.";
    }

    return result;
}

AudioProcessorEditor *ExtraNotesAudioProcessor::createEditor() {
    return new ExtraNotesAudioProcessorEditor(this, parameters, Resources::getCache());
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

AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
    return new ExtraNotesAudioProcessor();
}
