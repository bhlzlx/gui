#include "InterpolatablePath.h"

namespace gui {

    PathPoint::PathPoint(glm::vec3 const& p)
        : pos(p)
        , control0()
        , control1()
        , curveType(CurveType::Straight)
    {}

    PathPoint::PathPoint(glm::vec3 const& p, glm::vec3 const& ctrl)
        : pos(p)
        , control0(ctrl)
        , control1()
        , curveType(CurveType::Bezier)
    {}

    PathPoint::PathPoint(glm::vec3 const& p, glm::vec3 const& ctrl0, glm::vec3 const& ctrl1)
        : pos(p)
        , control0(ctrl0)
        , control1(ctrl1)
        , curveType(CurveType::CubicBezier)
    {}

    PathPoint::PathPoint(glm::vec3 const& p, CurveType type) {
        : pos(p)
        , control0()
        , control1()
        , curveType(type)
    {}

    void InterpoPath::createSplineSegment() {
        int cnt = (int)splinePoints.size();
        splinePoints.insert(splinePoints.begin(), splinePoints[0]);
        splinePoints.push_back(splinePoints[cnt]);
        splinePoints.push_back(splinePoints[cnt]);
        cnt += 3;

        Segment seg;
        seg.type = GPathPoint::CurveType::CRSpline;
        seg.ptStart = (int)_points.size();
        seg.ptCount = cnt;
        for (auto& it : splinePoints)
            _points.push_back(it);

        seg.length = 0;
        for (int i = 1; i < cnt; i++)
            seg.length += splinePoints[i - 1].distance(splinePoints[i]);
        _fullLength += seg.length;
        _segments.push_back(seg);
        splinePoints.clear();
    }

    glm::vec3 InterpoPath::onCRSplineCurve(int start, int count, float t) {

    }

    glm::vec3 InterpoPath::onBezierCurve(int start, int count, float t) {

    }

    InterpoPath::InterpoPath() {

    }

    void InterpoPath::create(PathPoint const* points, int count) {

    }

    void InterpoPath::clear() {

    }

    glm::vec3 InterpoPath::pointAt() const {

    }

    float InterpoPath::length() const {

    }

    int InterpoPath::segmentCount() const {

    }

    float InterpoPath::segmentLength(int segmentIndex) const {

    }

    void InterpoPath::queryPoints(int segment, float t0, float t1, std::vector<glm::vec3>& points, std::vector<float>* ts , float density ) const {

    }

    void InterpoPath::queryPoints(std::vector<glm::vec3>& points, float density) const {

    }


}