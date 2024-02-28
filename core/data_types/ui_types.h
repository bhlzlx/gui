#pragma once

namespace gui {

    struct Margin {
        int left, right, top, bottom;
    };

    enum class FlipType {
        None,
        Hori,
        Vert,
        Both,
    };

    enum class FillMethod {
        None,
        Hori,
        Vert,
        Radial90,
        Radial180,
        Radial360,
    };

    enum class FillOrigin {
        None
    };

    enum class ChildrenRenderOrder {
        Ascent,
        Descent,
        Arch,
    };

    enum class OverflowType {
        Visible,
        Hidden,
        Scroll
    };

}