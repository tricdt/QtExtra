cmake_minimum_required(VERSION 3.16)
set(LIB_MAJOR_VERSION "1")
set(LIB_MINOR_VERSION "0")
set(LIB_PATCH_VERSION "0")
set(LIB_VERSION_STRING "${LIB_MAJOR_VERSION}.${LIB_MINOR_VERSION}.${LIB_PATCH_VERSION}")

set(ENABLE_CUSTOM_ITEMEDITORS ON) #todo: move to config
project(qtwidgetsextra VERSION ${LIB_VERSION_STRING} LANGUAGES CXX)

message(STATUS "${PROJECT_NAME} version=${LIB_VERSION_STRING}")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

cmake_path(SET SUBPROJECT_ROOT "${QT6EXTRA_ROOT}/${PROJECT_NAME}")
message(STATUS "SUBPROJECT_ROOT=${SUBPROJECT_ROOT}")

add_definitions(-DQTWIDGETSEXTRA_MAKEDLL -DQTWIDGETSEXTRA_BUILD_LIB)
if (NOT ENABLE_CUSTOM_ITEMEDITORS)
    add_definitions(-DQTWIDGETSEXTRA_NO_CUSTOMEDITORS)
endif()

find_sources(SUBPROJECT_SOURCES "${SUBPROJECT_ROOT}/src" "cpp")
find_sources(SUBPROJECT_HEADERS "${SUBPROJECT_ROOT}/src" "h")

message(STATUS "SUBPROJECT_SOURCES=${SUBPROJECT_SOURCES}")
message(STATUS "SUBPROJECT_HEADERS=${SUBPROJECT_HEADERS}")

include_directories(${PROJECT_NAME} "${SUBPROJECT_ROOT}/include")
include_directories(${QT6EXTRA_ROOT}/qtextraaux/include)
include_directories(${PROJECT_NAME} "${SUBPROJECT_ROOT}/src/utils")
include_directories(${QT6EXTRA_ROOT}/qtextraaux/include)

add_definitions(-DQTGEOMETRY_DLL)
include_directories(${QT6EXTRA_ROOT}/qtgeometry/include)

add_library(${PROJECT_NAME} SHARED ${SUBPROJECT_SOURCES} ${SUBPROJECT_HEADERS})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets qtgeometry)
add_dependencies(${PROJECT_NAME} qtgeometry)

target_compile_definitions(${PROJECT_NAME} PRIVATE QTWIDGETSEXTRA_LIBRARY)


if (MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_NAME lib${PROJECT_NAME})
    set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_NAME_DEBUG lib${PROJECT_NAME}d)
else()
    set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_NAME ${PROJECT_NAME})
    set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_NAME_DEBUG ${PROJECT_NAME}d)
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${QT6EXTRA_LIB_DIR})
#set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${QT6EXTRA_ROOT}/libs) # for static linkage
