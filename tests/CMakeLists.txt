add_executable(can_db_tests
    test_can_db.c
    unity/unity.c
    test_main.c
)

target_link_libraries(can_db_tests PRIVATE can_db)

# Only needed if your tests include headers in tests/ (helpers, etc.)
target_include_directories(can_db_tests PRIVATE
    .
    unity
)

add_test(NAME can_db_tests COMMAND can_db_tests)

