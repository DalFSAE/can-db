#include "unity/unity.h"

#include "test_can_db.h"



void test_alive(void) {
    TEST_ASSERT_EQUAL(1, 1);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_alive);
    
    run_test_can_db();

    return UNITY_END();
}

void setUp(void) {}
void tearDown(void) {}
