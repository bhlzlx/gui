#include "tweener.h"

namespace gui {

    Tweener* Tweener::setDelay(float val) {
        delay_  = val;
        return this;
    }

    Tweener* Tweener::setDuration(float val) {
        duration_ = val;
        return this;
    }

    Tweener* Tweener::setBreakpoint(float val) {
        breakpoint_ = val;
        return this;
    }

    Tweener* Tweener::setEase(EaseType type) {
        easeType_ = type;
        return this;
    }

    Tweener* Tweener::setEasePeriod(float val) {
        easePeriod_ = val;
        return this;
    }

    Tweener* Tweener::setEaseOvershootOrAmplitude(float val) {
        easeOvershootOrAmplitude_ = val;
        return this;
    }

    Tweener* Tweener::setRepeat(int repeat, bool yoyo = false) {
        repeat_ = repeat;
        yoyo_ = yoyo;
        return this;
    }

    Tweener* Tweener::setTimeScale(float value) {
        timeScale_ = value;
        return this;
    }

    Tweener* Tweener::setSnapping(bool value) {
        snapping_ = value;
        return this;
    }

    Tweener* Tweener::setTargetAny(void* val) {
        target_ = val;
        return this;
    }

    Tweener* Tweener::setTarget(ObjectUID uid) {
    }

    Tweener* Tweener::setTarget(ObjectUID uid, TweenPropType type) {
    }

    Tweener* Tweener::setUserData(Userdata const& ud) {
        userdata_ = ud;
        return this;
    }

    Tweener* Tweener::setPath(InterpoPath* path) {
        path_ = path;
        return this;
    }

    Tweener* Tweener::setUpdateCallback(TweenCallback const& callback) {
        onUpdate_ = callback;
        return this;
    }

    Tweener* Tweener::setStartCallback(TweenCallback const& callback) {
        onStart_ = callback;
        return this;
    }

    Tweener* Tweener::setCompleteCallback(TweenCallback const& callback) {
        onComplete_ = callback;
        return this;
    }

    Tweener* Tweener::setCompleteCallbackSimple(TweenCallbackSimple const& callback) {
        onComplete0_ = callback;
        return this;
    }

    Tweener* Tweener::setPaused(bool paused) {
        paused_ = paused;
        return this;
    }

    float Tweener::getDelay() const {
        return delay_;
    }

    float Tweener::getDuration() const {
        return duration_;
    }

    int Tweener::getRepeat() const {
        return repeat_;
    }

    void* Tweener::getTarget() const {
        return target_;
    }

    float Tweener::getNormalizedTime() const {
        return normalizedTime_;
    }

    bool Tweener::isCompleted() const {
        return ended_;
    }

    bool Tweener::allCompleted() const {

    }

    void Tweener::seek(float time) const {

    }

    void Tweener::kill(bool complete = false) {

    }

    Userdata const& Tweener::getUserData() const {

    }

}