# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

cmake_minimum_required(VERSION 3.12)
project(Qt6Extra)

#set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

get_filename_component(QT6EXTRA_ROOT "${CMAKE_SOURCE_DIR}" ABSOLUTE)
cmake_path(SET QT6EXTRA_ROOT "${QT6EXTRA_ROOT}") # source root directiory
cmake_path(SET QT6EXTRA_BIN_DIR "${QT6EXTRA_ROOT}/bin") # binaries output directiory
cmake_path(SET QT6EXTRA_LIB_DIR "${QT6EXTRA_BIN_DIR}/libs") # libraries output directiory
cmake_path(SET QT6EXTRA_PLUGIN_DIR "${QT6EXTRA_BIN_DIR}/plugins") # plugins output directiory

# ---- scan for source files ----
function(find_sources output source_dir extension)
    file(GLOB_RECURSE _pathlist "${source_dir}/*.${extension}")
    set(${output} ${_pathlist} PARENT_SCOPE)
endfunction()

message(STATUS "Configuring Auxiliary Module")
add_subdirectory(qtextraaux)

message(STATUS "Configuring QtGeometry Module")
add_subdirectory(qtgeometry)

message(STATUS "Configuring QtWidgetsExtra Module")
add_subdirectory(qtwidgetsextra)

message(STATUS "Configuring Examples")
add_subdirectory(examples)
