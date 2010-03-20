/*
 *	File:		AUNotes.h
 *	
 *	Version:	1.0
 * 
 *	Created:	17.12.05
 *	
 */

#ifndef __AUNotes_H
#define __AUNotes_H

#include <AudioUnit/AudioUnitCarbonView.h>
#include "AUEffectBase.h"

#ifdef MAC
#include <sys/types.h>
#include <dirent.h>
#endif

#ifndef __defaults_H
#include "defaults.h"
#endif

/*
static CFStringRef PRM_NOTE_YEAR_NAME = CFSTR("Year");
static CFStringRef PRM_NOTE_DAY_NAME = CFSTR("Day");
static CFStringRef PRM_NOTE_DAYCOUNT_NAME = CFSTR("Daycount");
static CFStringRef PRM_NOTE_MONTH_NAME = CFSTR("Month");
static CFStringRef PRM_NOTE_INDEX_NAME = CFSTR("Index");
*/
 
class AUNotes : public AUEffectBase {
public:
	AUNotes(AudioUnit component);
	~AUNotes();
  
  AUKernelBase *NewKernel() { return new AUNotesKernel(this); };
  
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
	ComponentResult	Version() { return kAUNotesVersion; };
  
  int GetNumCustomUIComponents() { return 1; };
	void GetUIComponentDescs(ComponentDescription* inDescArray) {
    inDescArray[0].componentType = kAudioUnitCarbonViewComponentType;
    inDescArray[0].componentSubType = AUNotes_COMP_SUBTYPE;
    inDescArray[0].componentManufacturer = AUNotes_COMP_MANF;
    inDescArray[0].componentFlags = 0;
    inDescArray[0].componentFlagsMask = 0;
	};
  
  ComponentResult SaveState(CFPropertyListRef *outData);
  ComponentResult RestoreState(CFPropertyListRef plist);

  class AUNotesKernel : public AUKernelBase	{
public:
    AUNotesKernel(AUEffectBase *inAudioUnit) : AUKernelBase(inAudioUnit) { }
    
    virtual void Process(const Float32 	*inSourceP,
                         Float32 *inDestP,
                         UInt32 inFramesToProcess,
                         UInt32 inNumChannels,
                         bool &ioSilence);
    virtual void Reset();
  };
};
#endif