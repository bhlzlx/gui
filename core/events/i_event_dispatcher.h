#pragma once 
#include "../declare.h"
#include <string/name.h>
#include <functional>
#include <vector>

namespace gui {

    enum class EventType {
        Touch,
        Rollover,
        Rollout,
    };

    class EventContext {
    private:
        EventType   type_;
        Object*     object_;
        uint8_t     stopped_ : 1;
        uint8_t     defaultPrevented : 1;
        uint8_t     captureTouch_ : 1;
        void*       data_;
    public:
        EventType type() const { return type_; }
        void* data() { return data_; }
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
    public:
        constexpr static EventTag None;
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
        std::vector<EventCallbackItem*>         callbackItems_;
    public:
        void addEventListener(EventType event, EventCallback const& callback, EventTag tag = EventTag::None);
        void removeEventListener(EventType event, EventTag tag = EventTag::None);
        bool hasEventListener(EventType event, EventTag tag = EventTag::None) const;
        bool dispatchEvent(EventType event, void* data, std::vector<uint8_t> const& buffer);
        bool bubbleEvent(EventType event, void* data, std::vector<uint8_t> const& buffer);
    };

    comm::Name GetEventName(char const* name);

}