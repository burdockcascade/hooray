add_executable(window window.cpp)

target_link_libraries(window PRIVATE hooray)

set_target_properties(window PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/.."
)