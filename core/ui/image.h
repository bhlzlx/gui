#pragma  once

#include "core/data_types/ui_types.h"
#include "core/declare.h"
#include "core/display_objects/display_object.h"
#include "core/n_texture.h"
#include "object.h"

namespace gui {

    class Image : public Object {
    private:
        Color4B             color_;
        FlipType            flip_;
        FillMethod          fillMethod_;
        FillOrigin          fillOrigin_;
        float               fillAmount_; 
        bool                clockwise_;
        NTexture            texture_;
    public:
        Image()
            : Object()
            , color_(0)
            , flip_(FlipType::None)
            , fillMethod_(FillMethod::None)
            , fillOrigin_(FillOrigin::None)
            , fillAmount_(1.0f)
            , clockwise_(true)
            , texture_()
        {
        }

    };

}