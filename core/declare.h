#pragma once
#include <cstdint>
#include <queue>
#include <id/versioned_uid.hpp>

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
        Point2D<T>  base;
        Size2D<T>   size;
    };

    enum class MouseButton : int {
        Left,
        Right,
        Middle,
        Invalid,
    };

    enum class SortingOrder {
        Ascent,
        Descent,
    };

    enum class RelationType {
        LeftLeft,
        LeftCenter,
        LeftRight,
        CenterCenter,
        RightRight,
        RightCenter,
        RightLeft,
        Width,
        LeftExtLeft,
        LeftExtRight,
        RightExtLeft,
        RightExtRight,
        //
        TopTop,
        TopMiddle,
        TopBotton,
        MiddleMiddel,
        BottomTop,
        BottomMiddle,
        BottomBottom,
        //
        Height,
        //
        TopExtTop,
        TopExtBottom,
        BottomExtTop,
        BottomExtBottom,
        Size,
    };

    enum class Axis {
        X,
        Y
    };

    class GUIContext;
    class Object;
    class Group;
    class Touch;
    class InputEvent;
    class EventDispatcher;
    class Component;
    class Controller;
    class InputHandler;
    class ObjectDestroyManager;
    class ObjectTable;

    using ObjectUID = comm::VersionedUID;
    using ObjectUIDManager = comm::VersionedUIDManager;

    GUIContext* GetGUIContext();

}