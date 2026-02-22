cmake_minimum_required(VERSION 3.22)

project(can_db LANGUAGES C)

option(CAN_DB_BUILD_TESTS "Build unit tests" ON)

# Paths
set(CAN_DB_SRC_DIR        "${PROJECT_SOURCE_DIR}/src")
set(CAN_DB_INCLUDE_DIR    "${PROJECT_SOURCE_DIR}/include")


# ---- Library ---------------------------------------------------------------

# Generated CAN headers
set(CAN_DB_GENERATED_INCLUDE_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    CACHE PATH "Directory containing generated CAN headers"
)

file(GLOB_RECURSE CAN_DB_GENERATED_SOURCES
    CONFIGURE_DEPENDS
    "${CAN_DB_GENERATED_INCLUDE_DIR}/*.c"
)

add_library(can_db STATIC
    "${CAN_DB_SRC_DIR}/can_db.c"
    ${CAN_DB_GENERATED_SOURCES}
)

target_compile_features(can_db PUBLIC c_std_11)

target_include_directories(can_db PUBLIC
    "${CAN_DB_SRC_DIR}"
    "${CAN_DB_INCLUDE_DIR}"
)

# Warnings (GCC/Clang)
if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(can_db PRIVATE -Wall -Wextra -Wpedantic)
endif()

# ---- Main -----------------------------------------------------------
add_executable(main
    "${CAN_DB_SRC_DIR}/main.c"
)

target_link_libraries(main PRIVATE can_db)

# ---- Tests -----------------------------------------------------------------
if (CAN_DB_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

