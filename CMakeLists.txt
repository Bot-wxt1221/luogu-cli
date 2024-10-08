cmake_minimum_required(VERSION 3.15)

# set the project name
project(LuoguCLI)

SET(SRC_LIST src/main.c src/secret.c src/network.c src/csrf.c)

find_package(PkgConfig REQUIRED)

pkg_check_modules(LIBSECRET REQUIRED libsecret-1)
MESSAGE(STATUS "libsecret dirs:" ${LIBSECRET_INCLUDE_DIRS})
include_directories(${LIBSECRET_INCLUDE_DIRS})
link_directories(${LIBSECRET_LIBRARY_DIRS})

pkg_check_modules(JSON_C REQUIRED json-c)
MESSAGE(STATUS "json-c dirs:" ${JSON_C_INCLUDE_DIRS})
include_directories(${JSON_C_INCLUDE_DIRS})
link_directories(${JSON_C_LIBRARY_DIRS})

pkg_check_modules(CURL REQUIRED libcurl)
MESSAGE(STATUS "curl dirs:" ${CURL_INCLUDE_DIRS})
include_directories(${CURL_INCLUDE_DIRS})
link_directories(${CURL_LIBRARY_DIRS})

pkg_check_modules(LIBXML REQUIRED libxml-2.0)
MESSAGE(STATUS "libxml dirs:" ${LIBXML_INCLUDE_DIRS})
include_directories(${LIBXML_INCLUDE_DIRS})
link_directories(${LIBXML_LIBRARY_DIRS})

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${LIBSECRET_LIBRARIES} ${JSON_C_LIBRARIES} ${CURL_LIBRARIES} ${LIBXML_LIBRARIES})

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
