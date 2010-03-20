/*
 *  defaults.h
 *  AUNotes
 *
 *  Created by Nik Reiman on 23.12.05.
 *  Copyright 2005 Teragon Audio. All rights reserved.
 *
 */

#ifndef __defaults_H
#define __defaults_H

#ifdef DEBUG
#define kAUNotesVersion 0xFFFFFFFF
#else
#define kAUNotesVersion 0x00010000	
#endif

#define kNoteReaderPropertyId 64000
#define kNoteWriterPropertyId 64001

#define AUNotes_COMP_SUBTYPE 'Pass'
#define AUNotes_COMP_MANF 'Tera'

#endif