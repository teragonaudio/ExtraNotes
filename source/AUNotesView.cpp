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
#include "AUNotesView.h"
#endif

namespace teragon {
  namespace AUNotes {
    COMPONENT_ENTRY(AUNotesView)
    
    AUNotesView::AUNotesView(AudioUnitCarbonView view) :
    AUCarbonViewBase(view),
    NoteReader(),
    NoteWriter()
    {
    }
    
    AUNotesView::~AUNotesView() {
    }
    
    /**
     * Called by the host when the user opens the plugin's window.
     * \param xoffset X-coordinate offset
     * \param yoffset Y-corrdinate offset
     * \return noErr on success, mac error code on failure
     */
    OSStatus AUNotesView::CreateUI(Float32 xoffset, Float32 yoffset) {
      OSStatus result = noErr;
      
      IBNibRef nib;
      CFBundleRef bundle = CFBundleGetBundleWithIdentifier(CFSTR(kViewBundleName));
      result = CreateNibReferenceWithCFBundle(bundle, CFSTR(kViewMainWindow), &nib);
      verify_noerr(result);
      
      result = CreateWindowFromNib(nib, CFSTR(kViewMainWindow), &(this->mainWindow));
      verify_noerr(result);
      
      ControlRef nibContainer;
      result = GetRootControl(this->mainWindow, &nibContainer);
      verify_noerr(result);
      
      result = ::EmbedControl(nibContainer, mCarbonPane);
      verify_noerr(result);
      
      Rect r;
      GetControlBounds(nibContainer, &r);
      SizeControl(mCarbonPane, r.right, r.bottom);
      MoveControl(mCarbonPane, 0, 0);
      Update(true);
      
      // Push address to reader and writer to the underlying plugin
      result = setPluginInterfaceProperty(kNoteReaderPropertyId, dynamic_cast<NoteReader*>(this));
      verify_noerr(result);
      result = setPluginInterfaceProperty(kNoteWriterPropertyId, dynamic_cast<NoteWriter*>(this));
      verify_noerr(result);
      
      return result;
    }
    
    /**
     * Sets a property value in the underlying AudioUnit plugin.  This method is used to push a
     * pointer to the note reader/writer interface to the plugin, allowing communication between
     * the plugin and the view.
     * \param propertyId AudioUnit property ID (scope is assumed to be global)
     * \param inData Pointer to data to set for property
     * \return 
     */
    OSStatus AUNotesView::setPluginInterfaceProperty(AudioUnitPropertyID propertyId, const void* inData) {
      OSStatus result = noErr;
      
      AudioUnit audioUnit = GetEditAudioUnit();
      if(audioUnit != NULL) {
        result = AudioUnitSetProperty(audioUnit, propertyId, kAudioUnitScope_Global, 0, inData, sizeof(inData));
      }
      
      return result;
    }
    
    /**
     * NoteReader interface implementation to return value of current note in view's editor
     * \return CFStringRef containing user's note
     */
    const CFStringRef AUNotesView::getNote() const {
      OSStatus status = noErr;
      
      // Find the control from the root control
      HIViewRef noteTextViewRef = NULL;
      const HIViewID noteTextViewId = {'NOTE', 128};
      ControlRef rootControl;
      status = GetRootControl(this->mainWindow, &rootControl);
      verify_noerr(status);
      
      status = HIViewFindByID(rootControl, noteTextViewId, &noteTextViewRef);
      verify_noerr(status);
      
      // Extract data from the control and return this reference
      CFStringRef noteText = NULL;
      status = GetControlData(noteTextViewRef, 0, kControlStaticTextCFStringTag, sizeof(noteText), &noteText, NULL);
      verify_noerr(status);
      
      return noteText;
    }
    
    /**
     * NoteWriter interface implementation to set note text within the user interface's editor
     * \param noteText Note text to set
     */
    void AUNotesView::setNote(const CFStringRef noteText) {
      OSStatus status = noErr;
      
      // Find the control from the root control
      HIViewRef noteTextViewRef = NULL;
      const HIViewID noteTextViewId = {'NOTE', 128};
      ControlRef rootControl;
      status = GetRootControl(this->mainWindow, &rootControl);
      verify_noerr(status);
      
      status = HIViewFindByID(rootControl, noteTextViewId, &noteTextViewRef);
      verify_noerr(status);
      
      status = SetControlData(noteTextViewRef, 0, kControlStaticTextCFStringTag, sizeof(noteText), &noteText);
      verify_noerr(status);      
    }
  }
}