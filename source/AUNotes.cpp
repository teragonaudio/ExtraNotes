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
    COMPONENT_ENTRY(AUNotes)
    
    AUNotes::AUNotes(AudioUnit component)	: AUEffectBase(component) {
      CreateElements();
      Globals()->UseIndexedParameters(0);
      
      this->noteReader = NULL;
      this->noteWriter = NULL;
    }
    
    AUNotes::~AUNotes() {
    }
    
    void AUNotes::GetUIComponentDescs(ComponentDescription* inDescArray) {
      inDescArray[0].componentType = kAudioUnitCarbonViewComponentType;
      inDescArray[0].componentSubType = AUNotes_COMP_SUBTYPE;
      inDescArray[0].componentManufacturer = AUNotes_COMP_MANF;
      inDescArray[0].componentFlags = 0;
      inDescArray[0].componentFlagsMask = 0;
    };
    
    ComponentResult AUNotes::GetPropertyInfo(AudioUnitPropertyID inId,
                                             AudioUnitScope inScope,
                                             AudioUnitElement inElement,
                                             UInt32& outDataSize,
                                             Boolean& outWritable) {
      ComponentResult result;
      
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
    
    ComponentResult AUNotes::SetProperty(AudioUnitPropertyID inId,
                                         AudioUnitScope inScope,
                                         AudioUnitElement inElement,
                                         const void *inData,
                                         UInt32 inDataSize) {
      ComponentResult result;
      
      switch(inId) {
        case kNoteReaderPropertyId:
          this->noteReader = (NoteReader*)inData;
          result = noErr;
          break;
        case kNoteWriterPropertyId:
          this->noteWriter = (NoteWriter*)inData;
          result = noErr;
          break;
        default:
        result = AUEffectBase::SetProperty(inId, inScope, inElement, inData, inDataSize);
          break;
      }
      
      return result;
    }
    
    ComponentResult AUNotes::SaveState(CFPropertyListRef *outData) {
      ComponentResult err = AUBase::SaveState(outData);
      // FIXME: Read text here
      return err;
    }
    
    ComponentResult AUNotes::RestoreState(CFPropertyListRef plist) {
      ComponentResult err = AUBase::RestoreState(plist);
      // FIXME: Set text here
      return err;
    }
    
    // NoteReader interface
    const char* AUNotes::getNote() const {
      return NULL;
    }
    
    // NoteWriter interface
    void AUNotes::setNote(const char* note) {
    }
  }
}
