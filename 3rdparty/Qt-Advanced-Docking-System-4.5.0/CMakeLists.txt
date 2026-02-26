cmake_minimum_required(VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if (POLICY CMP0091)
  cmake_policy(SET CMP0091 NEW)
endif (POLICY CMP0091)

# 显式设置版本号以避免git标签获取失败
set(ADS_VERSION "4.5.0")
set(VERSION_SHORT "4.5.0")
set(VERSION_SONAME "4")

# 设置PROJECT_VERSION相关变量以支持资源文件生成
set(PROJECT_VERSION_MAJOR 4)
set(PROJECT_VERSION_MINOR 5)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION_STRING "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
set(PROJECT_GIT_HASH "unknown")
set(PROJECT_GIT_HASH_SHORT "unknown")
set(PROJECT_NAME "QtAdvancedDockingSystem")

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

# By default, the version information is extracted from the git index. However,
# we can override this behavior by explicitly setting ADS_VERSION and
# skipping the git checks. This is useful for cases where this project is being
# used independently of its original git repo (e.g. vendored in another project)
# if(NOT ADS_VERSION)
#     set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})
#     include(GetGitRevisionDescription)
#     git_describe(GitTagVersion --tags)
#     string(REGEX REPLACE "^([0-9]+)\\..*" "\\1" VERSION_MAJOR "${GitTagVersion}")
#     string(REGEX REPLACE "^[0-9]+\\.([0-9]+).*" "\\1" VERSION_MINOR "${GitTagVersion}")
#     string(REGEX REPLACE "^[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" VERSION_PATCH "${GitTagVersion}")
#     set(VERSION_SHORT "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
#     set(VERSION_SONAME "${VERSION_MAJOR}")
# else()
#     string(REGEX MATCHALL "[\.]" VERSION_DOT_MATCHES ${ADS_VERSION})
#     list(LENGTH VERSION_DOT_MATCHES VERSION_DOT_COUNT)
#     if(VERSION_DOT_COUNT EQUAL 2)
#         set(VERSION_SHORT ${ADS_VERSION})
#         string(REGEX REPLACE "^([0-9]+)\\..*" "\\1" VERSION_SONAME "${ADS_VERSION}")
#     else()
#         message(FATAL_ERROR "ADS_VERSION must be in major.minor.patch format, e.g. 3.8.1. Got ${ADS_VERSION}")
#     endif()
# endif()


project(QtADS LANGUAGES CXX VERSION ${VERSION_SHORT})

option(BUILD_STATIC "Build the static library" OFF)
option(BUILD_EXAMPLES "Build the examples" ON)

if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
    set(ads_PlatformDir "x86")
else()
    set(ads_PlatformDir "x64")
endif()

add_subdirectory(src)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
    add_subdirectory(demo)
endif()