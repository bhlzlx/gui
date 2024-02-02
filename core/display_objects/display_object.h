#pragma once
#include "../events/event_dispatcher.h"

namespace gui {

    class DisplayObject : public EventDispatcher {
    private:
        std::string         name_;
    public:
    };

}

