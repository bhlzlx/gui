#pragma once
#include <cstdint>
#include <queue>

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
        ObjectUID       uuid_;
        uint32_t        refCount_;
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