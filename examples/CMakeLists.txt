cmake_minimum_required(VERSION 3.28)

set(TARGETS
        window
)

foreach(TARGET ${TARGETS})
    add_executable(${TARGET} ${TARGET}.cpp)
    target_link_libraries(${TARGET} PRIVATE hooray)
    set_target_properties(${TARGET} PROPERTIES
            VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    )
endforeach()