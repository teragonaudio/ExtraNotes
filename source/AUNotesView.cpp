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
      
      //ControlRef rootContainer;
      //GetRootControl(mCarbonWindow, &rootContainer);
      result = CreateWindowFromNib(nib, CFSTR(kViewMainWindow), &(this->mainWindow));
      ControlRef nibContainer;
      GetRootControl(this->mainWindow, &nibContainer);
      
      result = ::EmbedControl(nibContainer, mCarbonPane);
      
      Rect r;
      GetControlBounds(nibContainer, &r);
      SizeControl(mCarbonPane, r.right - r.left, r.bottom);
      Update(true);
      
      // Get address of plugin
      getPluginInterfaceProperty(kNoteReaderPropertyId, this->noteReader);
      getPluginInterfaceProperty(kNoteWriterPropertyId, this->noteWriter);

      // Push address to reader and writer to the underlying plugin
      setPluginInterfaceProperty(kNoteReaderPropertyId, dynamic_cast<NoteReader*>(this));
      setPluginInterfaceProperty(kNoteWriterPropertyId, dynamic_cast<NoteWriter*>(this));
      
      return result;
    }
    
    bool AUNotesView::getPluginInterfaceProperty(AudioUnitPropertyID propertyId, void *outData) {
      bool result = false;
      
      AudioUnit audioUnit = GetEditAudioUnit();
      if(audioUnit != NULL) {
        UInt32 outDataSize;
        result = (AudioUnitGetProperty(audioUnit, propertyId, kAudioUnitScope_Global, 0, outData, &outDataSize) == noErr);
      }
      
      return result;
    }
    
    bool AUNotesView::setPluginInterfaceProperty(AudioUnitPropertyID propertyId, const void* inData) {
      bool result = false;
      
      AudioUnit audioUnit = GetEditAudioUnit();
      if(audioUnit != NULL) {
        result = (AudioUnitSetProperty(audioUnit, propertyId, kAudioUnitScope_Global, 0, inData, sizeof(inData)) == noErr);
      }
      
      return result;
    }
    
    // NoteReader interface
    const CFStringRef AUNotesView::getNote() const {
      CFStringRef result = CFSTR("");
      OSStatus status = noErr;
      
      // Find the control
      HIViewRef noteTextViewRef = NULL;
      const HIViewID noteTextViewId = {'NOTE', 128};
      ControlRef rootControl;
      GetRootControl(this->mainWindow, &rootControl);
      status = HIViewFindByID(rootControl, noteTextViewId, &noteTextViewRef);
      verify_noerr(status);
      
      CFStringRef noteTextRef = NULL;
      status = GetControlData(noteTextViewRef, 0, kControlStaticTextCFStringTag, sizeof(noteTextRef), &noteTextRef, NULL);
      verify_noerr(status);
      
      result = noteTextRef;
      return result;
    }
    
    // NoteWriter interface
    void AUNotesView::setNote(const CFStringRef note) {
      OSStatus status = noErr;
      
      // Find the control
      HIViewRef noteTextViewRef = NULL;
      const HIViewID noteTextViewId = {'NOTE', 128};
      ControlRef rootControl;
      GetRootControl(this->mainWindow, &rootControl);
      status = HIViewFindByID(rootControl, noteTextViewId, &noteTextViewRef);
      verify_noerr(status);
      
      status = SetControlData(noteTextViewRef, 0, kControlStaticTextCFStringTag, sizeof(note), &note);
      verify_noerr(status);      
    }
  }
}