/*
*	File:		AUNotes.r
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
#define kAudioUnitResID_AUNotes 1000
#define kAudioUnitResID_AUNotesView 2000

//~~~~~~~~~~~~~~~~~~~ AUNotes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define RES_ID			kAudioUnitResID_AUNotes
#define COMP_TYPE		kAudioUnitType_Effect
#define COMP_SUBTYPE	AUNotes_COMP_SUBTYPE
#define COMP_MANUF		AUNotes_COMP_MANF

#define VERSION			kAUNotesVersion
#define NAME			"Teragon Audio: AUNotes"
#define DESCRIPTION		"AUNotes"
#define ENTRY_POINT		"AUNotesEntry"

#include "AUResources.r"

//~~~~~~~~~~~~~~~~~~ AUNotes View ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define RES_ID			kAudioUnitResID_AUNotesView
#define COMP_TYPE		kAudioUnitCarbonViewComponentType
#define COMP_SUBTYPE	AUNotes_COMP_SUBTYPE
#define COMP_MANUF		AUNotes_COMP_MANF	

#define VERSION			kAUNotesVersion
#define NAME			"Teragon Audio: AUNotes"
#define DESCRIPTION		"AUNotes Carbon AU View"
#define ENTRY_POINT		"AUNotesViewEntry"

#include "AUResources.r"