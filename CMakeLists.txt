cmake_minimum_required(VERSION 3.0)
project(CMakeComponents)

set(CMAKE_CXX_STANDARD 17)


#Scan subdirectories for files
add_subdirectory(include)
add_subdirectory(src)

#Option for using component type auto-scan
option(SCAN_COMPONENTS "Scan component types from file names automatically" ON)

#Scan components or use manually provided lists depending on the preference
if(SCAN_COMPONENTS)
    message("Scanning component types from file names")

    #Set error message for failed type id query
    set(COMPONENT_TYPE_ERROR_MESSAGE "Component auto-scan was unable to find the component type.\
 Please make sure that component types are defined individually in headers with *Component.hpp postfix.")

    #Scan components
    set(COMPONENT_TYPES "${ENGINE_HEADERS} ${APP_HEADERS}")
    string(REPLACE ";" " " COMPONENT_TYPES "${COMPONENT_TYPES}")
    string(REGEX MATCHALL "[a-zA-Z0-9]+Component.hpp" COMPONENT_TYPES "${COMPONENT_TYPES}")
    string(REPLACE ".hpp" " " COMPONENT_TYPES "${COMPONENT_TYPES}")
    string(REPLACE ";" "" COMPONENT_TYPES "${COMPONENT_TYPES}")

    message("Detected component types: ${COMPONENT_TYPES}")
else()
    message("Component types provided manually")

    #Set error message for failed type id query
    set(COMPONENT_TYPE_ERROR_MESSAGE "Component type not registered in CMakeLists.txt.\
 Please make sure that all components are listed in COMPONENT_TYPES variable.")

    #Engine components
    set(COMPONENT_TYPES "${COMPONENT_TYPES} Type1Component Type2Component")

    #App components
    set(COMPONENT_TYPES "${COMPONENT_TYPES} Type3Component Type4Component")

    message("Provided component types: ${COMPONENT_TYPES}")
endif()

#Parse definitions for component types and forward declarations
string(STRIP "${COMPONENT_TYPES}" COMPONENT_TYPES)
string(REGEX REPLACE "([^ ]+)" "class \\1;" COMPONENT_FORWARD_DECLARATIONS "${COMPONENT_TYPES}")
string(REPLACE ";" "\\\;" COMPONENT_FORWARD_DECLARATIONS "${COMPONENT_FORWARD_DECLARATIONS}")
string(REPLACE " " ", " COMPONENT_TYPES ${COMPONENT_TYPES})


add_library(engine SHARED ${ENGINE_SOURCES})
target_compile_definitions(engine
    PUBLIC
        COMPONENT_TYPES=${COMPONENT_TYPES}
        COMPONENT_FORWARD_DECLARATIONS=${COMPONENT_FORWARD_DECLARATIONS}
        COMPONENT_TYPE_ERROR_MESSAGE="${COMPONENT_TYPE_ERROR_MESSAGE}")
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
