#include "object.h"
#include <cassert>
#include <core/gui_context.h>

namespace gui {

    void ObjectDestroyManager::add(ObjectUID uid) {
        destroyList_.push_back(uid);
    }

    void ObjectDestroyManager::tick() {
        auto context = GetGUIContext();
        auto objectTable = context->objectTable();
        for(auto iter = destroyList_.begin(); iter != destroyList_.end(); ++iter) {
            auto uid = *iter;
            auto obj = objectTable->removeRegist(uid);
            // destroy or move to object pool
            // todo
        }
    }

    ObjectUID ObjectTable::registObject(Object* obj) {
        auto id = IDManager_.alloc();
        auto row = id.number >> BitSize;
        auto index = id.number & RowMask;
        if(rows_.size() <= row) {
            assert(rows_.size() == row);
            item_t* row = new item_t[RowSize];
            assert(row);
            rows_.push_back(row);
        }
        rows_[row][index].obj = obj;
        rows_[row][index].uid = id;
        return id;
    }

    Object* ObjectTable::removeRegist(ObjectUID id) {
        auto row = id.number >> BitSize;
        auto index = id.number & RowMask;
        auto obj = rows_[row][index].obj;
        assert(obj != nullptr);
        rows_[row][index].obj = nullptr;
        IDManager_.free(id);
        return obj;
    }

    Object* ObjectTable::query(ObjectUID uid) {
        auto row = uid.number >> BitSize;
        auto index = uid.number & RowMask;
        if(row < rows_.size()) {
            auto item = rows_[row][index];
            if(item.uid.uuid() == uid.uuid()) {
                return item.obj;
            }
            return nullptr;
        }
        return nullptr;
    }

    void Object::release() {
        handle_.reset();
        delete this;
    }

    Object::~Object() {}

}
