#include "package.h"
#include <io/archive.h>
#include <utils/byte_buffer.h>

namespace gui {


    bool Package::loadFromBuffer(ByteBuffer* buffer) {
        // magic number, version, bool, id, name,[20 bytes], indexTables
        if(buffer->read<uint32_t>() != 0x46475549) {
            return false;
        }
        buffer->version = buffer->read<int>();
        bool v2 = buffer->version >= 2;
        buffer->read<bool>();
        id_ = buffer->read<std::string>();
        name_ = buffer->read<std::string>();
        buffer->skip(20);
        // index tables
        int indexTablePos = buffer->pos();
        int count = 0;
        buffer->seekToBlock(indexTablePos, 4);
    }

}