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

#ifndef __NoteReader_h__
#include "NoteReader.h"
#endif

#ifndef __NoteWriter_h__
#include "NoteWriter.h"
#endif

#ifndef __defaults_H
#include "defaults.h"
#endif

namespace teragon {
  namespace AUNotes {
    class AUNotes : public AUEffectBase, public NoteReader, public NoteWriter {
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
      
      // NoteReader interface
      const char* getNote() const;
      // NoteWriter interface
      void setNote(const char* note);
      
      class AUNotesKernel : public AUKernelBase	{
      public:
        AUNotesKernel(AUEffectBase *inAudioUnit) : AUKernelBase(inAudioUnit) { }
        // Pass the signal through
        void Process(const Float32 *inputs, Float32 *outputs,
                     UInt32 frames, UInt32 channels, bool &ioSilence) {
          for(unsigned int i = 0; i < frames; ++i) {
            outputs[i] = inputs[i];
          }          
        }
      };
    };
  }
}
#endif