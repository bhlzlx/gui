#pragma  once

#include "core/data_types/handle.h"
#include "core/display_objects/display_object.h"
#include <vector>

#include <entt/src/entt/entt.hpp>

namespace gui {

    extern entt::registry reg;

    namespace dispcomp {

        struct children {
            std::vector<DisplayObject> val;
        };

        struct parent {
            entt::entity val;
        };

        struct is_root {
        };

        struct owner {
            Handle val;
        };

    }
}