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
  m_orig_text = NULL;
  m_orig_len = 0;
}

AUNotesView::~AUNotesView() {
  if(m_orig_text) {
    delete [] m_orig_text;
  }
}

OSStatus AUNotesView::CreateUI(Float32 xoffset, Float32 yoffset) {
  IBNibRef nib;
  CFBundleRef bundle = CFBundleGetBundleWithIdentifier(CFSTR("org.teragon.AUNotes"));
  OSStatus err = CreateNibReferenceWithCFBundle(bundle, CFSTR("MainWindow"), &nib);
  ControlRef rootContainer;
  GetRootControl(mCarbonWindow, &rootContainer);
  
  WindowRef nibWindow;
  err = CreateWindowFromNib(nib, CFSTR("AUNotes"), &nibWindow);
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
  FILE *fp = NULL;
  if(fp == NULL) {
    return false;
  }
  
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
  return true;
}

bool AUNotesView::importData() {  
  FILE *fp = NULL;
  if(fp == NULL) {
    return false;
  }
  
  // Find out how many bytes are in the header and body
  unsigned int h_len;
  {
    unsigned int bytes = 2;
    char header_len[bytes + 1];
    if(fread(&header_len, sizeof(char), bytes, fp) < bytes) {
#ifdef DEBUG
      fprintf(stderr, "Read error getting header length\n");
#endif
      fclose(fp);
      return false;
    }
    header_len[bytes] = '\0';
    h_len = atoi(header_len);
  }
  {
    unsigned int bytes = 4;
    char body_len[bytes + 1];
    if(fread(&body_len, sizeof(char), bytes, fp) < bytes) {
#ifdef DEBUG
      fprintf(stderr, "Read error getting body length\n");
#endif
      fclose(fp);
      return false;
    }
    body_len[bytes] = '\0';
    m_orig_len = atoi(body_len);
  }
  
#ifdef DEBUG
  fprintf(stderr, "%d bytes in header, %d bytes in body\n", h_len, m_orig_len);
#endif
  
  // Now read in the header and body
  char header[h_len + 1];
  if(fread(&header, sizeof(char), h_len, fp) < h_len) {
#ifdef DEBUG
    fprintf(stderr, "Read error getting header\n");
#endif
    fclose(fp);
    return false;
  }    
  header[h_len] = '\0';
  
  if(m_orig_text) {
    delete [] m_orig_text;
  }
  m_orig_text = new char[m_orig_len + 1];
  if(fread(m_orig_text, sizeof(char), m_orig_len, fp) < m_orig_len) {
#ifdef DEBUG
    fprintf(stderr, "Read error getting body\n");
#endif
    fclose(fp);
    return false;
  }    
  m_orig_text[m_orig_len] = '\0';
  OSStatus err = SetControlData(m_text, kControlEditTextPart, kControlEditTextTextTag,
                                m_orig_len, m_orig_text);
  if(err != noErr) {
#ifdef DEBUG
    fprintf(stderr, "Could not set text from file\n");
#endif
  }
  DrawOneControl(m_text);
  
  fclose(fp);  
  return true;
}

bool AUNotesView::readData() {
  char *dname = new char[MAX_FILENAME];
  /*
  if(!getProductDir(DEF_PRODUCT_NAME, dname)) {
#ifdef DEBUG
    fprintf(stderr, "Could not get product directory\n");
#endif
    delete [] dname;
    return false;
  }
  */
  float year, daycount, index;
  AudioUnitGetParameter(GetEditAudioUnit(), PRM_NOTE_YEAR, kAudioUnitScope_Global, 0, &year);
  AudioUnitGetParameter(GetEditAudioUnit(), PRM_NOTE_DAYCOUNT, kAudioUnitScope_Global, 0, &daycount);
  AudioUnitGetParameter(GetEditAudioUnit(), PRM_NOTE_INDEX, kAudioUnitScope_Global, 0, &index);
  
  char fname[MAX_FILENAME];
  snprintf(fname, MAX_FILENAME, "%s%4d.%03d.%03d", dname, (int)year, (int)daycount, (int)index);
  FILE *fp = fopen(fname, "r");
  if(fp == NULL) {
#ifdef DEBUG
    fprintf(stderr, "No entry for '%s'\n", fname);
#endif
    delete [] dname;
    return false;
  }
  
  // Find out how many bytes are in the header and body
  unsigned int h_len;
  {
    unsigned int bytes = 2;
    char header_len[bytes + 1];
    if(fread(&header_len, sizeof(char), bytes, fp) < bytes) {
#ifdef DEBUG
      fprintf(stderr, "Read error getting header length\n");
#endif
      delete [] dname;
      fclose(fp);
      return false;
    }
    header_len[bytes] = '\0';
    h_len = atoi(header_len);
  }
  {
    unsigned int bytes = 4;
    char body_len[bytes + 1];
    if(fread(&body_len, sizeof(char), bytes, fp) < bytes) {
#ifdef DEBUG
      fprintf(stderr, "Read error getting body length\n");
#endif
      delete [] dname;
      fclose(fp);
      return false;
    }
    body_len[bytes] = '\0';
    m_orig_len = atoi(body_len);
  }
  
#ifdef DEBUG
  fprintf(stderr, "%d bytes in header, %d bytes in body\n", h_len, m_orig_len);
#endif
  
  // Now read in the header and body
  char header[h_len + 1];
  if(fread(&header, sizeof(char), h_len, fp) < h_len) {
#ifdef DEBUG
    fprintf(stderr, "Read error getting header\n");
#endif
    delete [] dname;
    fclose(fp);
    return false;
  }    
  header[h_len] = '\0';
  
  if(m_orig_text) {
    delete [] m_orig_text;
  }
  m_orig_text = new char[m_orig_len + 1];
  if(fread(m_orig_text, sizeof(char), m_orig_len, fp) < m_orig_len) {
#ifdef DEBUG
    fprintf(stderr, "Read error getting body\n");
#endif
    delete [] dname;
    fclose(fp);
    return false;
  }    
  m_orig_text[m_orig_len] = '\0';
  
  delete [] dname;
  fclose(fp);
  return true;
}

bool AUNotesView::saveData() {
  char *dname = new char[MAX_FILENAME];
  /*
  if(!getProductDir(DEF_PRODUCT_NAME, dname)) {
#ifdef DEBUG
    fprintf(stderr, "Could not get product directory\n");
#endif
    delete [] dname;
    return false;
  }
  */
  float year, month, day, daycount, index;
  AudioUnitGetParameter(GetEditAudioUnit(), PRM_NOTE_YEAR, kAudioUnitScope_Global, 0, &year);
  AudioUnitGetParameter(GetEditAudioUnit(), PRM_NOTE_DAY, kAudioUnitScope_Global, 0, &day);
  AudioUnitGetParameter(GetEditAudioUnit(), PRM_NOTE_DAYCOUNT, kAudioUnitScope_Global, 0, &daycount);
  AudioUnitGetParameter(GetEditAudioUnit(), PRM_NOTE_MONTH, kAudioUnitScope_Global, 0, &month);
  AudioUnitGetParameter(GetEditAudioUnit(), PRM_NOTE_INDEX, kAudioUnitScope_Global, 0, &index);
  
  char fname[MAX_FILENAME];
  snprintf(fname, MAX_FILENAME, "%s%4d.%03d.%03d", dname, (int)year, (int)daycount, (int)index);
  FILE *fp = fopen(fname, "w");
  if(fp == NULL) {
#ifdef DEBUG
    fprintf(stderr, "Could not open '%s' for writing\n", fname);
#endif
    delete [] dname;
    return false;
  }
  
  Size s_in, s_out;
  if(GetControlDataSize(m_text, kControlEditTextPart, kControlEditTextTextTag, &s_in) != noErr) {
#ifdef DEBUG
    fprintf(stderr, "Couldn't get size elements from control\n");
#endif
  }
  char *body = new char[(int)s_in + 1];
  if(GetControlData(m_text, kControlEditTextPart, kControlEditTextTextTag, s_in, body, &s_out) != noErr) {
#ifdef DEBUG
    fprintf(stderr, "No data in control\n");
#endif
    delete [] dname;
    return false;
  }
  else {
    body[(int)s_in] = '\0';
  }
  
  // Format: YYYYMMDD:USERNAME
  char header[48];
  snprintf(header, 48, "%04d%02d%02d:%s", (int)year, (int)month, (int)day, getenv("USER"));
  
  // Format: AABBBB:HEADER:ENTRY\n
  // Where AA is the number of characters in the header, and BBBB is the number
  // of characters in the entry body
  fprintf(fp, "%02d%04d%s%s\n", (int)strlen(header), (int)s_in, header, body);
  fflush(fp);
  fclose(fp);
  
  delete [] body;
  delete [] dname;
  return true;
}