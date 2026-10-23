add_executable(demo demo.cpp)
target_link_libraries(demo PRIVATE hooray)
set_target_properties(demo PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/.."
)

add_executable(window window.cpp)
target_link_libraries(window PRIVATE hooray)
set_target_properties(window PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/.."
)

add_executable(shapes shapes.cpp)
target_link_libraries(shapes PRIVATE hooray)
set_target_properties(shapes PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/.."
)