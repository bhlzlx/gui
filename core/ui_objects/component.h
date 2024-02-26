#pragma once
#include "core/data_types/ui_types.h"
#include "core/data_types/transition.h"
#include <core/ui_objects/object.h>
#include <vector>
#include "../display_objects/container.h"
#include "core/declare.h"
#include "core/display_objects/display_object.h"

namespace gui {

    class Component :public Object {
    protected:
        std::vector<Object*>        children_;
        std::vector<Controller*>    controllers_;
        std::vector<Transition>     transitions_;
        // std::vector<Transition>  这个先跳过去
        DisplayObject               root_;
        DisplayObject               scrollPane_;

        bool                        buildingDisplayList_;

        Margin                      margin_;

        bool                        traceBounds_;
        bool                        boudingChanged_;
        ChildrenRenderOrder         renderOrder_;
        int                         apexIndex_;
        glm::vec2                   alignOffset_;
        glm::vec2                   clipSoftness_;
        int                         sortingChildrenCount_;
        Controller*                 applyingController_;
    public: 
        Component()
            : children_()
            , controllers_()
            , transitions_()
            , margin_()
        {
        }

        
        

    };

}