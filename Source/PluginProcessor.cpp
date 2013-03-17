/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
ExtraNotesAudioProcessor::ExtraNotesAudioProcessor()
{
}

ExtraNotesAudioProcessor::~ExtraNotesAudioProcessor()
{
}

//==============================================================================
const String ExtraNotesAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int ExtraNotesAudioProcessor::getNumParameters()
{
    return 0;
}

float ExtraNotesAudioProcessor::getParameter (int index)
{
    return 0.0f;
}

void ExtraNotesAudioProcessor::setParameter (int index, float newValue)
{
}

const String ExtraNotesAudioProcessor::getParameterName (int index)
{
    return String::empty;
}

const String ExtraNotesAudioProcessor::getParameterText (int index)
{
    return String::empty;
}

const String ExtraNotesAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String ExtraNotesAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool ExtraNotesAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool ExtraNotesAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool ExtraNotesAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ExtraNotesAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ExtraNotesAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double ExtraNotesAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ExtraNotesAudioProcessor::getNumPrograms()
{
    return 0;
}

int ExtraNotesAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ExtraNotesAudioProcessor::setCurrentProgram (int index)
{
}

const String ExtraNotesAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void ExtraNotesAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ExtraNotesAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void ExtraNotesAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void ExtraNotesAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < getNumInputChannels(); ++channel)
    {
        float* channelData = buffer.getSampleData (channel);

        // ..do something to the data...
    }

    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
}

//==============================================================================
bool ExtraNotesAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ExtraNotesAudioProcessor::createEditor()
{
    return new ExtraNotesAudioProcessorEditor (this);
}

//==============================================================================
void ExtraNotesAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ExtraNotesAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ExtraNotesAudioProcessor();
}
