# ---- Project header ----
set(PE_CLI_TARGET pe_cli)
project(${PE_CLI_TARGET} CXX)

# ---- Frameworks and components ----
find_package(Boost COMPONENTS program_options REQUIRED)

# ---- Target ----
# Load APPCLI_SOURCES
include(sources.cmake)

# Create the application target
add_executable(${PE_CLI_TARGET} ${PE_CLI_SOURCES})

# ---- Global properties ----
# Set the output directory for executables in Debug and Release configurations
set_target_properties(${PE_CLI_TARGET} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>"
)

# ---- Cross-compiler options ----
# Set C++17 as the standard
target_compile_features(${PE_CLI_TARGET} PUBLIC cxx_std_17)

# ---- System-specific options ----

# ---- Include directories ----
target_include_directories(${PE_CLI_TARGET}
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
PRIVATE
    ${CMAKE_SOURCE_DIR}/pe/include
    ${fmt_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
)

# ---- Library dependencies ----
target_link_libraries(${PE_CLI_TARGET}
PRIVATE
  ${Boost_LIBRARIES}
  fmt::fmt
  pe
)
