#pragma once
#include <core/declare.h>
#include <utils/object_ptr.h>
#include <vector>

namespace gui {

    struct RelationInfo {
        RelationType    type;
        bool            isPercent;
        Axis            axis;
    };

    class RelationItem {
    private:
        ObjectPtr                       owner_;
        ObjectPtr                       target_;
        std::vector<RelationInfo>       infos_;
        Point2D<float>                  targetPos_;
        Size2D<float>                   targetSize_;
    public:
        Object* getTarget() const {
            return target_;
        }
        Object* getOwner() const {
            return owner_;
        }
    };

}