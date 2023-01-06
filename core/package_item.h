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
    private:
        Package*                        owner_;
        PackageItemType                 type_;
        ObjectType                      objType_;
        std::string                     id_;
        std::string                     name_;
        std::string                     file_;
        int                             width_;
        int                             height_;
        ByteBuffer*                     rawData_;

        std::vector<std::string>*       branches_;
        std::vector<std::string>*       highResolution_;


    public:
        PackageItem();
    };

}