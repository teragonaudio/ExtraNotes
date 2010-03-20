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
    
    void AUNotes::AUNotesKernel::Reset() {
    }
    
    void AUNotes::AUNotesKernel::Process(const Float32 *inputs, Float32 *outputs,
                                         UInt32 frames, UInt32 channels, bool &ioSilence) {
      for(unsigned int i = 0; i < frames; ++i) {
        outputs[i] = inputs[i];
      }
    }
  }
}
