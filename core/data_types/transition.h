#pragma once
#include <string>
#include "core/ui_objects/component.h"
#include "core/data_types/tweener.h"
#include <core/declare.h>
#include <core/ease/ease_type.h>
#include <core/data_types/tween_types.h>

#include "../utility/enum_bits.h"

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

    struct TransitionItem {
        float                   time;
        ObjectUID               targetID;
        TransitionActionType    type;
        TweenConfig*            tweenConfig;
        std::string             label;
        void*                   tval;                  
        TransitionHook          hook;
    };

    typedef void(*OnTransitionCompleteFn)(Transition const*);

    class Transition {
    public:
        enum class option_t {
            IgnoreDisplayController = 1,
            AutoStopDisabled = 2,
            AutoStopAtEnd = 4,
        };
    private:
        std::string                         name_;
        Component*                          owner_;
        std::vector<TransitionItem>         items_;
        int                                 totalTimes_;
        int                                 totalTasks_;
        bool                                playing_;
        bool                                paused_;
        float                               ownerBaseX_;
        float                               ownerBaseY_;
        OnTransitionCompleteFn              completeFn_;
        enum_bits<option_t>                 options_;
        bool                                reversed_;
        float                               totalDuration_;
        bool                                autoPlay_;
        int                                 autoPlayTime_; 
        float                               autoPlayDelay_;
        float                               timeScale_;
        bool                                ignoreEngineTimeScale_;
        float                               startTime_;
        float                               endTime_;

        Tweener::TweenCallback              delayedCallDelegate_;
        Tweener::TweenCallback              checkAllDelegate_;
    public:
        Transition(Component* owner);

    private:
        void play_();
    };

}