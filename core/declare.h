#pragma once
#include <cstdint>
#include <queue>
#include <string>
#include <id/versioned_uid.h>
#include <glm/glm.hpp>

// ugi headers
#include <ugi_declare.h>

namespace gui {

    template<class T>
    using Point2D = glm::vec<2, T, glm::defaultp>;

    template<class T>
    struct Size2D {
        T width;
        T height;
        operator glm::vec<2,T,glm::defaultp>() const {
            return glm::vec<2,T,glm::defaultp>(width, height);
        }
    };

    template<class T>
    struct Rect {
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
            #if BIG_ENDIAN
                uint8_t r, g, b, a; // #rgba
            #else
                uint8_t a, b, g, r; // #rgba
            #endif
            };
            uint32_t val;
        };
        Color4B(uint32_t ival) : val(ival) {}
        Color4B(uint8_t rr, uint8_t gg, uint8_t bb, uint8_t aa)
        #if BIG_ENDIAN
            : r(rr), g(gg), b(bb), a(aa)
        #else
            : a(rr), b(gg), g(bb), r(aa)
        #endif
        {}
        operator uint32_t () const {
            return val;
        }
    };

    struct Color3B {
        #if BIG_ENDIAN
            uint8_t r,g,b;
        #else
            uint8_t b,g,r;
        #endif
        Color3B(uint32_t ival) {
            #if BIG_ENDIAN
                memcpy(this, (uint8_t*)&ival+1, 3);
            #else
                memcpy(this, &ival, 3);
            #endif
        }
        Color3B(uint8_t rr, uint8_t gg, uint8_t bb)
        #if BIG_ENDIAN
            :r(rr), g(gg), b(bb)
        #else
            :b(rr), g(gg), r(bb)
        #endif
        {}
        operator uint32_t () const {
            uint32_t val = 0xffffffff;
            #if BIG_ENDIAN
                memcpy((uint8_t*)&val+1, this, 3);
            #else
                memcpy(&val,this,3);
            #endif
            return val;
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

    enum class ImageScaleOption {
        Grid9,
        Tile,
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
    class InterpoPath;

    struct AtlasSprite {
        PackageItem*    item;
        Rect<float>     rect;
        glm::vec2       origSize;
        glm::vec2       offset;
        bool            rotated;
    };

    struct Userdata {
    };


    template<class T, class Rep, std::enable_if_t<std::is_integral_v<Rep>, bool> v = true>
    class EnumClass {
    private:
        Rep val_;
    public:
        EnumClass(T val = 0) : val_((Rep)val) {}
        EnumClass(Rep val) : val_(val) {}
        operator Rep() const { return val_; }
        operator T() const { return (T)val_; }
    };

    enum class PackageBlockIndex {
        Dependences = 0,
        Items = 1,
        Sprites = 2,
        HitTestData = 3,
        StringTable = 4,
    };

    using ObjectUID = comm::VersionedUID;
    using ObjectUIDManager = comm::VersionedUIDManager;
    using Texture = ugi::Texture;
    using csref = std::string const&;

    GUIContext* GetGUIContext();

    ugi::StandardRenderContext* GetRenderContext();

}