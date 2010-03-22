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

/** Property to set NoteReader interface pointer */
#define kNoteReaderPropertyId 64000
/** Property to set NoteWriter interface pointer */
#define kNoteWriterPropertyId 64001
/** Plugin subtype of AudioUnit */
#define AUNotes_COMP_SUBTYPE 'note'
/** Plugin manufacturer of AudioUnit */
#define AUNotes_COMP_MANF 'Tera'

#endif