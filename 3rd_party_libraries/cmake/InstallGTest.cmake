# GoogleTest package

include(ExternalProject)

set(GOOGLETEST_SOURCE_DIR ${MAIN_SOURCE_DIR}/googletest)
set(GOOGLETEST_BINARY_DIR ${MAIN_BINARY_DIR}/googletest)
set(GOOGLETEST_INSTALL_PREFIX ${MAIN_INSTALL_PREFIX}/googletest)

message(STATUS "Install GoogleTest release 1.11.0")

ExternalProject_Add(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG e2239ee6043f73722e7aa812a459f54a28552929 # release 1.11.0
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    SOURCE_DIR ${GOOGLETEST_SOURCE_DIR}
    BINARY_DIR ${GOOGLETEST_BINARY_DIR}
    CMAKE_ARGS -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER} -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${GOOGLETEST_INSTALL_PREFIX}
    )
