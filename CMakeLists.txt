# This file is in root dir to project
# NOTE: DO NOT use ${PROJECT_BINARY_DIR}
#       DO NOT compile symtable.cc alone!
PROJECT(IEC_COMPILER)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src/parser ${PROJECT_SOURCE_DIR}/src/symtable ${PROJECT_SOURCE_DIR}/src/absyntax ${PROJECT_SOURCE_DIR}/src/absyntax_utils ${PROJECT_SOURCE_DIR}/src/generator ${PROJECT_SOURCE_DIR}/src/semantics ${PROJECT_SOURCE_DIR}/src/generator/utility)
ADD_SUBDIRECTORY(src)
