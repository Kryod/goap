CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

PROJECT(goap)
SET(CMAKE_CXX_STANDARD 17)

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include" "${PROJECT_SOURCE_DIR}/lib")

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
    ${PROJECT_SOURCE_DIR}/src/ui.cpp
    ${PROJECT_SOURCE_DIR}/src/texture_loader.cpp
    ${PROJECT_SOURCE_DIR}/src/font_loader.cpp
    ${PROJECT_SOURCE_DIR}/src/utils.cpp
    ${PROJECT_SOURCE_DIR}/src/actions/bundle_sticks.cpp
    ${PROJECT_SOURCE_DIR}/src/actions/chop_tree.cpp
    ${PROJECT_SOURCE_DIR}/src/actions/wood_cutting.cpp
    ${PROJECT_SOURCE_DIR}/lib/lib.cpp
)

configure_file(${PROJECT_SOURCE_DIR}/conf.json
         ${CMAKE_CURRENT_BINARY_DIR}/conf.json COPYONLY)
         
FIND_PACKAGE(SFML 2 REQUIRED graphics window system)
IF (SFML_FOUND)
    INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})
    TARGET_LINK_LIBRARIES(goap sfml-graphics sfml-window sfml-system)
ENDIF ()

ADD_CUSTOM_COMMAND(TARGET goap POST_BUILD COMMAND "${CMAKE_COMMAND}" -E rm -rf ${CMAKE_BINARY_DIR}/resources DEPENDS goap)
ADD_CUSTOM_COMMAND(TARGET goap POST_BUILD COMMAND "${CMAKE_COMMAND}" -E copy_directory ${PROJECT_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources DEPENDS goap)

IF (CMAKE_COMPILER_IS_GNUCC)
    TARGET_COMPILE_OPTIONS(goap PRIVATE "-Wall")
ENDIF ()
IF (MSVC)
    TARGET_COMPILE_OPTIONS(goap PRIVATE "/W4")
ENDIF ()
