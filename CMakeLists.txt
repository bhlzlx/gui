if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    cmake_minimum_required(VERSION 3.18)
    project(gui)
    add_subdirectory(thirdpart/lwc)
endif()

add_library(gui STATIC)

target_sources(gui 
PRIVATE 
    core/data_types/relation.cpp
    core/data_types/transition.cpp
    core/data_types/interpolatable_path.cpp
    core/data_types/tweener.cpp
    core/data_types/tween_types.cpp
    core/display_objects/display_object.cpp
    core/display_objects/container.cpp
    core/ui_objects/component.cpp
    core/ui_objects/object.cpp
    core/events/event_dispatcher.cpp
    core/events/input_event.cpp
    core/input_handler.cpp
    core/package.cpp
    core/package_item.cpp
    core/gui_context.cpp
    core/hit_test.cpp
    utils/byte_buffer.cpp
    utils/toolset.cpp
)

target_link_libraries(gui
PRIVATE
    LightWeightCommon
    EnTT
    UGI
)

target_include_directories(gui
PRIVATE
    .
)

target_compile_definitions(gui
PRIVATE
    $<$<STREQUAL:${CMAKE_CXX_BYTE_ORDER},"BIG_ENDIAN">: BIG_ENDIAN=1>
)