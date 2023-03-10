#include "tweener.h"
#include <core/ease/ease.h>
#include <random>
#include <core/data_types/interpolatable_path.h>

namespace gui {

    float rand_0_1() {
        return std::rand() / (float)RAND_MAX;
    }

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
        assert(false);
        // target_ = val;
        return this;
    }

    Tweener* Tweener::setTarget(ObjectUID uid) {
        target_ = uid;
        return this;
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
        return 0 != ended_;
    }

    bool Tweener::allCompleted() const {
        return ended_ == 1;
    }

    void Tweener::seek(float time) {
        if(killed_) {
            return;
        }
        elapsedTime_ = time;
        if(elapsedTime_ < delay_) {
            if(started_) {
                elapsedTime_ = delay_;
            } else {
                return;
            }
        }
        update();
    }

    void Tweener::kill(bool complete = false) {
        if(killed_) {
            return;
        }
        if(complete) {
            if(ended_ == 0) {
                if(breakpoint_ >= 0) {
                    elapsedTime_ = delay_ + breakpoint_;
                } else if( repeat_ >= 0) {
                    elapsedTime_ = delay_ + duration_ * (repeat_+1);
                } else {
                    elapsedTime_ = delay_ + duration_ * 2;
                }
                update();
            }
            callCompleteCallback();
        }
        killed_ = true;
    }

    Userdata const& Tweener::getUserData() const {
        return userdata_;
    }


    void Tweener::_init() {
    }

    void Tweener::_reset() {
    }

    void Tweener::_update(float dt) {
    }

    void Tweener::update() {
        ended_ = 0;
        if(TweenValueType::None == valueType_) {  // ????????????????????????
            if(elapsedTime_ >= delay_ + duration_) {
                ended_ = 1;
            }
            return;
        }
        // ????????????
        if(!started_) {
            if(elapsedTime_ < delay_) { // ???????????????
                return;
            }
            started_ = true;
            callStartCallback();
            if(killed_) { // ???????????????
                return;
            }
        }
        bool reversed = false;
        float exeTime = elapsedTime_ - delay_;
        if(breakpoint_ >= 0 && exeTime >= breakpoint_) {
            exeTime = breakpoint_;
            ended_ = 2; // ???breakpoint??????
        }
        if(repeat_) {
            int round = (int)floor(exeTime/duration_);
            exeTime -= duration_ * round;
            if(yoyo_) {
                reversed = (round % 2 == 1);
            }
            if(repeat_ > 0 && repeat_ - round < 0) {
                if(yoyo_) {
                    reversed = (repeat_ % 2 == 1);
                }
                exeTime = duration_;
                ended_ = 1;
            }
        } else if(exeTime >= duration_) {
            exeTime = duration_;
            ended_ = 1;
        }
        normalizedTime_ = ease::evaluate(easeType_, reversed ? (duration_ - exeTime) : exeTime, duration_, easeOvershootOrAmplitude_, easePeriod_);
        this->val.reset();
        this->deltaVal.reset();

        if(valueType_ == TweenValueType::Double) { // ?????????????????????
            double d = startVal.d + (endVal.d - startVal.d) * normalizedTime_;
            if(snapping_) {
                d = round(d);
            }
            deltaVal.d = d - val.d;
            val.d = d;
            val.x = float(d);
        } else if(valueType_ == TweenValueType::Shake) { // ?????????
            if (ended_ == 0) {
                float r = startVal.val.w * (1 - normalizedTime_);
                float rx = (rand_0_1() * 2 - 1) * r;
                float ry = (rand_0_1() * 2 - 1) * r;
                rx = rx > 0 ? ceil(rx) : floor(rx);
                ry = ry > 0 ? ceil(ry) : floor(ry);
                deltaVal.val.x = rx;
                deltaVal.val.y = ry;
                val.val.x = startVal.val.x + rx;
                val.val.y = startVal.val.y + ry;
            } else {
                val.setVec3(startVal.vec3());
            }
        } else if(path_) { // ????????????
            glm::vec3 v3 = path_->pointAt(normalizedTime_);
            if(snapping_) {
                v3.x = round(v3.x);
                v3.y = round(v3.y);
                v3.z = round(v3.z);
            }
            deltaVal.setVec3(v3 - val.vec3());
            val.setVec3(v3);
        } else { // float/vec2/vec3/vec4
            assert(valueType_ > 0 && valueType_ <= 4);
            for(uint32_t i = 0; i<valueType_; ++i) {
                float fval = startVal.val[i] + (endVal.val[0] - startVal.val[i]) * normalizedTime_;
                if(snapping_) {
                    fval = round(fval);
                }
                deltaVal.val[i] = fval - val.val[i];
                val.val[i] = fval;
            }
        }

        if()
    }

    void Tweener::callStartCallback() {
    }

    void Tweener::callUpdateCallback() {
    }

    void Tweener::callCompleteCallback() {
    }


}