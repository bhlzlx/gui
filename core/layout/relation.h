#pragma once
#include <core/declare.h>
#include <vector>

namespace gui {

    struct RelationInfo {
        RelationType    type;
        bool            isPercent;
        Axis            axis;
    };

    class RelationItem {
    private:
        gui::VersionedUID                  targetUID_;
        Object*                         owner_;
        std::vector<RelationInfo>       infos_;
        Point2D<float>                  targetPos_;
        Size2D<float>                   targetSize_;
    public:
        Object* getTarget() const {
            return 
        }
    };

}