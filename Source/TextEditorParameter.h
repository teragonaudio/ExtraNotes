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

class TextEditorParameter : public StringParameter, public TextEditor::Listener, public MouseListener {
public:
    TextEditorParameter(const ParameterString &inName,
                        const ParameterString &inDefaultValue = "") :
    StringParameter(inName, inDefaultValue), TextEditor::Listener(), MouseListener(),
    defaultValue(inDefaultValue), textEditor(nullptr) {}

    virtual ~TextEditorParameter() {}

    virtual void mouseUp(const MouseEvent &event) {
        if(getDisplayText() == defaultValue && textEditor != nullptr) {
            textEditor->setText(String::empty, false);
        }
    }

    virtual void setTextEditor(TextEditor *inTextEditor) {
        this->textEditor = inTextEditor;
    }

    virtual void textEditorTextChanged(TextEditor &textEditor) {
        syncParameterValue(textEditor);
    }

    virtual void textEditorEscapeKeyPressed(TextEditor &textEditor) {
        syncParameterValue(textEditor);
        textEditor.unfocusAllComponents();
    }

protected:
    virtual void syncParameterValue(TextEditor &textEditor) {
        String text = textEditor.getText();
        // Warning: may cause priority inversion, bypasses the normal event queues
        StringParameter::setValue(text.toRawUTF8(), (const size_t)text.length());
    }

private:
    const ParameterString defaultValue;
    TextEditor *textEditor;
};

} // namespace teragon

#endif  // TEXTEDITORPARAMETER_H_INCLUDED
