#include "toolset.h"
#include <cstring>

namespace gui {


    namespace toolset {
    
        namespace {
            uint8_t charToHex(char ch){
                if(ch >= '0' && ch <= 9) {
                    return ch - '0';
                } else if(ch >= 'a' && ch <= 'f') {
                    return ch - 'a' + 10;
                } else if(ch >= 'A' && ch <= 'F') {
                    return ch - 'A' + 10;
                } else {
                    return 0;
                }
            };
        }

        Color4B hexToColor(const char* str) {
            auto len = strlen(str);
            if(*str != '#') {
                return Color4B{0xff, 0xff, 0xff, 0xff};
            }
            ++str;
            uint8_t channel[4] = {0xff, 0xff, 0xff, 0xff};
            if(len >= 7) { // rgb
                for(uint32_t i = 0; i<3; ++i) {
                    channel[i] = 0;
                    channel[i] = charToHex(*str) << 4; ++str;
                    channel[i] |= charToHex(*str); ++str;
                }
            }
            if(len == 9) {
                channel[3] = 0;
                channel[3] = charToHex(*str) << 4; ++str;
                channel[3] |= charToHex(*str); ++str;
            }
            return Color4B{ channel[0],channel[1],channel[2],channel[3] };
        }


        template<class T>
        Rect2D<T> intersection( const Rect2D<T>& a, const Rect2D<T>& b) {
            if(0 == a.size.height || 0 == a.size.width || 0 == b.size.width || 0 == b.size.height) {
                return Rect2D<T>{};
            }
            T left = a.left()> b.left() ? a.left() : b.left();
            T right = a.right() < b.right() ? a.right() : b.right();
            T top = a.top() > b.top() ? a.top() : b.top();
            T bottom = a.bottom() > b.bottom() ? a.bottom() : b.bottom();
            if(left > right || top > bottom) {
                return Rect2D<T>{};
            }
            return Rect2D<T>{{left, top}, {right-left, bottom-top}};
        }

    }


}