#pragma once
#include <core/declare.h>
#include <cstdint>

namespace gui {

    class InputEvent {
        Object*         target_;
        Touch*          touch_;
        int             touchID_;
        int             clickCount_;
        int             mouseWheelDelta_;
        uint16_t        keyModifiers_;
        InputHandler*   inputHandler_;
    };

}