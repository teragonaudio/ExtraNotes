/*
 *	File:		Notepad.cpp
 *	
 *	Version:	1.0
 * 
 *	Created:	17.12.05
 *	
 *	Copyright:  Copyright © 2005 Teragon Audio, All Rights Reserved
 *
 */

#ifndef __Notepad_H
#include "Notepad.h"
#endif

COMPONENT_ENTRY(Notepad)

Notepad::Notepad(AudioUnit component)	: AUEffectBase(component) {
	CreateElements();
	Globals()->UseIndexedParameters(NUM_PARAMS);
}

Notepad::~Notepad() {
}

ComponentResult Notepad::GetParameterValueStrings(AudioUnitScope inScope,
                                                  AudioUnitParameterID inParameterID,
                                                  CFArrayRef *outStrings) {
  return AUEffectBase::GetParameterValueStrings(inScope, inParameterID, outStrings);
}

ComponentResult Notepad::GetParameterInfo(AudioUnitScope inScope,
                                          AudioUnitParameterID inParameterID,
                                          AudioUnitParameterInfo &outParameterInfo) {
	ComponentResult result = noErr;
  
	outParameterInfo.flags = kAudioUnitParameterFlag_IsWritable |
    kAudioUnitParameterFlag_IsReadable;
  
  if(inScope == kAudioUnitScope_Global) {
    switch(inParameterID) {
        /*
      case PRM_NOTE_YEAR:
        AUBase::FillInParameterName(outParameterInfo, PRM_NOTE_YEAR_NAME, false);
        outParameterInfo.unit = kAudioUnitParameterUnit_Generic;
        outParameterInfo.minValue = 2005;
        outParameterInfo.maxValue = 2010;
        outParameterInfo.defaultValue = m_year;
        break;
      case PRM_NOTE_DAY:
        AUBase::FillInParameterName(outParameterInfo, PRM_NOTE_DAY_NAME, false);
        outParameterInfo.unit = kAudioUnitParameterUnit_Generic;
        outParameterInfo.minValue = 0;
        outParameterInfo.maxValue = 31;
        outParameterInfo.defaultValue = m_daycount;
        break;
      case PRM_NOTE_DAYCOUNT:
        AUBase::FillInParameterName(outParameterInfo, PRM_NOTE_DAYCOUNT_NAME, false);
        outParameterInfo.unit = kAudioUnitParameterUnit_Generic;
        outParameterInfo.minValue = 0;
        outParameterInfo.maxValue = 365;
        outParameterInfo.defaultValue = m_daycount;
        break;
      case PRM_NOTE_MONTH:
        AUBase::FillInParameterName(outParameterInfo, PRM_NOTE_MONTH_NAME, false);
        outParameterInfo.unit = kAudioUnitParameterUnit_Generic;
        outParameterInfo.minValue = 0;
        outParameterInfo.maxValue = 11;
        outParameterInfo.defaultValue = m_daycount;
        break;
      case PRM_NOTE_INDEX:
        AUBase::FillInParameterName(outParameterInfo, PRM_NOTE_INDEX_NAME, false);
        outParameterInfo.unit = kAudioUnitParameterUnit_Generic;
        outParameterInfo.minValue = 0;
        outParameterInfo.maxValue = 100;
        outParameterInfo.defaultValue = m_index;
        break;
         */
      default:
        result = AUBase::GetParameterInfo(inScope, inParameterID, outParameterInfo);
        break;
    }
	}
  else {
    result = kAudioUnitErr_InvalidParameter;
  }
  
	return result;
}

ComponentResult Notepad::GetPropertyInfo(AudioUnitPropertyID inID,
                                         AudioUnitScope inScope,
                                         AudioUnitElement inElement,
                                         UInt32 &outDataSize,
                                         Boolean &outWritable) {
	return AUEffectBase::GetPropertyInfo(inID, inScope, inElement, outDataSize, outWritable);
}

ComponentResult Notepad::SaveState(CFPropertyListRef *outData) {
  ComponentResult err = AUBase::SaveState(outData);
  
  return err;
}

ComponentResult Notepad::RestoreState(CFPropertyListRef plist) {
  ComponentResult err = AUBase::RestoreState(plist);
  
  return err;
}

ComponentResult Notepad::GetProperty(AudioUnitPropertyID inID,
                                     AudioUnitScope inScope,
                                     AudioUnitElement inElement,
                                     void *outData) {
	return AUEffectBase::GetProperty(inID, inScope, inElement, outData);
}

void Notepad::NotepadKernel::Reset() {
}

void Notepad::NotepadKernel::Process(const Float32 *inSourceP,
                                     Float32 *inDestP,
                                     UInt32 inFramesToProcess,
                                     UInt32 inNumChannels,
                                     bool &ioSilence) {
#if 1
  for(unsigned int i = 0; i < inFramesToProcess; ++i) {
    inDestP[i] = inSourceP[i];
  }
#else
	UInt32 nSampleFrames = inFramesToProcess;
	const Float32 *sourceP = inSourceP;
	Float32 *destP = inDestP;
  
  // Not sure what the hell all this is necessary for...
	while(--nSampleFrames > 0) {
    Float32 inputSample = *sourceP;
		
		sourceP += inNumChannels;
    Float32 outputSample = inputSample;
    
		*destP = outputSample;
		destP += inNumChannels;
	}
#endif
}