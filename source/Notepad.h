/*
 *	File:		Notepad.h
 *	
 *	Version:	1.0
 * 
 *	Created:	17.12.05
 *	
 */

#ifndef __Notepad_H
#define __Notepad_H

#include <AudioUnit/AudioUnitCarbonView.h>
#include "AUEffectBase.h"

#ifdef MAC
#include <sys/types.h>
#include <dirent.h>
#endif

#ifndef __defaults_H
#include "defaults.h"
#endif

#ifndef __productDir_H
#include "productDir.h"
#endif

/*
static CFStringRef PRM_NOTE_YEAR_NAME = CFSTR("Year");
static CFStringRef PRM_NOTE_DAY_NAME = CFSTR("Day");
static CFStringRef PRM_NOTE_DAYCOUNT_NAME = CFSTR("Daycount");
static CFStringRef PRM_NOTE_MONTH_NAME = CFSTR("Month");
static CFStringRef PRM_NOTE_INDEX_NAME = CFSTR("Index");
*/
 
class Notepad : public AUEffectBase {
public:
	Notepad(AudioUnit component);
	~Notepad();
  
  AUKernelBase *NewKernel() { return new NotepadKernel(this); };
  
	ComponentResult GetParameterValueStrings(AudioUnitScope inScope,
                                           AudioUnitParameterID inParameterID,
                                           CFArrayRef *outStrings);
	ComponentResult GetParameterInfo(AudioUnitScope inScope,
                                   AudioUnitParameterID	inParameterID,
                                   AudioUnitParameterInfo	&outParameterInfo);
	ComponentResult GetPropertyInfo(AudioUnitPropertyID inID,
                                  AudioUnitScope inScope,
                                  AudioUnitElement inElement,
                                  UInt32 &outDataSize,
                                  Boolean	&outWritable);
	ComponentResult GetProperty(AudioUnitPropertyID inID,
                              AudioUnitScope inScope,
                              AudioUnitElement inElement,
                              void *outData);
  
  bool SupportsTail() { return false; };
	ComponentResult	Version() { return kNotepadVersion; };
  
  int GetNumCustomUIComponents() { return 1; };
	void GetUIComponentDescs(ComponentDescription* inDescArray) {
    inDescArray[0].componentType = kAudioUnitCarbonViewComponentType;
    inDescArray[0].componentSubType = Notepad_COMP_SUBTYPE;
    inDescArray[0].componentManufacturer = Notepad_COMP_MANF;
    inDescArray[0].componentFlags = 0;
    inDescArray[0].componentFlagsMask = 0;
	};
  
  ComponentResult SaveState(CFPropertyListRef *outData);
  ComponentResult RestoreState(CFPropertyListRef plist);

  class NotepadKernel : public AUKernelBase	{
public:
    NotepadKernel(AUEffectBase *inAudioUnit) : AUKernelBase(inAudioUnit) { }
    
    virtual void Process(const Float32 	*inSourceP,
                         Float32 *inDestP,
                         UInt32 inFramesToProcess,
                         UInt32 inNumChannels,
                         bool &ioSilence);
    virtual void Reset();
  };
};
#endif