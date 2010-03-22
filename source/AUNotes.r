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

#include <AudioUnit/AudioUnit.r>

#ifndef __defaults_H
#include "defaults.h"
#endif

// Note that resource IDs must be spaced 2 apart for the 'STR ' name and description
#define kAudioUnitResID_AUNotes 1000
#define kAudioUnitResID_AUNotesView 2000

// AudioUnit plugin
#define RES_ID			kAudioUnitResID_AUNotes
#define COMP_TYPE		kAudioUnitType_Effect
#define COMP_SUBTYPE	AUNotes_COMP_SUBTYPE
#define COMP_MANUF		AUNotes_COMP_MANF

#define VERSION			kAUNotesVersion
#define NAME			"Teragon Audio: AUNotes"
#define DESCRIPTION		"AUNotes"
#define ENTRY_POINT		"AUNotesEntry"

#include "AUResources.r"

// Custom plugin view
#define RES_ID			kAudioUnitResID_AUNotesView
#define COMP_TYPE		kAudioUnitCarbonViewComponentType
#define COMP_SUBTYPE	AUNotes_COMP_SUBTYPE
#define COMP_MANUF		AUNotes_COMP_MANF	

#define VERSION			kAUNotesVersion
#define NAME			"Teragon Audio: AUNotes"
#define DESCRIPTION		"AUNotes Carbon AU View"
#define ENTRY_POINT		"AUNotesViewEntry"

#include "AUResources.r"