cmake_minimum_required(VERSION 3.18)

project(gui)

add_subdirectory(thirdpart/lwc)

add_library(gui STATIC)

target_sources(gui 
PRIVATE 
    core/events/event_dispatcher.cpp
    core/events/input_event.cpp
    core/input_handler.cpp
    core/object.cpp
    core/package.cpp
    core/package_item.cpp
    core/gui_context.cpp
    core/layout/relation.cpp
    utils/byte_buffer.cpp
    utils/toolset.cpp
)

target_link_libraries(gui
PRIVATE
    LightWeightCommon
)

target_include_directories(gui
PRIVATE
    .
)