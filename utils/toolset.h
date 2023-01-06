#pragma once
#include <core/declare.h>

namespace gui {

    namespace toolset {

        Color4B hexToColor(const char* str);

        template<class T>
        Rect2D<T> intersection( const Rect2D<T>& a, const Rect2D<T>& b);

    };

}