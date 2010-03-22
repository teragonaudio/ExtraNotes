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

#ifndef __AUNotesView_H
#define __AUNotesView_H

#include <Carbon/Carbon.h>
#include <Quicktime/Quicktime.h>

#include "AUCarbonViewBase.h"
#include "AUControlGroup.h"

#ifndef __NoteReader_h__
#include "NoteReader.h"
#endif

#ifndef __NoteWriter_h__
#include "NoteWriter.h"
#endif

#ifndef __defaults_H
#include "defaults.h"
#endif

#define kViewBundleName "org.teragon.AUNotes"
#define kViewMainWindow "MainWindow"

namespace teragon {
  namespace AUNotes {
    /**
     * This class provides a custom carbon view which is used by the AudioUnit to display
     * and edit the user's note.
     */
    class AUNotesView : public AUCarbonViewBase, public NoteReader, public NoteWriter {
    public:
      AUNotesView(AudioUnitCarbonView auv);
      ~AUNotesView();
      
      virtual OSStatus CreateUI(Float32 inXOffset, Float32 inYOffset);
      
      // Note reader & writer interfaces
      const CFStringRef getNote() const;
      void setNote(const CFStringRef noteText);
      
    private:
      OSStatus setPluginInterfaceProperty(AudioUnitPropertyID propertyId, const void* inData);
            
      HIWindowRef mainWindow;
      NoteReader* noteReader;
    };
  }
}
#endif