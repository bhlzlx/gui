#include "object.h"
#include <cassert>

namespace gui {

    ObjectUID ObjectTable::allocateID(Object* obj) {
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
        return id;
    }

    void ObjectTable::freeID(Object* obj) {
        auto id = obj->uid();
        auto row = id.number >> BitSize;
        auto index = id.number & RowMask;
        rows_[row][index].obj = nullptr;
        IDManager_.free(id);
    }


}
