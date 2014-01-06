/*
 * Copyright (c) 2013 - Teragon Audio LLC
 *
 * Permission is granted to use this software under the terms of either:
 * a) the GPL v2 (or any later version)
 * b) the Affero GPL v3
 *
 * Details of these licenses can be found at: www.gnu.org/licenses
 *
 * This software is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * ------------------------------------------------------------------------------
 *
 * This software uses the JUCE library.
 *
 * To release a closed-source product which uses JUCE, commercial licenses are
 * available: visit www.juce.com for more information.
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
