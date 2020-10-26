cmake_minimum_required(VERSION 3.15)
include(${CMAKE_SOURCE_DIR}/GetGitRevisionDescription.cmake)
get_git_head_revision(GIT_REFSPEC BMC_GIT_COMMIT)

cmake_policy(SET CMP0091 NEW)
project(BlackMesaClassic VERSION 0.0.1)
include (${CMAKE_ROOT}/Modules/ExternalProject.cmake)

string(COMPARE EQUAL "${CMAKE_BUILD_TYPE}" "" result)
if(result)
    set(CONFIG_TYPE "Debug")
else()
    set(CONFIG_TYPE "${CMAKE_BUILD_TYPE}")
endif()
message("${CONFIG_TYPE} ${CMAKE_BUILD_TYPE}")

ExternalProject_Add(fmt
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/fmt-source
    GIT_REPOSITORY https://github.com/fmtlib/fmt
    GIT_TAG master
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/fmt-build
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/fmt-bin
    CMAKE_CACHE_ARGS
        -DCMAKE_TOOLCHAIN_FILE:STRING=${CMAKE_TOOLCHAIN_FILE}
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/fmt-bin
        -DCMAKE_GENERATOR_TOOLSET:PATH=${CMAKE_GENERATOR_TOOLSET}
        -DCMAKE_C_FLAGS_INIT:STRING=${MSVCFlags}
        -DCMAKE_CXX_FLAGS_INIT:STRING=${MSVCFlags}
        -DFMT_TEST:BOOL=OFF
        -DFMT_PEDANTIC:BOOL=ON
        -DFMT_OS:BOOL=ON
        -DFMT_INSTALL:BOOL=ON
        -DFMT_DOC:BOOL=OFF
    PATCH_COMMAND
        git apply --whitespace=fix --unsafe-paths --verbose --directory ${CMAKE_CURRENT_BINARY_DIR}/fmt-source/src/fmt ${CMAKE_SOURCE_DIR}/fmt-static-msvc.diff
    BUILD_COMMAND ""
    INSTALL_COMMAND
        ${CMAKE_COMMAND} --build . --target install --config ${CONFIG_TYPE}
)

install(SCRIPT ${CMAKE_SOURCE_DIR}/MakeLicense.cmake)

add_subdirectory(cl_dll)
add_subdirectory(dlls)
add_subdirectory(modstub)

add_dependencies(hl fmt)
add_dependencies(client fmt)