/*
 *	File:		NotepadView.h
 *	
 *	Version:	1.0
 * 
 *	Created:	17.12.05
 *	
 *	Copyright:  Copyright 2005 Teragon Audio, All Rights Reserved
 * 
 */

#ifndef __NotepadView_H
#define __NotepadView_H

#include <Quicktime/Quicktime.h>

#include "AUCarbonViewBase.h"
#include "AUControlGroup.h"

#ifndef __defaults_H
#include "defaults.h"
#endif

#ifndef __productDir_H
#include "productDir.h"
#endif

static char _STRBUF[MAX_FILENAME];
static bool _STRSET;

class NotepadView : public AUCarbonViewBase {
public:
	NotepadView(AudioUnitCarbonView auv);
	~NotepadView();
  
  pascal ControlKeyFilterResult	StdKeyFilterCallback(ControlRef theControl, 
                                                     SInt16 *keyCode, SInt16 *charCode, 
                                                     EventModifiers *modifiers);    
	virtual OSStatus CreateUI(Float32 inXOffset, Float32 inYOffset);
//  virtual bool HandleEvent(EventRef event);
  static void dialogEventHandler(NavEventCallbackMessage message,
                                 NavCBRecPtr parms,
                                 NavCallBackUserData data);
  
protected:
  bool exportData();
  bool importData();
  bool readData();
  bool saveData();
private:
    ControlRef m_save_button;
  ControlRef m_cancel_button;
  ControlRef m_import_button;
  ControlRef m_export_button;
  ControlRef m_text;
  
  char *m_orig_text;
  unsigned int m_orig_len;
};

#endif