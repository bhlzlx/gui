#pragma once
#include <core/declare.h>

namespace gui {

    class GUIContext {
    private:
        ObjectDestoryManager* destroyManager_;
        ObjectTable* objectTable_;
    public:
        ObjectDestoryManager* destroyManager();
        ObjectTable* objectTable();
    };

}