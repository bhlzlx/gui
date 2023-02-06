#pragma once
#include <core/object.h>
#include <vector>

namespace gui {

    class Component :public Object {
    protected:
        std::vector<Object*>        children_;
        std::vector<Controller*>    controllers_;
        // std::vector<Transition>
    public: 
    };

}