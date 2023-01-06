#pragma once
#include <cstdint>
#include <queue>
#include <id/versioned_uid.hpp>

//#define GUI_BIG_ENDIAN 

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
        T left() { return base.x; };
        T right() { return base.x + size.width; };
        T top() { return base.y};
        T bottom() { return base.y + size.height; };
    };

    struct Color4B {
        union {
            struct {
            #if GUI_BIG_ENDIAN
                uint8_t r, g, b, a; // #rgba
            #else
                uint8_t a, b, g, r; // #rgba
            #endif
            };
            uint32_t val;
        };
        Color4B(uint32_t ival) : val(ival) {}
        Color4B(uint8_t rr, uint8_t gg, uint8_t bb, uint8_t aa)
            : r(rr), g(gg), b(bb), a(aa)
        {}
        operator uint32_t () const {
            return val;
        }
    };

    struct Color3B {
        #if GUI_BIG_ENDIAN
            uint8_t r,g,b;
        #else
            uint8_t b,g,r;
        #endif
        Color3B(uint32_t ival) {
            #if GUI_BIG_ENDIAN
                memcpy(this, (uint8_t*)&ival+1, 3);
            #else
                memcpy(this, &ival, 3);
            #endif
        }
        Color3B(uint8_t rr, uint8_t gg, uint8_t bb)
            :r(rr), g(gg), b(bb)
        {}
        operator uint32_t () const {
            uint32_t val = 0xffffffff;
            #if GUI_BIG_ENDIAN
                memcpy((uint8_t*)&val+1, this, 3);
            #else
                memcpy(&val,this,3);
            #endif
        }
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
    class Package;
    class PackageItem;
    class Group;
    class Touch;
    class InputEvent;
    class EventDispatcher;
    class Component;
    class Controller;
    class InputHandler;
    class ObjectDestroyManager;
    class ObjectTable;
    class ByteBuffer;

    using ObjectUID = comm::VersionedUID;
    using ObjectUIDManager = comm::VersionedUIDManager;

    GUIContext* GetGUIContext();

}