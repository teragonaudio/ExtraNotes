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
      
      // Get address of plugin
      /* TODO: Does not seem to work properly...
      this->noteReader = reinterpret_cast<NoteReader*>(getPluginInterfaceProperty(kNoteReaderPropertyId));
      if(this->noteReader != NULL) {
        // After link to plugin has been established, get the saved text
        setNote(this->noteReader->getNote());
      }
      */
      
      // Push address to reader and writer to the underlying plugin
      setPluginInterfaceProperty(kNoteReaderPropertyId, dynamic_cast<NoteReader*>(this));
      setPluginInterfaceProperty(kNoteWriterPropertyId, dynamic_cast<NoteWriter*>(this));
      
      return result;
    }
    
    void* AUNotesView::getPluginInterfaceProperty(AudioUnitPropertyID propertyId) {
      OSStatus status = noErr;
      // TODO: If initialized to NULL, then the GetProperty() override does not seem to be properly called
      void* outData = (void*)0xdeadbeef;
      
      AudioUnit audioUnit = GetEditAudioUnit();
      if(audioUnit != NULL) {
        UInt32 outDataSize;
        status = AudioUnitGetPropertyInfo(audioUnit, propertyId, kAudioUnitScope_Global, 0, &outDataSize, NULL);
        verify_noerr(status);
        status = AudioUnitGetProperty(audioUnit, propertyId, kAudioUnitScope_Global, 0, outData, &outDataSize);
        verify_noerr(status);
      }
      
      return outData;
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
    
    // NoteReader interface
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
    
    // NoteWriter interface
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