add_executable(simple simple.cpp)

target_link_libraries(simple PRIVATE hooray)

set_target_properties(simple PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/.."
)

########################

add_executable(window window.cpp)

target_link_libraries(window PRIVATE hooray)

set_target_properties(window PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/.."
)

########################

add_executable(swarm swarm.cpp)

target_link_libraries(swarm PRIVATE hooray)

set_target_properties(swarm PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/.."
)

########################

add_executable(mouse mouse.cpp)

target_link_libraries(mouse PRIVATE hooray)

set_target_properties(mouse PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/.."
)