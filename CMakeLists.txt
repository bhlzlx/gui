cmake_minimum_required(VERSION 3.18)

project(gui)

add_subdirectory(thirdpart/lwc)

add_library(gui STATIC)

target_sources(gui 
PRIVATE 
    core/events/event_dispatcher.cpp
    core/object.cpp
)

target_link_libraries(gui
PRIVATE
    LightWeightCommon
)