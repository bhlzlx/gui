#include "byte_buffer.h"

namespace gui {

    constexpr std::string EmptyString;

    std::string const& ByteBuffer::readRefString() {
        auto index = this->read<uint16_t>();
        if(stringTable_.size() > index) {
            return stringTable_[index];
        }
        return EmptyString;
    }

    void ByteBuffer::updateRefString(std::string const& str) {
        auto index = this->read<uint16_t>();
        if(stringTable_.size() > index) {
            stringTable_[index] = str;
        }
    }

    void ByteBuffer::readRefStringArray(std::vector<std::string>& vec) {

    }


    bool ByteBuffer::seekToBlock(int indexTablePos, int blockIndex) {
        auto bak = position_;
        position_ = indexTablePos;
    }

}