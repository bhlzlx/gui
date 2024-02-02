#pragma once 
#include "../declare.h"
//#include <string/name.h>
#include <functional>
#include <vector>
#include <concepts>
#include "../data_types/handle.h"
#include "core/data_types/handle.h"
#include "core/data_types/value.h"

namespace gui {

    enum class EventType {
        Touch,
        Rollover,
        Rollout,
    };

    class EventContext {
    private:
        EventType           event_;
        Handle              sender_;
        uint8_t             stopped_ : 1;
        uint8_t             defaultPrevented_ : 1;
        uint8_t             captureTouch_ : 1;
        Value               data_;
    public:
        EventContext(EventType event, EventDispatcher* sender, void* data);
        EventType event() const { return event_; }
        Value const& data() const { return data_; }
    };

    class EventTag {
    private:
        size_t tag_;
    public:
        constexpr EventTag() : tag_(0) { }
        EventTag(size_t tag) : tag_(tag) { }
        EventTag(void* ptr) : tag_((size_t)ptr) { }
        operator size_t() const { return tag_; };
        bool operator !=( EventTag& tag ) {
            return tag_ != tag.tag_;
        }
        bool operator ==(EventTag& tag ) {
            return tag_ == tag.tag_;
        }
        operator bool() const {
            return tag_ != 0;
        }
    };

    using EventCallback = std::function<void(EventContext* context)>;

    class EventDispatcher {
        struct EventCallbackItem {
            EventCallback   callback;
            EventType       event;
            EventTag        tag;
            int             dispatching;
        };
    private:
        ObjectHandle                            handle_;
        std::vector<EventCallbackItem*>         callbackItems_;
    public:
        EventDispatcher()
            : callbackItems_ {}
        {}
        void addEventListener(EventType event, EventCallback const& callback, EventTag tag = EventTag());
        void removeEventListener(EventType event, EventTag tag = EventTag());
        bool hasEventListener(EventType event, EventTag tag = EventTag()) const;
        bool dispatchEvent(EventType event, void* data, Value dataValue);
        bool bubbleEvent(EventType event, void* data, std::vector<uint8_t> const& buffer);
        // template<class T>
        // requires std::sub
        Handle getHandle() {
            return handle_.handle();
        }
    };

    // comm::Name GetEventName(char const* name);

}