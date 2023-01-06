#pragma once
#include <cstdint>
#include <queue>
#include <core/declare.h>
#include <core/events/event_dispatcher.h>
#include <utils/byte_buffer.h>

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
        Object()
            : EventDispatcher()
            , uid_()
            , refCount_(1)
            , position_{}
            , size_{}
            , rawSize_{}
            , scale_{}
            , pivot_{}
            , alpha_(1.0f)
            , rotation_(0.0f)
            , pivotAsAnchor_(0)
            , visible_(1)
            , grayed_(0)
            , finalGrayed_(0)
            , internalVisible_(1)
            , handlingController_(0)
            , draggable_(0)
            , focusable_(0)
            , pixelSnapping_(0)
            , sortingOrder_(SortingOrder::Ascent)
            , group_(nullptr)
            , sizePercentInGroup_(1.0f)
        {}
        void retain() {
            refCount_++;
        }
        void release();

        ObjectUID uid() const {
            return uid_;
        }

protected:
        virtual void onInit();
        virtual void onSizeChanged();
        virtual void onScaleChanged();
        virtual void onGrayedChanged();
        virtual void onPositionChanged();
        virtual void onAlphaChanged();
        virtual void onVisibleChanged();
        virtual void onEnter();
        virtual void onExit();
        virtual void onControllerChanged(Controller* controller);

        virtual void setupBeforeAdd(ByteBuffer* buffer, int startPos);
        virtual void setupAfterAdd(ByteBuffer* buffer, int startPos);

        bool init();

        void updateGear(int index);
        void checkGearDisplay();
        void setSizeDirectly(Size2D<float> const& size);
    private:
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
            Object*         obj;
            ObjectUID       uid;
        };
        static constexpr uint32_t BitSize = 11;
        static constexpr uint32_t RowSize = 1<<BitSize; // 2048
        static constexpr uint32_t RowMask = (1<<BitSize) - 1; // 2048
    private:
        ObjectUIDManager        IDManager_;
        std::vector<item_t*>    rows_;
    public:
        ObjectUID registObject(Object* obj);
        Object* removeRegist(ObjectUID uid);
        Object* query(ObjectUID uid);
    };

}