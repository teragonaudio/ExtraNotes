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
    /**
     * This class is the entry point for the AudioUnit and interfaces directly with the
     * host.  Since this plugin doesn't require so much special functionality, this class
     * simply inherits from the AUEffectBase class, which we let do most of the work except
     * when necessary.
     */
    class AUNotes : public AUEffectBase {
    public:
      AUNotes(AudioUnit component);
      ~AUNotes();
      
      OSStatus Initialize();
      
      // Must be set, or else auval will crash
      bool SupportsTail() { return false; };
      
      // Return plugin version number
      ComponentResult	Version() { return kAUNotesVersion; };
      
      // Must be set to 1 for our custom view
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