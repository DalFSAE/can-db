cmake_minimum_required(VERSION 3.22)
project(can_db LANGUAGES C)

option(CAN_DB_BUILD_TESTS "Build unit tests" ON)

# Where your generated CAN headers live (committed for now)
set(CAN_DB_GENERATED_INCLUDE_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    CACHE PATH "Directory containing generated CAN headers"
)

# ---- Library ---------------------------------------------------------------
# List sources here

file(GLOB_RECURSE CAN_DB_GENERATED_SOURCES
    CONFIGURE_DEPENDS
    "${CAN_DB_GENERATED_INCLUDE_DIR}/*.c"
)

add_library(can_db STATIC
    src/can_db.c
    ${CAN_DB_GENERATED_SOURCES}
)

target_compile_features(can_db PUBLIC c_std_11)

target_include_directories(can_db PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CAN_DB_GENERATED_INCLUDE_DIR}"
)

# Warnings (GCC/Clang)
if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(can_db PRIVATE -Wall -Wextra -Wpedantic)
endif()

# ---- Hello World -----------------------------------------------------------
add_executable(can_db_hello
    src/main.c
)

target_link_libraries(can_db_hello PRIVATE can_db)

# ---- Tests -----------------------------------------------------------------
if (CAN_DB_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

