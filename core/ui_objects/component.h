#pragma once
#include "core/data_types/transition.h"
#include <core/ui_objects/object.h>
#include <vector>

namespace gui {


    class Component :public Object {
    protected:
        std::vector<Object*>        children_;
        std::vector<Controller*>    controllers_;
        // std::vector<Transition>  这个先跳过去
    public: 
    };

}