#include "gui_context.h"

namespace gui {

    GUIContext UniqueGUIContext;
    
    GUIContext* GetGUIContext() {
        return &UniqueGUIContext;
    }

    ObjectDestoryManager* GUIContext::destroyManager() {
        return destroyManager_;
    }

    ObjectTable* GUIContext::objectTable() {
        return objectTable_;
    }

}