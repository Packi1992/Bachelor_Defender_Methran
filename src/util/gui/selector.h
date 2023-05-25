//
// Created by banoodle on 24.05.23.
//

#ifndef BACHELOR_DEFENDER_GUI_SELECTOR_H
#define BACHELOR_DEFENDER_GUI_SELECTOR_H

#include "../../gamebase.h"

class Selector : public Gui {
public:
    void set(Point wSize, string path, string ending);

    void show(Gui **focus);

    string getSelectedFile();

    bool isFileSelected() const;

    void Render() override;

    void Input() override;

    void Update() override;

    void setFocus(Gui *next) override;
    ~Selector();

private:
    void collectFiles();

    void createButtons();

    Point wSize{};
    string _path;
    string _ending;
    string selectedFile;
    Vector<string> maps;
    Vector<Button*> buttons;
    Gui *last{};
    Gui **focus{};
    bool showSelector = false;
    bool fileSelected = false;

    void tidyUp();
};


#endif //BACHELOR_DEFENDER_GUI_SELECTOR_H
