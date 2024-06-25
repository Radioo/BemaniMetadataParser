//
// Created by Radio on 21/06/2024.
//

#include "UiHelper.hpp"

void UIHelper::setCommonGridAttributes(wxGrid* grid) {
    grid->EnableEditing(false);
    grid->DisableDragRowSize();
    grid->DisableDragColSize();
}

wxString UIHelper::getRowIdValue(wxGrid* grid, wxGridEvent& event) {
    return grid->GetCellValue(event.GetRow(), 0);
}

wxMenu* UIHelper::getGridMenu() {
    auto* menu = new wxMenu;
    menu->Append(wxID_EDIT, wxT("Edit"));
    menu->Append(wxID_DELETE, wxT("Delete"));

    return menu;
}
