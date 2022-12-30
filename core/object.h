#pragma once

namespace gui {

    class UiObjectID {
    private:
    public:
    };

    class Object {
    private:
        uint32_t refCount_;
    public:
        Object();
        void addRef();
        void decRef();
    };

}