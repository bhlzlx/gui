#pragma once

namespace gui {

    struct Margin {
        int left, right, top, bottom;
    };

    enum class ChildrenRenderOrder {
        Ascent,
        Descent,
        Arch,
    };

}