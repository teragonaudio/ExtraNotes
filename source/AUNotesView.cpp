/*
 *	File:		AUNotesView.cpp
 *	
 *	Version:	1.0
 * 
 *	Created:	17.12.05
 *	
 *	Copyright:  Copyright 2005 Teragon Audio, All Rights Reserved
 * 
 */

#ifndef __AUNotesView_H
#include "AUNotesView.h"
#endif

COMPONENT_ENTRY(AUNotesView)

AUNotesView::AUNotesView(AudioUnitCarbonView auv) : AUCarbonViewBase(auv) {
}

AUNotesView::~AUNotesView() {
}

OSStatus AUNotesView::CreateUI(Float32 xoffset, Float32 yoffset) {
  IBNibRef nib;
  CFBundleRef bundle = CFBundleGetBundleWithIdentifier(CFSTR(kViewBundleName));
  OSStatus err = CreateNibReferenceWithCFBundle(bundle, CFSTR(kViewMainWindow), &nib);
  ControlRef rootContainer;
  GetRootControl(mCarbonWindow, &rootContainer);
  
  WindowRef nibWindow;
  err = CreateWindowFromNib(nib, CFSTR(kViewMainWindow), &nibWindow);
  ControlRef nibContainer;
  GetRootControl(nibWindow, &nibContainer);

  err = ::EmbedControl(nibContainer, mCarbonPane);

  Rect r;
  GetControlBounds(nibContainer, &r);
  SizeControl(mCarbonPane, r.right - r.left, r.bottom - r.top);
  Update(true);
  
  return noErr;
}

bool AUNotesView::exportData() {
  /*
  Size s_in, s_out;
  if(GetControlDataSize(m_text, kControlEditTextPart, kControlEditTextTextTag, &s_in) != noErr) {
    fprintf(stderr, "Couldn't get size elements from control\n");
  }
  char *body = new char[(int)s_in + 1];
  if(GetControlData(m_text, kControlEditTextPart, kControlEditTextTextTag, s_in, body, &s_out) != noErr) {
    fprintf(stderr, "No data in control\n");
    return false;
  }
  else {
    body[(int)s_in] = '\0';
  }

  delete [] body;
   */
  return true;
}

bool AUNotesView::importData() {
  /*
  OSStatus err = SetControlData(m_text, kControlEditTextPart, kControlEditTextTextTag,
                                m_orig_len, m_orig_text);
  if(err != noErr) {
    fprintf(stderr, "Could not set text from file\n");
  }
  DrawOneControl(m_text);
  */
  return true;
}

bool AUNotesView::saveData() {
  /*
  Size s_in, s_out;
  if(GetControlDataSize(m_text, kControlEditTextPart, kControlEditTextTextTag, &s_in) != noErr) {
    fprintf(stderr, "Couldn't get size elements from control\n");
  }
  char *body = new char[(int)s_in + 1];
  if(GetControlData(m_text, kControlEditTextPart, kControlEditTextTextTag, s_in, body, &s_out) != noErr) {
    fprintf(stderr, "No data in control\n");
    delete [] dname;
    return false;
  }
  else {
    body[(int)s_in] = '\0';
  }
  */
  return true;
}