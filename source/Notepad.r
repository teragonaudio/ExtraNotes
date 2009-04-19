/*
*	File:		Notepad.r
*	
*	Version:	1.0
* 
*	Created:	17.12.05
*	
*	Copyright:  Copyright © 2005 Teragon Audio, All Rights Reserved
* 
*/

#include <AudioUnit/AudioUnit.r>

#ifndef __defaults_H
#include "defaults.h"
#endif

// Note that resource IDs must be spaced 2 apart for the 'STR ' name and description
#define kAudioUnitResID_Notepad 1000
#define kAudioUnitResID_NotepadView 2000

//~~~~~~~~~~~~~~~~~~~ Notepad ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define RES_ID			kAudioUnitResID_Notepad
#define COMP_TYPE		kAudioUnitType_Effect
#define COMP_SUBTYPE	Notepad_COMP_SUBTYPE
#define COMP_MANUF		Notepad_COMP_MANF

#define VERSION			kNotepadVersion
#define NAME			"Teragon Audio: Notepad"
#define DESCRIPTION		"Notepad AU"
#define ENTRY_POINT		"NotepadEntry"

#include "AUResources.r"

//~~~~~~~~~~~~~~~~~~ Notepad View ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define RES_ID			kAudioUnitResID_NotepadView
#define COMP_TYPE		kAudioUnitCarbonViewComponentType
#define COMP_SUBTYPE	Notepad_COMP_SUBTYPE
#define COMP_MANUF		Notepad_COMP_MANF	

#define VERSION			kNotepadVersion
#define NAME			"Teragon Audio: Notepad"
#define DESCRIPTION		"Notepad Carbon AU View"
#define ENTRY_POINT		"NotepadViewEntry"

#include "AUResources.r"