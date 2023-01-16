#include "byte_buffer.h"

namespace gui {

    static std::string EmptyString = "";

    std::string const& ByteBuffer::readRefString() {
        auto index = this->read<uint16_t>();
        if(stringTable_->size() > index) {
            return stringTable_->at(index);
        }
        return EmptyString;
    }

    void ByteBuffer::updateRefString(std::string const& str) {
        auto index = this->read<uint16_t>();
        if(stringTable_->size() > index) {
            stringTable_->at(index) = str;
        }
    }

    void ByteBuffer::readRefStringArray(std::vector<std::string>& vec, uint32_t count) {
        for(uint32_t i = 0; i<count; ++i) {
            vec.push_back(readRefString());
        }
    }

    bool ByteBuffer::seekToBlock(int indexTablePos, int blockIndex) {
        auto bak = position_;
        position_ = indexTablePos;
        auto blockCount = read<uint8_t>();
        if(blockIndex<blockCount) {
            bool indexIsInt16 = (read<uint8_t>() == 1); // index is int16_t or int32_t
            int newPos = 0;
            if(indexIsInt16) {
                // read specified block index value
                position_ += sizeof(int16_t) * blockIndex; // locate the position that stores the block's offset
                newPos = read<int16_t>();
            } else {
                position_ += sizeof(int32_t) * blockIndex;
                newPos = read<int32_t>();
            }
            if(newPos>0) {
                position_ = indexTablePos + newPos;
                return true;
            }
        }
        // restore the state
        position_ = bak;
        return false;
    }

}