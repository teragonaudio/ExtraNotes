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

#include <Carbon/Carbon.h>
#include <Quicktime/Quicktime.h>

#include "AUCarbonViewBase.h"
#include "AUControlGroup.h"

#ifndef __defaults_H
#include "defaults.h"
#endif

#define kViewBundleName "org.teragon.AUNotes"
#define kViewMainWindow "MainWindow"

namespace teragon {
  namespace AUNotes {
    class AUNotesView : public AUCarbonViewBase {
    public:
      AUNotesView(AudioUnitCarbonView auv);
      ~AUNotesView();
      
      virtual OSStatus CreateUI(Float32 inXOffset, Float32 inYOffset);
      
      bool exportData();
      bool importData();
      bool readData();
      bool saveData();
      
    private:
    };
  }
}
#endif