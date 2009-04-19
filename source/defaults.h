/*
 *  defaults.h
 *  Notepad
 *
 *  Created by Nik Reiman on 23.12.05.
 *  Copyright 2005 Teragon Audio. All rights reserved.
 *
 */

#ifndef __defaults_H
#define __defaults_H

// GUI dimensional measurements
#define DEF_BUTTON_HEIGHT 20
#define DEF_BUTTON_WIDTH 70
#define DEF_TEXT_HEIGHT 300
#define DEF_TEXT_WIDTH 450
#define DEF_OFFSET 10
#define DEF_PRODUCT_NAME "Notepad"

// GUI Control references
#define CTL_TEXT 1000
#define CTL_SAVE 1001
#define CTL_CANCEL 1002
#define CTL_IMPORT 1003
#define CTL_EXPORT 1004

// Parameter stuff
enum
{
  PRM_NOTE_YEAR = 0,
  PRM_NOTE_DAY,
  PRM_NOTE_DAYCOUNT,
  PRM_NOTE_MONTH,
  PRM_NOTE_INDEX,
  NUM_PARAMS
};

// Other constants
#define MAX_FILENAME 512

#ifdef DEBUG
#define kNotepadVersion 0xFFFFFFFF
#else
#define kNotepadVersion 0x00010000	
#endif

#define Notepad_COMP_SUBTYPE 'Pass'
#define Notepad_COMP_MANF 'Tera'

#endif