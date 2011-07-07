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
#include "AUNotes.h"
#endif

namespace teragon {
  namespace AUNotes {
    // Entry point for audio unit component
    COMPONENT_ENTRY(AUNotes)
    
    AUNotes::AUNotes(AudioUnit component)	: AUEffectBase(component) {
      CreateElements();
      this->savedNote = NULL;
      this->noteReader = NULL;
      this->noteWriter = NULL;
    }
    
    AUNotes::~AUNotes() {
      if(this->savedNote) {
        CFRelease(this->savedNote);
      }
    }
    
    /**
     * Called when the audio unit is being initialized by the host
     */
    OSStatus AUNotes::Initialize() {
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
          this->noteReader = (const NoteReader*)inData;
          result = noErr;
          break;
        case kNoteWriterPropertyId:
        {
          // The note writer pointer cannot be const, since that interface method
          // is not const, so first we need to get a pointer to the interface and
          // then discard the const-ness of the pointer.
          const NoteWriter *noteWriterPtr = (NoteWriter*)inData;
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
