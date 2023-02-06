#pragma once
#include <functional>
#include <core/declare.h>
#include <core/data_types/tween_types.h>

namespace gui {

    enum class TweenPropType {
        None,
        X,
        Y,
        Position,
        Width,
        Height,
        Size,
        ScaleX,
        ScaleY,
        Scale,
        Rotation,
        Alpha,
        Progress
    };

    void SetObjectTweenProps(Object* target, TweenPropType type, TValue const& val);

    class Tweener {
    private:
        using TweenCallback = std::function<void(Tweener*)>;
        using TweenCallbackSimple = std::function<void(Tweener*)>;
    public:
        Tweener();
        ~Tweener();

        Tweener* setDelay(float val);
        Tweener* setDuration(float val);
        Tweener* setBreakpoint(float val);
        Tweener* setEase(EaseType type);
        Tweener* setEasePeriod(float val);
        Tweener* setEaseOvershootOrAmplitude(float val);
        Tweener* setRepeat(int repeat, bool yoyo = false);
        Tweener* setTimeScale(float value);
        Tweener* setSnapping(bool value);
        Tweener* setTargetAny(void* val);
        Tweener* setTarget(ObjectUID uid);
        Tweener* setTarget(ObjectUID uid, TweenPropType type);
        Tweener* setUserData(Userdata const& ud);
        Tweener* setPath(InterpoPath* path);
        Tweener* setUpdateCallback(TweenCallback const& callback);
        Tweener* setStartCallback(TweenCallback const& callback);
        Tweener* setCompleteCallback(TweenCallback const& callback);
        Tweener* setCompleteCallbackSimple(TweenCallbackSimple const& callback);
        Tweener* setPaused(bool paused);

        float getDelay() const;
        float getDuration() const;
        int getRepeat() const;
        void* getTarget() const;
        float getNormalizedTime() const;
        bool isCompleted() const;
        bool allCompleted() const;
        void seek(float time) const;
        void kill(bool complete = false);
        Userdata const& getUserData() const;

        TValue startVal;
        TValue endVal;
        TValue deltaVal;
        TValue val;
    private:
        Tweener* _to(float start, float end, float duration);
        Tweener* _to(const glm::vec2& start, const glm::vec2& end, float duration);
        Tweener* _to(const glm::vec3& start, const glm::vec3& end, float duration);
        Tweener* _to(const glm::vec4& start, const glm::vec4& end, float duration);
        Tweener* _to(const Color4B& start, const Color4B& end, float duration);
        Tweener* _to(double start, double end, float duration);
        Tweener* _shake(const glm::vec2& start, float amplitude, float duration);

        void _init();
        void _reset();
        void _update(float dt);
        void update();
        void callStartCallback();
        void callUpdateCallback();
        void callCompleteCallback();

        void*               target_;
        // cocos2d::Ref* _refTarget;
        TweenPropType       propType_;
        bool                killed_;
        bool                paused_;

        float               delay_;
        float               duration_;
        float               breakpoint_;
        EaseType            easeType_;
        float               easeOvershootOrAmplitude_;
        float               easePeriod_;
        int                 repeat_;
        bool                yoyo_;
        float               timeScale_;
        bool                snapping_;
        Userdata            userdata_;
        int                 valueSize_;
        InterpoPath*        path_;

        TweenCallback       onUpdate_;
        TweenCallback       onStart_;
        TweenCallback       onComplete_;
        TweenCallbackSimple onComplete0_;

        bool                started_;
        int                 ended_;
        float               elapsedTime_;
        float               normalizedTime_;

    };

}