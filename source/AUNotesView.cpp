/*
 *	File:		AUNotesView.cpp
 *	
 *	Version:	1.0
 * 
 *	Created:	17.12.05
 *	
 *	Copyright:  Copyright 2005 Teragon Audio, All Rights Reserved
 * 
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
      SizeControl(mCarbonPane, r.right - r.left, r.bottom);
      Update(true);
      
      // Push address to reader and writer to the underlying plugin
      setPluginInterfaceProperty(kNoteReaderPropertyId, dynamic_cast<NoteReader*>(this));
      setPluginInterfaceProperty(kNoteWriterPropertyId, dynamic_cast<NoteWriter*>(this));
      
      return result;
    }
    
    bool AUNotesView::setPluginInterfaceProperty(AudioUnitPropertyID propertyId, const void* inData) {
      OSStatus status = noErr;
      
      AudioUnit audioUnit = GetEditAudioUnit();
      if(audioUnit != NULL) {
        status = AudioUnitSetProperty(audioUnit, propertyId, kAudioUnitScope_Global, 0, inData, sizeof(inData));
        verify_noerr(status);
      }
      
      return (status == noErr);
    }
    
    const CFStringRef AUNotesView::getNote() const {
      OSStatus status = noErr;
      
      // Find the control
      HIViewRef noteTextViewRef = NULL;
      const HIViewID noteTextViewId = {'NOTE', 128};
      ControlRef rootControl;
      status = GetRootControl(this->mainWindow, &rootControl);
      verify_noerr(status);
      
      status = HIViewFindByID(rootControl, noteTextViewId, &noteTextViewRef);
      verify_noerr(status);
      
      CFStringRef noteText = NULL;
      status = GetControlData(noteTextViewRef, 0, kControlStaticTextCFStringTag, sizeof(noteText), &noteText, NULL);
      verify_noerr(status);
      
      return noteText;
    }
    
    void AUNotesView::setNote(const CFStringRef noteText) {
      OSStatus status = noErr;
      
      // Find the control
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