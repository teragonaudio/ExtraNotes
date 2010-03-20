/*
 *	File:		AUNotesView.h
 *	
 *	Version:	1.0
 * 
 *	Created:	17.12.05
 *	
 *	Copyright:  Copyright 2005 Teragon Audio, All Rights Reserved
 * 
 */

#ifndef __AUNotesView_H
#define __AUNotesView_H

#include <Quicktime/Quicktime.h>

#include "AUCarbonViewBase.h"
#include "AUControlGroup.h"

#ifndef __defaults_H
#include "defaults.h"
#endif

class AUNotesView : public AUCarbonViewBase {
public:
	AUNotesView(AudioUnitCarbonView auv);
	~AUNotesView();
  
  pascal ControlKeyFilterResult	StdKeyFilterCallback(ControlRef theControl, 
                                                     SInt16 *keyCode, SInt16 *charCode, 
                                                     EventModifiers *modifiers);    
	virtual OSStatus CreateUI(Float32 inXOffset, Float32 inYOffset);

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