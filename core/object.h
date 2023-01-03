#pragma once
#include <cstdint>
#include <queue>
#include <core/declare.h>

/**
 * @brief Anchor & Pivot
 * anchor跟对象的位置有关系，也就是对象局部坐标的原点。一般anchor是pivot，如果不设置pivot为anchor
 * pivot是变换的中心点
 */

namespace gui {

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

    class Object {
    private:
        ObjectUID       uid_;
        uint32_t        refCount_;
        Point2D<float>  position_;
        Size2D<float>   size_;
        Size2D<float>   rawSize_;
        Point2D<float>  pivot_;
        bool            pivotAsAnchor_;

    public:
        Object();
        void addRef() {
            refCount_++;
        }
        void decRef() {
            refCount_--;
        }
    };



}