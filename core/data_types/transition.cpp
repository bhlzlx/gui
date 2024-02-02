#include "transition.h"
#include "tweener.h"

namespace gui {

    Transition::Transition(Component* owner)
        : owner_(owner)
        , timeScale_(1.0f)
        , ignoreEngineTimeScale_(true)
        , delayedCallDelegate_(Tweener::OnDelayedPlay)
        , checkAllDelegate_(Tweener::OnCheckAllComplete)
    {}


}