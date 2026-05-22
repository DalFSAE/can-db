#include "unity/unity.h"
#include "test_can_db.h"

#include "can_db.h"
#include "can0_powertrain/can0_powertrain.h"


void test_can0_m172(void) {

    struct can0_powertrain_m172_torque_and_timer_info_t tx;
    can0_powertrain_m172_torque_and_timer_info_init(&tx);

    double commanded_torque = 100.0;    // Nm
    double torque_feedback  = 0.0;      // Nm
    double power_on_time    = 10.0;     // s

    // converter to raw units
    
    tx.inv_commanded_torque =
        can0_powertrain_m172_torque_and_timer_info_inv_commanded_torque_encode(commanded_torque);
    tx.inv_torque_feedback =
        can0_powertrain_m172_torque_and_timer_info_inv_torque_feedback_encode(torque_feedback);
    tx.inv_power_on_timer =
        can0_powertrain_m172_torque_and_timer_info_inv_power_on_timer_encode(power_on_time);

    /* Scale = 0.1 → raw = value / 0.1 */
    TEST_ASSERT_EQUAL_INT16(
        (int16_t)(commanded_torque / 0.1),
        tx.inv_commanded_torque
    );

    TEST_ASSERT_EQUAL_INT16(
        (int16_t)(torque_feedback / 0.1),
        tx.inv_torque_feedback
    );

    /* Scale = 0.003 → raw = value / 0.003 */
    TEST_ASSERT_EQUAL_UINT32(
        (uint32_t)(power_on_time / 0.003),
        tx.inv_power_on_timer
    );

    TEST_ASSERT_EQUAL(1, 1);
}

void test_can_import(void) {
    int rc = can_test();
    TEST_ASSERT_EQUAL(0, rc);
}

void test_can_table(void) {
    TEST_ASSERT_EQUAL(1, 0);
}

void run_test_can_db(void) {
    RUN_TEST(test_can_import);
    RUN_TEST(test_can0_m172);
    RUN_TEST(test_can_table);
}
