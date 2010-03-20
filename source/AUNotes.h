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

#ifndef __defaults_H
#include "defaults.h"
#endif

namespace teragon {
  namespace AUNotes {
    class AUNotes : public AUEffectBase {
    public:
      AUNotes(AudioUnit component);
      ~AUNotes();
      
      AUKernelBase *NewKernel() { return new AUNotesKernel(this); };
      
      bool SupportsTail() { return false; };
      ComponentResult	Version() { return kAUNotesVersion; };
      
      int GetNumCustomUIComponents() { return 1; };
      void GetUIComponentDescs(ComponentDescription* inDescArray);
      
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
  }
}
#endif