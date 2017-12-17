cmake_minimum_required(VERSION 3.2)

set(PROJECT_VERSION_PATCH $ENV{TRAVIS_BUILD_NUMBER})

project(ip_filter VERSION 0.0.${PROJECT_VERSION_PATCH})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in version.h @ONLY)

#Library lib
set( SOURCE_LIB
        lib.cpp
        lex_sort.cpp
        filter.cpp
        split_ip.cpp
        )
set( HEADER_LIB
        lib.h
        lex_sort.h
        filter.h
        split_ip.h
        ip.h
        )
add_library(lib ${SOURCE_LIB} ${HEADER_LIB} )
set_target_properties(lib PROPERTIES
   INCLUDE_DIRECTORIES ${CMAKE_CURRENT_BINARY_DIR}
)

#Program ip_filter
add_executable(ip_filter main.cpp)
set_target_properties(ip_filter PROPERTIES
    INCLUDE_DIRECTORIES ${CMAKE_CURRENT_BINARY_DIR}
)
target_link_libraries(ip_filter
    lib
)

#Test
add_executable(test_ip_filter test.cpp)
set_target_properties(test_ip_filter PROPERTIES
    COMPILE_DEFINITIONS    BOOST_TEST_DYN_LINK
)

target_include_directories(test_ip_filter PUBLIC ${Boost_INCLUDE_DIR} ${Boost_INCLUDE_DIR} )

target_link_libraries(test_ip_filter
    ${Boost_LIBRARIES}
    lib
)

#Дополнительный свойста компилятора для всех проектов
set_target_properties( ip_filter lib test_ip_filter PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS -Wall
)

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT aquila-2004@yandex.ru)

include(CPack)

enable_testing()

add_test(test_ip_filter test_ip_filter)
