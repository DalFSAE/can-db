# tests/CMakeLists.txt

file(GLOB_RECURSE CAN_DB_TEST_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)

add_executable(can_db_tests
    ${CAN_DB_TEST_SOURCES}
)

target_link_libraries(can_db_tests PRIVATE can_db)

# Only needed if your tests include headers in tests/ (helpers, etc.)
target_include_directories(can_db_tests PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/unity"
)

add_test(NAME can_db_tests COMMAND can_db_tests)

