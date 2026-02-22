#include "unity/unity.h"

#include "test_can_db.h"

int main(void) {
    UNITY_BEGIN();
    
    run_test_can_db();

    return UNITY_END();
}

void setUp(void) {}
void tearDown(void) {}
