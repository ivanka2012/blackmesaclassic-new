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

install(SCRIPT ${CMAKE_SOURCE_DIR}/MakeLicense.cmake)

add_subdirectory(cl_dll)
add_subdirectory(dlls)
add_subdirectory(modstub)