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
    class AUNotes : public AUEffectBase {
    public:
      AUNotes(AudioUnit component);
      ~AUNotes();
      
      OSStatus Initialize();
      
      bool SupportsTail() { return false; };
      ComponentResult	Version() { return kAUNotesVersion; };
      
      int GetNumCustomUIComponents() { return 1; };
      void GetUIComponentDescs(ComponentDescription* inDescArray);
      
      OSStatus GetPropertyInfo(AudioUnitPropertyID inID,
                               AudioUnitScope inScope,
                               AudioUnitElement inElement,
                               UInt32& outDataSize,
                               Boolean& outWritable);
      OSStatus SetProperty(AudioUnitPropertyID inID,
                           AudioUnitScope inScope,
                           AudioUnitElement inElement,
                           const void* inData,
                           UInt32 inDataSize);
      
      ComponentResult SaveState(CFPropertyListRef *outData);
      ComponentResult RestoreState(CFPropertyListRef plist);
      
      // Note reader & writer interfaces
      const CFStringRef getNote() const;
      void setNote(const CFStringRef note);
      
    private:
      void setViewNoteText(CFStringRef noteText);
      
      CFStringRef savedNote;
      const NoteReader* noteReader;
      NoteWriter* noteWriter;
    };
  }
}
#endif