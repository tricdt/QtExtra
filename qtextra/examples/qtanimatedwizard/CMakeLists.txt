cmake_minimum_required(VERSION 3.19)
project(qtanimatedwizard LANGUAGES CXX)

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

qt_standard_project_setup()

cmake_path(SET SUBPROJECT_ROOT "${QT6EXTRA_EXAMPLES_ROOT}/${PROJECT_NAME}")
message(STATUS "SUBPROJECT_ROOT=${SUBPROJECT_ROOT}")

add_definitions(-DQTWIDGETSEXTRA_DLL)
include_directories(${QT6EXTRA_ROOT}/qtwidgetsextra/include)



find_sources(SUBPROJECT_SOURCES "${SUBPROJECT_ROOT}" "cpp")
find_sources(SUBPROJECT_HEADERS "${SUBPROJECT_ROOT}" "h")

message(STATUS "SUBPROJECT_SOURCES=${SUBPROJECT_SOURCES}")
message(STATUS "SUBPROJECT_HEADERS=${SUBPROJECT_HEADERS}")

#add_executable(${PROJECT_NAME} MACOSX_BUNDLE WIN32 ${SUBPROJECT_SOURCES} ${SUBPROJECT_HEADERS})
add_executable(${PROJECT_NAME} ${SUBPROJECT_SOURCES} ${SUBPROJECT_HEADERS})
add_dependencies(${PROJECT_NAME} qtwidgetsextra)
target_link_libraries(${PROJECT_NAME} qtwidgetsextra Qt6::Core Qt6::Widgets)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${QT6EXTRA_BIN_DIR})
