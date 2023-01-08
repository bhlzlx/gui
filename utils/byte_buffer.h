#pragma once
#include <cstdint>
#include <type_traits>
#include <string>
#include <vector>
#include <compiler_def.h>

namespace gui {

    // 目测序列化FGUI是按小端存储的
    class ByteBuffer {
    public:
        int                         version;
    private:
        uint8_t*                    ptr_;
        int                         offset_;
        int                         length_;
        int                         position_;
        uint8_t                     ownBuffer_ : 1;
        std::vector<std::string>    stringTable_;
    public:
        ByteBuffer(uint8_t* ptr, int offset, int len, bool owner)
            : ptr_(ptr)
            , offset_(offset)
            , length_(len)
            , ownBuffer_(1)
        {}

        ~ByteBuffer() {
            if(ownBuffer_ && ptr_) {
                delete []ptr_;
            }
        }

        int pos() const {
            return position_;
        }

        void skip(int offset) {
            auto tmp = position_;
            position_ += offset;
            if(position_ > length_) {
                position_ = length_;
            }
        }

        template<class T>
        inline T read() {
            static_assert(std::enable_if_t<std::is_pod_v<T>, bool>, "must be pod type!");
            T val;
            #if LITTLE_ENDIAN // 这里需要注意一下大小端问题
            memcpy(&val, ptr_ + offset_ + position_, sizeof(T));
            #else
            uint8_t* dst = (uint8_t*)&val;
            for(size_t i = 0; i<sizeof(T); ++i) {
                dst[sizeof(T)-1-i] = ptr_[offset_+position_+i];
            }
            #endif
            position_ += sizeof(T);
            return val;
        }

        template<>
        inline std::string read<std::string>() {
            std::string val;
            uint16_t len = read<uint16_t>();
            if(len) {
                val.resize(len);
                memcpy(&val[0], ptr_ + position_ + offset_, len);
                position_ += len;
            }
            return val;
        }

        // fgui序列化结构可能是存了几份block
        bool seekToBlock(int indexTablePos, int blockIndex);
        std::string const& readRefString(); // read string index on current location & query the string from `string table` at this index
        void readRefStringArray(std::vector<std::string>& vec, uint32_t count); // similar as `readRefString`
        void updateRefString(std::string const& str); // similar as `readRefString`

    };

}
