cmake_minimum_required(VERSION 3.14)

# ---- Header ----
project(
    PortableExecutableEditor
    VERSION 1.0.0
    DESCRIPTION "Short description"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

# Set policies and stop the script on the first error
cmake_policy(SET CMP0046 NEW)
cmake_policy(SET CMP0065 NEW)

# ---- Global properties ----
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# ---- Frameworks and components ----
include(FetchContent)
# Include fmt library using FetchContent
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG master
)
FetchContent_MakeAvailable(fmt)

# ---- Global properties ----
# define WIN32 macro version
# param version: output for Windows version, for example 0x0601 for Windows 7 SP1
macro(get_win32_winnt version)

    if (WIN32 AND CMAKE_SYSTEM_VERSION)
        set(ver ${CMAKE_SYSTEM_VERSION})
        string(REPLACE "." "" ver ${ver})
        string(REGEX REPLACE "([0-9])" "0\\1" ver ${ver})

        set(${version} "0x${ver}")
    endif()

endmacro(get_win32_winnt)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# VS Folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

add_subdirectory(pe)
add_subdirectory(pe-cli)

set(libpeconv_INCLUDE_DIR ${libpeconv_SOURCE_DIR}/include)
message("libpeconv_INCLUDE_DIR=" ${libpeconv_INCLUDE_DIR})

# Set the startup project and working directory for debugging
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PE_CLI_TARGET})
set_property(TARGET ${PE_CLI_TARGET} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")

# ---- System-specific options ----
if(WIN32)
    get_win32_winnt(ver)
    add_definitions(-D_WIN32_WINNT=${ver})
endif()
