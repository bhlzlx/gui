#include "package_item.h"


namespace gui {

    PackageItem::PackageItem()
        : owner_(nullptr)
        , type_(PackageItemType::Component)
        , objType_(ObjectType::Component)
        , id_()
        , name_()
        , file_()
        , width_(0)
        , height_(0)
        , rawData_(nullptr)
        , branches_()
        , highResolution_()
        , texture_(nullptr)
        , scaledByTile_(false)
        , tileGridIndex_(0)
        , interval_(0.0f)
        , repeatDelay_(0.0f)
        , swing_(false)
        , extensionCreator_()
        , translated_(false)
        , skeletonAnchor_{}
    {}

    PackageItem::~PackageItem() {
        if(scale9Grid_) {
            delete scale9Grid_;
        }
        if(rawData_) {
            delete rawData_;
        }
        if(anim)
    }
}