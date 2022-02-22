/**
 * @file MainFrame.h
 * @author Md Samad
 *
 *
 */

#ifndef AQUARIUM_MAINFRAME_H
#define AQUARIUM_MAINFRAME_H

/**
 *  Initialize MainFrame
 */
class MainFrame : public wxFrame {
private:

public:

    void Initialize();

    void OnExit(wxCommandEvent& event);

    void OnAbout(wxCommandEvent& event);

};

#endif //AQUARIUM_MAINFRAME_H
