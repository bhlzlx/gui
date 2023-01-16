#pragma once
#include <core/declare.h>
#include <string>
#include <vector>

namespace gui {

    namespace toolset {

        Color4B hexToColor(const char* str);

        template<class T>
        Rect2D<T> intersection( const Rect2D<T>& a, const Rect2D<T>& b);

        uint32_t findIndexStringArray(std::vector<std::string> const& array, std::string const& str);

    };

}