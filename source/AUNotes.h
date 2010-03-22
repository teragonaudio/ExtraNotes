/*
 * AUNotes - Teragon Audio - http://www.teragon.org
 * Copyright 2010 Teragon Audio LLC. All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY TERAGON AUDIO LLC ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TERAGON AUDIO LLC OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * The views and conclusions contained in the software and documentation are those of the
 * authors and should not be interpreted as representing official policies, either expressed
 * or implied, of Teragon Audio LLC.
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