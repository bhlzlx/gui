#pragma once

namespace gui {

    template<class T>
    struct Point2D {
        T x;
        T y;
    };

    enum class MouseButton : int {
        Left,
        Right,
        Middle,
        Invalid,
    };
    class Object;
    class Touch;
    class InputEvent;
    class EventDispatcher;

}