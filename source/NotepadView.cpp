/*
 *	File:		NotepadView.cpp
 *	
 *	Version:	1.0
 * 
 *	Created:	17.12.05
 *	
 *	Copyright:  Copyright 2005 Teragon Audio, All Rights Reserved
 * 
 */

#ifndef __NotepadView_H
#include "NotepadView.h"
#endif

COMPONENT_ENTRY(NotepadView)

NotepadView::NotepadView(AudioUnitCarbonView auv) : AUCarbonViewBase(auv) {
  m_orig_text = NULL;
  m_orig_len = 0;
  memset(_STRBUF, 0x0, sizeof(char) * MAX_FILENAME);
  _STRSET = false;
}

NotepadView::~NotepadView() {
  if(m_orig_text) {
    delete [] m_orig_text;
  }
}

OSStatus NotepadView::CreateUI(Float32 xoffset, Float32 yoffset) {
  IBNibRef nib;
  CFBundleRef bundle = CFBundleGetBundleWithIdentifier(CFSTR("org.teragon.Notepad.AU"));
  OSStatus err = CreateNibReferenceWithCFBundle(bundle, CFSTR("MainWindow"), &nib);
  ControlRef rootContainer;
  GetRootControl(mCarbonWindow, &rootContainer);
  
  WindowRef nibWindow;
  err = CreateWindowFromNib(nib, CFSTR("Notepad"), &nibWindow);
  ControlRef nibContainer;
  GetRootControl(nibWindow, &nibContainer);

  err = ::EmbedControl(nibContainer, mCarbonPane);

  Rect r;
  GetControlBounds(nibContainer, &r);
  SizeControl(mCarbonPane, r.right - r.left, r.bottom - r.top);
  Update(true);
  
  /*
  int xoff = (int)xoffset;
  int yoff = (int)yoffset;
  
  ControlFontStyleRec fontStyle;
  fontStyle.flags = kControlUseFontMask | kControlUseJustMask;
  fontStyle.font = kControlFontSmallSystemFont;
  fontStyle.just = teFlushRight;
  
  Rect r;
  OSStatus err = noErr;
  
  // Text editor box
  r.top = DEF_OFFSET + yoff;
  r.bottom = r.top + DEF_TEXT_HEIGHT;
  r.left = DEF_OFFSET + xoff;
  r.right = r.left + DEF_TEXT_WIDTH;
  err = CreateEditUnicodeTextControl(mCarbonWindow, &r, NULL, false, NULL, &m_text);
  SetControlReference(m_text, CTL_TEXT);
  ControlFontStyleRec font;
  font.flags = kControlUseFontMask;
  font.font = kControlFontViewSystemFont;  
  SetControlFontStyle(m_text, &font);
  err = EmbedControl(m_text);
  if(readData()) {
    err = SetControlData(m_text, kControlEditTextPart, kControlEditTextTextTag, m_orig_len, m_orig_text);
    if(err != noErr) {
#ifdef DEBUG
      fprintf(stderr, "Could not set text from file\n");
#endif
    }
  }
  EventTypeSpec events[] = {
    { kEventClassControl, kEventControlSetFocusPart },
    { kEventClassControl, kEventControlClick }
  };
  WantEventTypes(GetControlEventTarget(m_text), GetEventTypeCount(events), events); 
 // ControlKeyFilterUPP proc = StdKeyFilterCallback;
 // SetControlData(m_text, 0, kControlEditTextKeyFilterTag, sizeof(proc), &proc);

  // Import button
  r.top = (DEF_OFFSET * 2) + DEF_TEXT_HEIGHT + yoff;
  r.bottom = r.top + DEF_BUTTON_HEIGHT;
  r.left = xoff + DEF_OFFSET;
  r.right = r.left + DEF_BUTTON_WIDTH;
  err = CreatePushButtonControl(mCarbonWindow, &r, CFSTR("Import"), &m_import_button);
  SetControlReference(m_import_button, CTL_IMPORT);
  err = EmbedControl(m_import_button);
	WantEventTypes(GetControlEventTarget(m_import_button), GetEventTypeCount(events), events);
  
  // Export button
  r.left = r.right + DEF_OFFSET;
  r.right = r.left + DEF_BUTTON_WIDTH;
  err = CreatePushButtonControl(mCarbonWindow, &r, CFSTR("Export"), &m_export_button);
  SetControlReference(m_export_button, CTL_EXPORT);
  err = EmbedControl(m_export_button);
  WantEventTypes(GetControlEventTarget(m_export_button), GetEventTypeCount(events), events);

  // Save button
  r.right = mBottomRight.h;
  r.left = r.right - DEF_BUTTON_WIDTH;
  err = CreatePushButtonControl(mCarbonWindow, &r, CFSTR("Save"), &m_save_button);
  SetControlReference(m_save_button, CTL_SAVE);
  err = EmbedControl(m_save_button);
  WantEventTypes(GetControlEventTarget(m_save_button), GetEventTypeCount(events), events);
  
  // Cancel button
  r.right = r.left - DEF_OFFSET;
  r.left = r.right - DEF_BUTTON_WIDTH;
  err = CreatePushButtonControl(mCarbonWindow, &r, CFSTR("Cancel"), &m_cancel_button);
  SetControlReference(m_cancel_button, CTL_CANCEL);
  err = EmbedControl(m_cancel_button);
  WantEventTypes(GetControlEventTarget(m_cancel_button), GetEventTypeCount(events), events);
  
  // Set size of overall pane
  SizeControl(mCarbonPane, mBottomRight.h + DEF_OFFSET, mBottomRight.v + DEF_OFFSET);
  Update(true);
*/
  return noErr;
}

void NotepadView::dialogEventHandler(NavEventCallbackMessage message,
                                     NavCBRecPtr parms, NavCallBackUserData data) {
  NavReplyRecord navreply;
  NavUserAction useraction;
  
  switch(message) {
    case kNavCBUserAction:
      OSStatus err = NavDialogGetReply(parms->context, &navreply);
      if(err == noErr && navreply.validRecord) {
        useraction = NavDialogGetUserAction(parms->context);
        switch(useraction) {
          AEDesc aeDesc;
          case kNavUserActionSaveAs:
            if(AECoerceDesc(&navreply.selection, typeFSRef, &aeDesc) == noErr) {
              Size dataSize = AEGetDescDataSize(&aeDesc);
              if(dataSize > 0) {
                FSRef fsRefParent;                
                if(AEGetDescData(&aeDesc, &fsRefParent, sizeof(FSRef)) == noErr) {
                  char *dir = new char[MAX_FILENAME];
                  FSRefMakePath(&fsRefParent, (UInt8*)dir, MAX_FILENAME);
                  char *file = new char[MAX_FILENAME];
                  CFStringGetCString(navreply.saveFileName, file, (CFIndex)MAX_FILENAME,
                                     kCFStringEncodingMacRoman);
                  snprintf(_STRBUF, MAX_FILENAME, "%s/%s", dir, file);
                  _STRSET = true;
                  
                  delete [] dir;
                  delete [] file;
                }
              }
            }
            break;
          case kNavUserActionOpen:
            AEKeyword keyword;
            DescType actualtype;
            FSSpec filespec;
            Size actualsize;
            
            if(AEGetNthPtr(&navreply.selection, 1, typeFSS, &keyword, &actualtype,
                           &filespec, sizeof(FSSpec), &actualsize) == noErr) {
              FSRef fileref;
              FSpMakeFSRef(&filespec, &fileref);
              FSRefMakePath(&fileref, (UInt8*)&_STRBUF, MAX_FILENAME);
              _STRSET = true;
            }
              break;
          default:
            break;
        }
      }
      default:
        break;
  }
}

/*
bool NotepadView::HandleEvent(EventRef event) {
  UInt32 eclass = GetEventClass(event);
	UInt32 ekind = GetEventKind(event);
  ControlRef control;
  bool handled = false;
  
  switch(eclass) {
    case kEventClassControl:
      switch(ekind) {
        case kEventControlClick:
          GetEventParameter(event, kEventParamDirectObject, typeControlRef, NULL,
                            sizeof(ControlRef), NULL, &control);
          SInt16 value = GetControlReference(control);
          
          if(value == 0) {
            if(IsControlActive(m_text)) {
              DeactivateControl(m_text);
            }
          }
            
            switch(value) {
              case CTL_SAVE:
#ifdef DEBUG
                fprintf(stderr, "Save button pressed\n");
#endif
                saveData();
                break;
              case CTL_CANCEL:
#ifdef DEBUG
                fprintf(stderr, "Cancel button pressed\n");
#endif
                if(m_orig_len) {
                  if(SetControlData(m_text, kControlEditTextPart, kControlEditTextTextTag,
                                    m_orig_len, m_orig_text) != noErr) {
#ifdef DEBUG
                    fprintf(stderr, "Could not set text from file\n");
#endif
                  }
                  else {
                    DrawOneControl(m_text);
                  }
                }
                  else {
                    SetControlData(m_text, kControlEditTextPart, kControlEditTextTextTag,
                                   0, CFSTR(""));
                    DrawOneControl(m_text);
                  }
                  break;
              case CTL_IMPORT:
              {
#ifdef DEBUG
                fprintf(stderr, "Import button received\n");
#endif
                HiliteControl(m_import_button, kControlButtonPart);
                
                NavDialogCreationOptions *opts = new NavDialogCreationOptions;
                opts->version = kNavDialogCreationOptionsVersion;
                opts->optionFlags = kNavNoTypePopup;
                Point *p = new Point;
                p->h = 100;
                p->v = 100;
                opts->location = *p;
                opts->clientName = CFSTR(DEF_PRODUCT_NAME);
                opts->windowTitle = CFSTR("Import Data...");
                opts->actionButtonLabel = CFSTR("Import");
                opts->cancelButtonLabel = NULL;
                
                opts->saveFileName = NULL;
                opts->message = CFSTR("Choose a file to import data from");
                opts->preferenceKey = 0;
                opts->popupExtension = NULL;
                opts->modality = kWindowModalitySystemModal;
                opts->parentWindow = mCarbonWindow;
                
                NavDialogRef dref;
                if(NavCreateGetFileDialog(opts, NULL, NewNavEventUPP(this->dialogEventHandler),
                                          NULL, NULL, NULL, &dref) != noErr) {
#ifdef DEBUG
                  fprintf(stderr, "Couldn't create put file dialog\n");
#endif
                }
                else {
                  NavDialogRun(dref);
                }
                
                importData();
                saveData();
                handled = true;
                HiliteControl(m_import_button, 0);
              }
                break;
              case CTL_EXPORT:
              {
#ifdef DEBUG
                fprintf(stderr, "Export button received\n");
#endif
                HiliteControl(m_export_button, kControlButtonPart);
                
                // Save the note first
                saveData();
                
                NavDialogCreationOptions *opts = new NavDialogCreationOptions;
                opts->version = kNavDialogCreationOptionsVersion;
                opts->optionFlags = kNavNoTypePopup;
                Point *p = new Point;
                p->h = 100;
                p->v = 100;
                opts->location = *p;
                opts->clientName = CFSTR(DEF_PRODUCT_NAME);
                opts->windowTitle = CFSTR("Export Data...");
                opts->actionButtonLabel = CFSTR("Export");
                opts->cancelButtonLabel = NULL;
                
                char tmpname[MAX_FILENAME];
                float year, month, day;
                AudioUnitGetParameter(GetEditAudioUnit(), PRM_NOTE_YEAR, kAudioUnitScope_Global, 0, &year);
                AudioUnitGetParameter(GetEditAudioUnit(), PRM_NOTE_DAY, kAudioUnitScope_Global, 0, &day);
                AudioUnitGetParameter(GetEditAudioUnit(), PRM_NOTE_MONTH, kAudioUnitScope_Global, 0, &month);
                snprintf(tmpname, MAX_FILENAME, "Note-%04d-%02d-%02d", (int)year, (int)month, (int)day);
                CFStringRef savename = CFStringCreateWithCString(kCFAllocatorDefault, tmpname,
                                                                 kCFStringEncodingMacRoman);
                opts->saveFileName = savename;
                opts->message = CFSTR("Choose a file to save this note to");
                opts->preferenceKey = 0;
                opts->popupExtension = NULL;
                opts->modality = kWindowModalitySystemModal;
                opts->parentWindow = mCarbonWindow;
                
                NavDialogRef dref;
                if(NavCreatePutFileDialog(opts, 'Note', 'Tera',
                                          NewNavEventUPP(this->dialogEventHandler),
                                          NULL, &dref) != noErr) {
#ifdef DEBUG
                  fprintf(stderr, "Couldn't create get file dialog\n");
#endif
                }
                else {
                  NavDialogRun(dref);
                }
                exportData();
                handled = true;
                HiliteControl(m_export_button, 0);
                delete p;
                delete opts;
              }
                break;
              case CTL_TEXT:
#ifdef DEBUG
                fprintf(stderr, "Text control activated\n");
#endif
                if(!IsControlActive(m_text)) {
                  ActivateControl(m_text);
                }
                  handled = false;
                break;
              default:
#ifdef DEBUG
                fprintf(stderr, "%d is not handled\n", value);
#endif
                break;
            }
            break;
        default:
          break;
      }
      break;
    default:
      break;
  }
  
  return handled;
}
 */

bool NotepadView::exportData() {
  if(!_STRSET) {
    return false;
  }
  
#ifdef DEBUG
  fprintf(stderr, "Writing data to '%s'\n", _STRBUF);
#endif
  FILE *fp = fopen(_STRBUF, "w");
  if(fp == NULL) {
    _STRSET = false;
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
    return false;
  }
  else {
    body[(int)s_in] = '\0';
  }
  
  float year, month, day;
  AudioUnitGetParameter(GetEditAudioUnit(), PRM_NOTE_YEAR, kAudioUnitScope_Global, 0, &year);
  AudioUnitGetParameter(GetEditAudioUnit(), PRM_NOTE_DAY, kAudioUnitScope_Global, 0, &day);
  AudioUnitGetParameter(GetEditAudioUnit(), PRM_NOTE_MONTH, kAudioUnitScope_Global, 0, &month);
  
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
  
  _STRSET = false;
  return true;
}

bool NotepadView::importData() {
  if(!_STRSET) {
    return false;
  }
  
#ifdef DEBUG
  fprintf(stderr, "Reading data from '%s'\n", _STRBUF);
#endif
  
  FILE *fp = fopen(_STRBUF, "r");
  if(fp == NULL) {
    _STRSET = false;
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

bool NotepadView::readData() {
  char *dname = new char[MAX_FILENAME];
  
  if(!getProductDir(DEF_PRODUCT_NAME, dname)) {
#ifdef DEBUG
    fprintf(stderr, "Could not get product directory\n");
#endif
    delete [] dname;
    return false;
  }
  
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

bool NotepadView::saveData() {
  char *dname = new char[MAX_FILENAME];
  
  if(!getProductDir(DEF_PRODUCT_NAME, dname)) {
#ifdef DEBUG
    fprintf(stderr, "Could not get product directory\n");
#endif
    delete [] dname;
    return false;
  }
  
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