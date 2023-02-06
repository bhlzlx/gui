#pragma once
#include <string>
#include <core/declare.h>
#include <core/ease/ease_type.h>
#include <core/data_types/tween_types.h>

namespace gui {

    enum class TransitionActionType {
        Size,
        Scale,
        Pivot,
        Alpha,
        Rotation,
        Color,
        Animation,
        Visible,
        Sound,
        Transition,
        Shake,
        ColorFilter,
        Skew,
        Text,
        Icon,
        Unknown
    };

    using TransitionHook = std::function<void()>;
    using PlayCompleteCallback = std::function<void()>;

    struct TranstionItem {
        float                   time;
        ObjectUID               targetID;
        TransitionActionType    type;
        TweenConfig*            tweenConfig;
        std::string             label;
        void*                   tval;                  
        TransitionHook          hook;
    };

    class Transition {
    private:
    public:
    };

}