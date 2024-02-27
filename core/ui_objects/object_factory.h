#pragma once

#include "core/declare.h"
namespace gui {

    class ObjectFactory {
    private:
    public:
        static Object* CreateObject(PackageItem* item);
        static Object* createComponent(PackageItem* item);
    };

}