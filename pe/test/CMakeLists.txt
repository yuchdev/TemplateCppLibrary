set(TARGET pe_test)

file(GLOB SOURCES src/pe_test.cpp)
find_package(Boost ${BOOST_MIN_VERSION} COMPONENTS unit_test_framework REQUIRED)
 
include_directories(
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include)

add_executable(${TARGET} ${SOURCES})
target_link_libraries(${TARGET} 
PRIVATE 
    ${Boost_LIBRARIES}
    pe
)
add_test(NAME ${TARGET} COMMAND ${TARGET})
set_property(TARGET ${TARGET} PROPERTY FOLDER "UnitTests")
