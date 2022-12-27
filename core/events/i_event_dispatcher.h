#pragma once 
#include <string/name.h>

namespace gui {

    class IEventDispatcher {
    public:
    };

    comm::Name const* GetEventName(char const* name);

}