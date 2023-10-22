# ---- Project header ----
set(PE_TARGET pe)
project(${PE_TARGET} CXX)

message("BUILD_SHARED_LIBS=" ${BUILD_SHARED_LIBS})
message("CMAKE_BUILD_TYPE=" ${CMAKE_BUILD_TYPE})
message("CMAKE_SYSTEM_VERSION=" ${CMAKE_SYSTEM_VERSION})
message("CMAKE_C_COMPILER=" ${CMAKE_C_COMPILER})
message("CMAKE_CXX_COMPILER=" ${CMAKE_CXX_COMPILER})

# ---- Frameworks and components ----

# ---- Target ----
# Check if building a static or shared library
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

# Load PE_SOURCES
include(sources.cmake)

# Create the library target
add_library(${PE_TARGET} SHARED ${PE_SOURCES})

# ---- Global properties ----
# Set the output directory for shared libraries (DLLs) in Debug and Release configurations
set_target_properties(${PE_TARGET} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>"
)

# ---- Cross-compiler options ----
# Set C++17 as the standard
target_compile_features(${PE_TARGET} PUBLIC cxx_std_17)

# ---- System-specific options ----
# Set Exception handling as exceptions, suppress MSVC security warnings, and use Visual Studio Folders
if(WIN32)
    set(CMAKE_CXX_FLAGS "/EHsc")
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-DDLL_EXPORT)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)    
else()
    # Set the position independent code flag
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

# ---- Include directories ----
target_include_directories(${PE_TARGET}
PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${fmt_SOURCE_DIR}/include
)

# ---- Library dependencies ----
target_link_libraries(${PE_TARGET} 
PRIVATE
    fmt::fmt
)
