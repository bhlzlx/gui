#pragma  once

#include "core/display_objects/display_object.h"
#include <vector>

#include <entt/src/entt/entt.hpp>

namespace gui {

    extern entt::registry reg;

    namespace dispcomp {

        struct children {
            std::vector<DisplayObject> children;
        };

        struct parent {
            entt::entity parent;
        };

        struct is_root {
        };

    }
}