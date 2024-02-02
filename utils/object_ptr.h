#pragma once

#include <core/declare.h>

namespace gui {

    /**
     * @brief 
     * 内存模型上，等价于一个Object*，所以没有额外的内存开销，放心使用
     * 
     * 这个类用来保证在C++层，C++的逻辑里没有Object的野指针！
     * 特别强调在C++层，是因为以后在Lua层不保证控件一定存在
     * 
     * C++层鼓励使用ObjectPtr
     */

    class ObjectPtr {
    private:
        Object* raw_;
    public:
        ObjectPtr()
            : raw_(nullptr)
        {}

        ObjectPtr(ObjectPtr const& ptr);
        ObjectPtr(ObjectPtr&& ptr);
        ObjectPtr(Object* ptr);

        ObjectPtr& operator = (ObjectPtr const& ptr);
        ObjectPtr& operator = (ObjectPtr && ptr);

        bool operator == (ObjectPtr const& ptr) const;
        bool operator != (ObjectPtr const& ptr) const;

        Object* operator->() const {
            return raw_;
        }
        operator bool() const {
            return nullptr != raw_;
        }
        operator Object*() const {
            return raw_;
        }

        ~ObjectPtr();
    };

}