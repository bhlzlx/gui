#pragma once
#include <core/declare.h>
#include <string>

namespace gui {

    enum class PackageItemType {
        Image,
        MovieClip,
        Sound,
        Component,
        Atlas,
        Font,
        Swf,
        Misc,
        Unknown,
        Spine,
        DragonBones,
    };

    enum class ObjectType {
        Image,
        MovieClip,
        Swf,
        Graph,
        Loader,
        Group,
        Text,
        RichText,
        InputText,
        Component,
        List,
        Label,
        Button,
        ComboBox,
        ProgressBar,
        Slider,
        ScrollBar,
        Tree,
        Loader3D,
    };
    
    class PackageItem {
        friend class Package;
    private:
        Package*                        owner_;
        PackageItemType                 type_;
        ObjectType                      objType_;
        std::string                     id_;
        std::string                     name_;
        std::string                     file_;
        int                             width_;
        int                             height_;
        ByteBuffer*                     rawData_; // 有必要用指针？？？这个后续关注下！

        std::vector<std::string>*       branches_;
        std::vector<std::string>*       highResolution_;

        // if is atlas
        Texture*                        texture_;

        // if is image
        Rect2D<float>*                  scale9Grid_;
        int                             tileGridIndex_;
        bool                            scaledByTile_;
        // HitTestData                  pixelHitTestData_;

        // is is movie clip
        float                           interval_;
        float                           repeatDelay_;
        bool                            swing_;
        // Frames                       frames_; // 这个肯定是需要自己用Texture写一份了

        // component
        std::function<Component*()>     extensionCreator_;
        bool                            translated_;

        // bitmap font
        //BitmapFont*                     bitmapFont_;

        // skeleton
        Point2D<float>                  skeletonAnchor_;

    public:
        PackageItem();
    };

}