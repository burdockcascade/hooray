add_executable(swarm swarm.cpp)

target_link_libraries(swarm PRIVATE hooray)

set_target_properties(swarm PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/.."
)