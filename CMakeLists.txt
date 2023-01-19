if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    cmake_minimum_required(VERSION 3.18)
    project(gui)
    add_subdirectory(thirdpart/lwc)
endif()

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
    core/hit_test.cpp
    core/component.cpp
    utils/byte_buffer.cpp
    utils/toolset.cpp
    utils/object_ptr.cpp
)

target_link_libraries(gui
PRIVATE
    LightWeightCommon
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