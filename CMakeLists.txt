cmake_minimum_required(VERSION 3.2)

if($ENV{TRAVIS_BUILD_NUMBER}) 
    project(IpTask VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(IpTask VERSION 0.0.3)
endif()

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
find_package (Threads REQUIRED)

configure_file(version.h.in "${CMAKE_CURRENT_SOURCE_DIR}/version.h")

add_subdirectory(
       "${CMAKE_CURRENT_SOURCE_DIR}/googletest"
       googletest
)

add_executable(iptask main.cpp)
add_library(iptask.lib lib.cpp)
add_executable(test_version testboost.cpp)
add_executable(test_version_g testg.cpp)

set_target_properties(iptask  iptask.lib test_version test_version_g gtest gtest_main gmock gmock_main PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(iptask.lib
    PRIVATE "${CMAKE_BINARY_DIR}"
)
set_target_properties(test_version PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(iptask PRIVATE
    iptask.lib
)
target_link_libraries(test_version
    ${Boost_LIBRARIES}
    iptask.lib
)

target_link_libraries(test_version_g
    gtest 
    ${CMAKE_THREAD_LIBS_INIT}
    iptask.lib gtest_main
)

if (MSVC)
    target_compile_options(iptask PRIVATE
        /W4
    )
    target_compile_options(iptask.lib PRIVATE
        /W4
    )
    target_compile_options(test_version PRIVATE
        /W4
    )
    target_compile_options(test_version_g PRIVATE
        /W4
    )
else ()
    target_compile_options(iptask PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(iptask.lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_version PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_version_g PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS iptask RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT lismut@gmail.com)

include(CPack)

enable_testing()

add_test(test_version test_version)
add_test(test_version_g test_version_g)
