#include "component.h"
#include "core/declare.h"
#include "core/package_item.h"
#include "utils/byte_buffer.h"


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
        ByteBuffer<ComponentBlocks> buff(packageItem->rawData_.ptr() + packageItem->offset(), 0, packageItem->rawData_.pos());
    }

}