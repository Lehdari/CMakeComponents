cmake_minimum_required(VERSION 3.0)
project(CMakeComponents)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)

#Engine components
set(COMPONENT_TYPES "${COMPONENT_TYPES} Type1Component Type2Component")

#App components
set(COMPONENT_TYPES "${COMPONENT_TYPES} Type3Component Type4Component")


#Parse definitions for component types and forward declarations
string(STRIP ${COMPONENT_TYPES} COMPONENT_TYPES)
string(REGEX REPLACE "([^ ]+)" "class \\1;" COMPONENT_FORWARD_DECLARATIONS "${COMPONENT_TYPES}")
string(REPLACE ";" "\\\;" COMPONENT_FORWARD_DECLARATIONS "${COMPONENT_FORWARD_DECLARATIONS}")
string(REPLACE " " ", " COMPONENT_TYPES ${COMPONENT_TYPES})


add_library(engine SHARED ${ENGINE_SOURCES})
target_compile_definitions(engine
    PUBLIC
        COMPONENT_TYPES=${COMPONENT_TYPES}
        COMPONENT_FORWARD_DECLARATIONS=${COMPONENT_FORWARD_DECLARATIONS})
target_include_directories(engine
    PRIVATE
        include
        include/engine)

add_executable(App ${APP_SOURCES})
target_include_directories(App
    PRIVATE
        include
        include/app)

target_link_libraries(App PUBLIC engine)
