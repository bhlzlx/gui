#include "component.h"
#include "core/data_types/ui_types.h"
#include "core/declare.h"
#include "core/package.h"
#include "core/package_item.h"
#include "core/ui_objects/object_factory.h"
#include "imgui/imgui.h"
#include "utils/byte_buffer.h"
#include "core/display_objects/display_object.h"
#include "core/controller.h"


namespace gui {

    void Component::constructFromResource() {
        constructFromResource({}, 0);
    }

    void Component::constructFromResource(std::vector<Object*> objectPool, uint32_t index) {
        auto packageItem = this->packageItem_;
        this->name_ = packageItem->name_;
        PackageItem* contentItem = packageItem->getBranch();
        if(!contentItem->translated_) {
            contentItem->translated_ = true;
            // translate ....
        }
        // create bytebuffer ref
        ByteBuffer buff = packageItem->rawData_;
        buff.seekToBlock(0, ComponentBlocks::Props);
        //
        rawSize_.width = buff.read<int>();
        rawSize_.height = buff.read<int>();
        setSize(rawSize_);
        if(buff.read<bool>()) {
            minSize_.width = buff.read<int>();
            maxSize_.width = buff.read<int>();
            minSize_.height = buff.read<int>();
            maxSize_.height = buff.read<int>();
        }
        if(buff.read<bool>()) {
            glm::vec2 pivot = buff.read<glm::vec2>();
            setPivot(pivot, buff.read<bool>());
        }
        if(buff.read<bool>()) {
            margin_ = buff.read<Margin>();
        }
        OverflowType overflowType = (OverflowType)buff.read<uint8_t>();
        if(overflowType == OverflowType::Scroll) {
            int savedPos = buff.pos();
            buff.seekToBlock(0, ComponentBlocks::ScrollData);
            setupScroll(buff);
            buff.setPos(savedPos);
        } else {
            setupOverflow(overflowType);
        }
        if(buff.read<bool>()) {
            Size2D<int> size = buff.read<Size2D<int>>();
            clipSoftness_ = glm::vec2(size.width, size.height);
        }
        // 
        buildingDisplayList_ = true;
        int controllerCount = buff.read<uint16_t>();
        for(int i = 0; i<controllerCount; ++i) {
            int nextPos = buff.read<uint16_t>();
            nextPos += buff.pos();
            Controller* controller = new Controller();
            controllers_.push_back(controller);
            controller->parent_ = this;
            controller->setup(buff);
            buff.setPos(nextPos);
        }
        buff.seekToBlock(0, ComponentBlocks::Children);
        Object* obj = nullptr;
        int childCount = buff.read<uint16_t>();
        for(int i = 0; i<childCount; ++i) {
            auto childData = buff.readShortBuffer();
            childData.seekToBlock<ObjectBlocks>(0, ObjectBlocks::Props);
            auto type = childData.read<ObjectType>();
            std::string itemID = buff.read<std::string>();
            std::string pkgID = buff.read<std::string>();
            PackageItem* pi = nullptr;
            Package* pkg = nullptr;
            if(itemID.size()) {
                pkg = PackageForID(pkgID);
                if(!pkg) {
                    pkg = pi->owner_;
                }
                if(pkg) {
                    pi = pkg->itemByID(itemID);
                } else {
                    pi = nullptr;
                }
            }
            if(pi) {
                obj = ObjectFactory::CreateObject(pi);
                obj->constructFromResource();
            } else {
                obj = ObjectFactory::CreateObject(type);
            }
            obj->underConstruct_ = 1;
            obj->setupBeforeAdd(childData);
            obj->internalSetParent(this);
            children_.push_back(obj);
        }
        // setup relations
        buff.seekToBlock<ComponentBlocks>(0, ComponentBlocks::Relations);
        relations_.setup(buff, true);
        // child relations
        buff.seekToBlock<ComponentBlocks>(0, ComponentBlocks::Children);
        buff.skip(2);
        for(int i = 0; i<childCount; ++i) {
            ByteBuffer childData = buff.readShortBuffer();
            childData.seekToBlock<ObjectBlocks>(0, ObjectBlocks::Relations);
            children_[i]->relations_.setup(childData, false);
        }
        buff.seekToBlock<ComponentBlocks>(0, ComponentBlocks::Children);
        buff.skip(2);
        for(int i = 0; i < childCount; ++i) {
            ByteBuffer childData = buff.readShortBuffer();
            auto child = children_[i];
            child->setupAfterAdd(childData);
            child->underConstruct_ = false;
        }
        buff.seekToBlock<ComponentBlocks>(0, ComponentBlocks::CustomData);
        buff.skip(2);
    }

    void Component::setupScroll(ByteBuffer& buff) {
        if(root_ == container_) {
            container_ = DisplayObject::createDisplayObject();
            root_.addChild(container_);
        }
    }

    void Component::setupOverflow(OverflowType overflow) {
        // 有裁剪和偏移的就得在中间添加一层，方便处理
        if(overflow == OverflowType::Hidden) {
            if(root_ == container_) {
                container_ = DisplayObject::createDisplayObject();
                root_.addChild(container_);
            }
            updateClipRect();
            container_.setPosition({margin_.left, margin_.top});
        } else if(margin_.left != 0 | margin_.top != 0) {
            if(root_ == container_) {
                container_ = DisplayObject::createDisplayObject();
                root_.addChild(container_);
            }
            container_.setPosition({margin_.left, margin_.top});
        }
    }

}