/*
  ==============================================================================

    TextEditorParameter.h
    Created: 25 Dec 2013 11:21:38am
    Author:  Nik Reiman

  ==============================================================================
*/

#ifndef TEXTEDITORPARAMETER_H_INCLUDED
#define TEXTEDITORPARAMETER_H_INCLUDED

#include "JuceHeader.h"
#include "PluginParameters.h"

namespace teragon {

class TextEditorParameter : public StringParameter, public TextEditor::Listener {
public:
    TextEditorParameter(ParameterString inName, ParameterString inDefaultValue = "") :
        StringParameter(inName, inDefaultValue), TextEditor::Listener() {}

    virtual ~TextEditorParameter() {}

    virtual void textEditorTextChanged(TextEditor &textEditor) {
        StringParameter::setValue(textEditor.getText().toStdString());
    }
};

} // namespace teragon

#endif  // TEXTEDITORPARAMETER_H_INCLUDED
