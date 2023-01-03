#pragma once

namespace gui {

    template<class T>
    struct Point2D {
        T x;
        T y;
    };

    template<class T>
    struct Size2D {
        T width;
        T height;
    };

    template<class T>
    struct Rect2D {
        Point2D     base;
        Size2D      size;
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
    class Component;
    class InputHandler;

}