/*
 *  NoteReader.h
 *  AUNotes
 *
 *  Created by Nik Reiman on 2010-03-20.
 *  Copyright 2010 Teragon Audio. All rights reserved.
 *
 */

#ifndef __NoteReader_h__
#define __NoteReader_h__

namespace teragon {
  namespace AUNotes {
    class NoteReader {
    public:
      NoteReader() {};
      virtual ~NoteReader() {};
      
      virtual const char* getNote() const = 0;
    };
  }
}

#endif