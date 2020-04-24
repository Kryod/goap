CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

PROJECT(goap)
SET(CMAKE_CXX_STANDARD 17)

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/include", "${CMAKE_CURRENT_SOURCE_DIR}/lib")

ADD_EXECUTABLE(
    goap

    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/action.cpp
    ${PROJECT_SOURCE_DIR}/src/world.cpp
    ${PROJECT_SOURCE_DIR}/src/building.cpp
    ${PROJECT_SOURCE_DIR}/src/planner.cpp
    ${PROJECT_SOURCE_DIR}/src/agent.cpp
    ${PROJECT_SOURCE_DIR}/src/map.cpp
    ${PROJECT_SOURCE_DIR}/src/item_stack.cpp
    ${PROJECT_SOURCE_DIR}/src/json_parser.cpp
    ${PROJECT_SOURCE_DIR}/src/actions/bundle_sticks.cpp
    ${PROJECT_SOURCE_DIR}/src/actions/chop_tree.cpp
    ${PROJECT_SOURCE_DIR}/src/actions/wood_cutting.cpp
)

IF (CMAKE_COMPILER_IS_GNUCC)
    TARGET_COMPILE_OPTIONS(goap PRIVATE "-Wall")
ENDIF ()
IF (MSVC)
    TARGET_COMPILE_OPTIONS(goap PRIVATE "/W4")
ENDIF ()
