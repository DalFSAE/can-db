#include "unity/unity.h"
#include "test_can_db.h"

#include "can_db.h"
#include "unity/unity_internals.h"


void test_can_import(void) {
    int rc = can_test();
    TEST_ASSERT_EQUAL(0, rc);
}

void run_test_can_db(void) {
    RUN_TEST(test_can_import);
    return;
}
