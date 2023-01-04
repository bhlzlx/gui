#pragma once
#include <cstdint>
#include <queue>

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
        RightLeft,
        RightCenter,
        RightRight,
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

    class Object;
    class Group;
    class Touch;
    class InputEvent;
    class EventDispatcher;
    class Component;
    class InputHandler;

    struct ObjectUID {
        union {
            struct {
                uint32_t ver : 8;
                uint32_t number : 24;
            };
            uint32_t uuid;
        };
    };
    static constexpr ObjectUID InvalidUID = {0, 0};

    static_assert(sizeof(ObjectUID) == sizeof(uint32_t), "");

    class ObjectUIDManager {
    private:
        uint32_t                counter_;
        std::queue<ObjectUID>   freeList_;
    public:
        void free(ObjectUID id) {
            ++id.ver;
            freeList_.push(id);
        }
        ObjectUID alloc() {
            if(freeList_.size()) {
                auto rst = freeList_.front();
                freeList_.pop();
                return rst;
            } else {
                if(counter_ & ~0xffffff) { // 超过最大限了
                    return {}; // invalid id
                } else {
                    return ObjectUID{0, ++counter_}; // 从1开始计算
                }
            }
        }
    };

}