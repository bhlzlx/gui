#pragma once
#include <cstdint>
#include <queue>
#include <core/declare.h>
#include <core/events/event_dispatcher.h>

/**
 * @brief Anchor & Pivot
 * anchor跟对象的位置有关系，也就是对象局部坐标的原点。一般anchor是pivot，如果不设置pivot为anchor
 * pivot是变换的中心点
 */


/**
 * @brief UID 和 引用计数
 * uid 可以用来给脚本使用
 * 引用计数可以用来在C++层控制生命周期，C++层存储uid去访问会比较慢。
 */

namespace gui {

    class Object : public EventDispatcher {
    protected:
        ObjectUID       uid_;
        uint32_t        refCount_;
        Point2D<float>  position_;
        Size2D<float>   size_;
        Size2D<float>   rawSize_;
        Point2D<float>  scale_;
        Point2D<float>  pivot_;
        float           alpha_;
        float           rotation_;
        uint8_t         pivotAsAnchor_:1;
        uint8_t         visible_:1;
        uint8_t         grayed_:1;
        uint8_t         finalGrayed_:1;
    private:
        uint8_t         internalVisible_:1;
        uint8_t         handlingController_:1;
        uint8_t         draggable_:1;
        uint8_t         focusable_:1;
        uint8_t         pixelSnapping_:1;
        SortingOrder    sortingOrder_;
        Group*          group_;
        float           sizePercentInGroup_;
    private:
        void setUID_(ObjectUID uid) {
            uid_ = uid;
        }
    public:
        Object();
        void retain() {
            refCount_++;
        }
        void releaes() {
            refCount_--;
        }

        ObjectUID uid() const {
            return uid_;
        }

    };

    class ObjectDestroyManager {
    private:
        std::vector<ObjectUID> destroyList_;
    public:
        void add(ObjectUID uid);
        void tick();
    };

    class ObjectTable {
        struct item_t {
            Object* obj;
            ObjectUID uid;
        };
        static constexpr uint32_t BitSize = 11;
        static constexpr uint32_t RowSize = 1<<BitSize; // 2048
        static constexpr uint32_t RowMask = (1<<BitSize) - 1; // 2048
    private:
        ObjectUIDManager        IDManager_;
        std::vector<item_t*>    rows_;
    public:
        ObjectUID allocateID(Object* obj);
        Object* freeID(ObjectUID uid);
        Object* query(ObjectUID uid);
    };

}