//
// Created by banoodle on 24.05.23.
//

#ifndef BACHELOR_DEFENDER_GUI_SELECTOR_H
#define BACHELOR_DEFENDER_GUI_SELECTOR_H

#include "../../gamebase.h"

class SelectorDialog : public Gui {
public:
    void set(string path, string ending);

    string getSelectedFile();

    bool isFileSelected() const;

    void Render() override;

    void Input() override;

    void Update() override;

    ~SelectorDialog();

private:
    void collectFiles();

    void createButtons();

    string _path;
    string _ending;
    string selectedFile;
    Vector<string> maps;
    Vector<Button*> buttons;
    bool fileSelected = false;

    void tidyUp();
};


#endif //BACHELOR_DEFENDER_GUI_SELECTOR_H
