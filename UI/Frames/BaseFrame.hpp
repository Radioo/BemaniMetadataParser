//
// Created by Radio on 18/05/2024.
//

#ifndef BEMANIMETADATAPARSER_BASEFRAME_HPP
#define BEMANIMETADATAPARSER_BASEFRAME_HPP

#include <wx/simplebook.h>
#include <wx/wx.h>
#include <functional>
#include <unordered_map>

#include "../Enums/Page.hpp"
#include "Parser.hpp"

class BaseFrame : public wxFrame {
public:
    explicit BaseFrame(Parser parser);

protected:
    wxSimplebook* simpleBook;

    std::function<void(wxCommandEvent&)> onChangeFrame;

private:
    Parser parser;
    std::unordered_map<Page, std::uint8_t> pageMap;

    void setupMenuBar();

    // Panels
    void setupHomePanel();
    void setupSeriesPanel();
    void setupGamePanel();
    void setupReleasePanel();
    void setupSDVXParserPanel();

    void onExit([[maybe_unused]] wxCommandEvent& event);
    static void onCommitDb([[maybe_unused]] [[maybe_unused]] wxCommandEvent& event);
    void addPage(Page page, wxWindow* panel, const wxString& title);
    void changePage(Page page);
};


#endif //BEMANIMETADATAPARSER_BASEFRAME_HPP
