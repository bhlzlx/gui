#include "object_ptr.h"
#include <core/object.h>

namespace gui {

        ObjectPtr::ObjectPtr(ObjectPtr const& ptr) {
            raw_ = ptr.raw_;            
            if(raw_) {
                raw_->retain();
            }
        }

        ObjectPtr::ObjectPtr(ObjectPtr&& ptr) {
            raw_ = ptr.raw_;
            ptr.raw_ = nullptr;
        }

        ObjectPtr::ObjectPtr(Object* ptr) {
            if(ptr != nullptr) {
                ptr->retain();
                raw_ = ptr;
            } else {
                raw_ = nullptr;
            }
        }

        ObjectPtr& ObjectPtr::operator = (ObjectPtr const& ptr) {
            if(raw_) {
                raw_->release();
            }
            raw_ = ptr.raw_;            
            if(raw_) {
                raw_->retain();
            }
            return *this;
        }

        ObjectPtr& ObjectPtr::operator = (ObjectPtr && ptr) {
            if(raw_) {
                raw_->release();
            }
            raw_ = ptr.raw_;            
            if(raw_) {
                raw_->retain();
            }
            return *this;
        }

        bool ObjectPtr::operator == (ObjectPtr const& ptr) const {
            return raw_ == ptr.raw_;
        }

        bool ObjectPtr::operator != (ObjectPtr const& ptr) const {
            return raw_ != ptr.raw_;
        }

        ObjectPtr::~ObjectPtr() {
            if(raw_) {
                raw_->release();
            }
        }

}