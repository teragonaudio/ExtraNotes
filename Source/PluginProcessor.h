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
