#include "i_event_dispatcher.h"

namespace gui {

    constexpr EventTag EventTag::None; 

    namespace {
        comm::NamePool EventNamePool;
    }

    comm::Name GetEventName(char const* name) {
        auto rst = EventNamePool.getName(name);
        return rst;
    }

    void EventDispatcher::addEventListener(EventType event, EventCallback const& callback, EventTag tag) {
        if(tag != EventTag::None) {
            for(auto &item: callbackItems_) {
                if(item->event == event && item->tag == tag) {
                    item->callback = callback;
                    return;
                }
            }
        }
        EventCallbackItem* item = new EventCallbackItem {
            callback,
            event,
            tag,
            0
        };
        callbackItems_.push_back(item);
    }

    void EventDispatcher::removeEventListener(EventType event, EventTag tag) {
        for(auto it = callbackItems_.begin(); it != callbackItems_.end();) {
            auto& itemPtr= *it;
            auto tag = itemPtr->tag;
            if(itemPtr->event == event && (itemPtr->tag != EventTag::None || itemPtr->tag == tag)) {
                if(itemPtr->dispatching) {
                    itemPtr->callback = {};
                    ++it;
                } else {
                    delete itemPtr;
                    it = callbackItems_.erase(it);
                }
            }
        }
    }

    bool EventDispatcher::hasEventListener(EventType event, EventTag tag) const {
        for(auto iter = callbackItems_.begin(); iter != callbackItems_.end(); ++iter) {
            auto item = *iter;
            if(item->callback) {
                if(item->event == event) {
                    if(item->tag) {
                        if(item->tag == tag) {
                            return true;
                        }
                    } else {
                        return true;
                    }
                }
            }
        }
    }
}