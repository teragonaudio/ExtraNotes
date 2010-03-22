/*
 *	File:		AUNotes.cpp
 *	
 *	Version:	1.0
 * 
 *	Created:	17.12.05
 *	
 *	Copyright:  Copyright © 2005 Teragon Audio, All Rights Reserved
 *
 */

#ifndef __AUNotes_H
#include "AUNotes.h"
#endif

namespace teragon {
  namespace AUNotes {
    // Entry point for audio unit component
    COMPONENT_ENTRY(AUNotes)
    
    AUNotes::AUNotes(AudioUnit component)	: AUEffectBase(component) {
      CreateElements();
    }
    
    AUNotes::~AUNotes() {
      CFRelease(this->savedNote);
    }
    
    /**
     * Called when the audio unit is being initialized by the host
     */
    OSStatus AUNotes::Initialize() {
      this->savedNote = CFSTR("");
      this->noteReader = NULL;
      this->noteWriter = NULL;
      return noErr;
    }
    
    /**
     * Get component discriptions for custom user interface views
     * \param inDescArray Array to write list of custom component descriptions to.  The length
     * of this array is determined when the host calls GetNumCustomUIComponents().
     */
    void AUNotes::GetUIComponentDescs(ComponentDescription* inDescArray) {
      inDescArray[0].componentType = kAudioUnitCarbonViewComponentType;
      inDescArray[0].componentSubType = AUNotes_COMP_SUBTYPE;
      inDescArray[0].componentManufacturer = AUNotes_COMP_MANF;
      inDescArray[0].componentFlags = 0;
      inDescArray[0].componentFlagsMask = 0;
    };
    
    /**
     * Called by the host to determine the size and writable status of plugin properties
     * \param inId Property ID
     * \param inScope Property scope
     * \param inElement Property element ID, if applicable
     * \param outDataSize Reference to integer which indicates the property's size
     * \param outWriteable Reference to boolean which indicates if the property can be
     * written to
     * \return noErr on success, other mac error code on failure
     */
    OSStatus AUNotes::GetPropertyInfo(AudioUnitPropertyID inId,
                                      AudioUnitScope inScope,
                                      AudioUnitElement inElement,
                                      UInt32& outDataSize,
                                      Boolean& outWritable) {
      OSStatus result;
      
      switch(inId) {
        case kNoteReaderPropertyId:
          outDataSize = sizeof(NoteReader*);
          result = noErr;
          break;
        case kNoteWriterPropertyId:
          outDataSize = sizeof(NoteWriter*);
          result = noErr;
          break;
        default:
          result = AUEffectBase::GetPropertyInfo(inId, inScope, inElement, outDataSize, outWritable);
          break;
      }
      return result;
    }
    
    /**
     * Set a property within the AudioUnit
     * \param inId Property ID
     * \param inScope Property scope
     * \param inElement Property element ID, if applicable
     * \param inData Pointer which contains a data chunk which will be set to the property's data
     * \param inDataSize Size of inData, in bytes
     * \return noErr on success, other mac error code on failure
     */
    OSStatus AUNotes::SetProperty(AudioUnitPropertyID inId,
                                  AudioUnitScope inScope,
                                  AudioUnitElement inElement,
                                  const void* inData,
                                  UInt32 inDataSize) {
      OSStatus result;
      
      switch(inId) {
        case kNoteReaderPropertyId:
          this->noteReader = reinterpret_cast<const NoteReader*>(inData);
          result = noErr;
          break;
        case kNoteWriterPropertyId:
        {
          // The note writer pointer cannot be const, since that interface method
          // is not const, so first we need to get a pointer to the interface and
          // then discard the const-ness of the pointer.
          const NoteWriter *noteWriterPtr = reinterpret_cast<const NoteWriter*>(inData);
          this->noteWriter = const_cast<NoteWriter*>(noteWriterPtr);
          // After the view sets this property, we push the current value of the
          // note back up to it so that it can display this text in the window.
          setViewNoteText(this->savedNote);
          result = noErr;
        }
          break;
        default:
          result = AUEffectBase::SetProperty(inId, inScope, inElement, inData, inDataSize);
          break;
      }
      
      return result;
    }
    
    /**
     * Called by the host when the user saves their document.  This allows the plugin
     * to write some data which will be saved alongside the document.
     * \param outData Pointer to data, which is a generic reference to any carbon type
     * \return noErro on succes, other mac error code on failure
     */
    ComponentResult AUNotes::SaveState(CFPropertyListRef *outData) {
      ComponentResult err = AUBase::SaveState(outData);
      
      if(this->noteReader != NULL) {
        this->savedNote = CFStringCreateCopy(kCFAllocatorDefault, this->noteReader->getNote());
        *outData = this->savedNote;
      }
      
      return err;
    }
    
    /**
     * Called by the host when a document is opened by the user, or when the plugin is
     * first instantiated.  This allows the plugin to retrieve any data written to the
     * document in the SaveState() call.
     * \param inData Reference to data created during SaveState.  When the plugin is first
     * instantiated, this method will also be called with non-null data, so we should be
     * careful to interpret this data correctly.
     * \return noError on success, other mac error code on failure
     */
    ComponentResult AUNotes::RestoreState(CFPropertyListRef inData) {
      ComponentResult err = AUBase::RestoreState(inData);
      
      if(inData != NULL) {
        this->savedNote = CFStringCreateCopy(kCFAllocatorDefault, reinterpret_cast<CFStringRef>(inData));
      }
      
      if(this->noteWriter != NULL) {
        setViewNoteText(this->savedNote);
      }
      
      return err;
    }
    
    /**
     * Push the text of a note from the plugin up to the view's window.
     * \param noteText Note text (may not be null)
     */
    void AUNotes::setViewNoteText(CFStringRef noteText) {
      if(this->noteWriter != NULL && noteText != NULL) {
        this->noteWriter->setNote(noteText);
      }
    }
  }
}
