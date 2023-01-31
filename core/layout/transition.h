#pragma once
#include <string>
#include <core/declare.h>
#include <core/ease/ease_type.h>

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

    struct TValue {
        glm::vec4 val; 

        glm::vec2 vec2() const;
        glm::vec2 vec4() const;
        Color4B color4B() const;

        void setVec2(glm::vec2 const& v);
        void setVec4(glm::vec2 const& v);
        void setColor4B(Color4B const& v);
    };

    struct TweenConfig {
        float       duration;
        EaseType    easeType;
        int         repeat;
        bool        yoyo;
        //
        TValue*     startValue;
        TValue*     endValue;
    };

    struct TranstionItem {
        float               time;
        ObjectUID           targetID;
    };

    class Transition {
    private:
    public:
    };

}